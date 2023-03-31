/*
 * CSCI 5103 Spring 2023
 * Assignment 3
 * name:       Gabe Fendrich, Flercher Gornick
 * student id: 5556448,       5579904
 * x500 id:    gorni025,      fendr012
 * CSELABS machine: csel-xsme-s23-csci5103-13
 *                  csel-xsme-s23-csci5103-15
 */

/*
 * main.c --  template file given for TimeoutBuffer device
 *            assignment for CSCI 5103
 * This code is based on the scullpipe code from LDD book.
 *         CSCI 5103 March 2023  -- Anand Tripathi
 *
 * This module will create only one device /dev/timedbufer
 *
 * The source code in this file can be freely used, adapted,
 * and redistributed in source or binary form, so long as an
 * acknowledgment appears in derived source files.  The citation
 * should list that the code comes from the book "Linux Device
 * Drivers" by Alessandro Rubini and Jonathan Corbet, published
 * by O'Reilly & Associates.   No warranty is attached;
 * we cannot take responsibility for errors or fitness for use.
 */

#include <linux/cdev.h>
#include <linux/configfs.h>
#include <linux/errno.h> /* error codes */
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/fs.h>    /* everything... */
#include <linux/init.h>
#include <linux/kernel.h> /* printk() */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/seq_file.h>
#include <linux/slab.h>    /* kmalloc() */
#include <linux/types.h>   /* size_t */
#include <linux/uaccess.h> /* copy_*_user */

#include "timedbuffer.h" /* local definitions */

/* Our parameters which can be set at load time. */
struct scull_buffer {
  wait_queue_head_t inq, outq; /* read and write queues         */
  char *buffer, *end;          /* begin of buf, end of buf      */
  int buffersize;              /* used in pointer arithmetic    */
  char *rp, *wp;               /* where to read, where to write */
  int itemcount;               /* Number of items in the buffer */
  int nreaders, nwriters;      /* number of openings for r/w    */
  struct semaphore sem;        /* mutual exclusion semaphore    */
  struct cdev cdev;            /* Char device structure         */
};

dev_t scull_b_devno; /* our first device number */

static struct scull_buffer *scull_b_devices;

#define init_MUTEX(_m) sema_init(_m, 1);

int scull_major = SCULL_MAJOR;
int scull_minor = 0;
int NITEMS = 20;
int itemsize = ITEM_SIZE;

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(NITEMS, int, 0);

MODULE_AUTHOR("Student CSCI 5103-Spring-2023 - adding code to the frameowrk by "
              "Anand Tripathi");
MODULE_LICENSE("Dual BSD/GPL");

/* open and close */
static int scull_b_open(struct inode *inode, struct file *filp) {
  /* retrieve scull buffer and set filp private_data pointer to it */
  struct scull_buffer *dev;
  dev = container_of(inode->i_cdev, struct scull_buffer, cdev);
  filp->private_data = dev;

  /* acquire semaphore for altering scull_buffer vars */
  if (down_interruptible(&dev->sem))
    return -ERESTARTSYS;

  /* if pointer to buffer is null, then our data isn't initialized
   * so malloc buffer and set the pointers (rp, wp point to start) */
  if (!dev->buffer) {
    dev->buffersize = NITEMS * itemsize;
    dev->buffer = kmalloc(dev->buffersize, GFP_KERNEL);
    dev->end = dev->buffer + dev->buffersize;
    dev->rp = dev->buffer;
    dev->wp = dev->buffer;
    dev->itemcount = 0;
  }

  /* increment reader or writer depending on file permissions
   * write only means it's a writer, read only (other) means
   * it's a reader */
  if ((filp->f_flags & O_ACCMODE) == O_WRONLY)
    dev->nwriters++;
  else
    dev->nreaders++;

  /* release semaphore and clear new bits / mark object as not
   * being seekable */
  up(&dev->sem);
  return nonseekable_open(inode, filp);
}

static int scull_b_release(struct inode *inode, struct file *filp) {
  /* grab our scull buffer struct */
  struct scull_buffer *dev = filp->private_data;

  /* acquire semaphore for altering scull_buffer vars */
  if (down_interruptible(&dev->sem))
    return -ERESTARTSYS;

  /* decrement reader or writer depending on file permissions
   * write only means it's a writer, read only (other) means
   * it's a reader */
  if ((filp->f_flags & O_ACCMODE) == O_WRONLY)
    dev->nwriters--;
  else
    dev->nreaders--;

  /* if there are no more readers and writers left to access
   * our data, then free the buffer and make sure there are no
   * dangling pointers */
  if (dev->nreaders == 0 && dev->nwriters == 0) {
    kfree(dev->buffer);
    dev->buffer = NULL;
    dev->end = NULL;
    dev->rp = NULL;
    dev->wp = NULL;
  }

  /* release semaphore and return */
  up(&dev->sem);
  return 0;
}

/* data management: read and write */
static ssize_t scull_b_read(struct file *filp, char __user *buf, size_t count,
                            loff_t *f_pos) {
  /* grab our scull buffer struct */
  struct scull_buffer *dev = filp->private_data;

  /* if our buffer is empty, we wait until an item is dropped in.
   * if we've waited for 20 sec and still haven't woken up, then check
   * if there are any writer processes left. If not, return 0 */
  while (dev->itemcount == 0) {
    wait_event_interruptible_timeout(dev->inq, dev->itemcount > 0, 2000);
    if (dev->itemcount == 0 && dev->nwriters == 0)
      return 0;
  }

  /* acquire semaphore for altering scull_buffer vars
   * (return -1 if fail) */
  if (down_interruptible(&dev->sem))
    return -1;

  /* read item from our buffer into the calling user's buffer
   * (return -1 if fail) */
  if (copy_to_user(buf, dev->rp, count))
    return -1;

  /* if all went well, update our read pointer and decrement the
   * item count */
  dev->rp += count;
  if (dev->rp >= dev->end)
    dev->rp = dev->buffer;

  dev->itemcount--;

  /* release semaphore notify any writers that there's a slot available
   * then return the size of the item we just read into user's buffer */
  up(&dev->sem);
  wake_up_interruptible(&dev->outq);
  return count;
}

static ssize_t scull_b_write(struct file *filp, const char __user *buf,
                             size_t count, loff_t *f_pos) {
  /* grab our scull buffer struct */
  struct scull_buffer *dev = filp->private_data;

  /* if our buffer is full, we wait until an item is picked out.
   * if we've waited for 20 sec and still haven't woken up, then check
   * if there are any reader processes left. If not, return 0 */
  while (dev->itemcount == NITEMS) {
    wait_event_interruptible_timeout(dev->outq, dev->itemcount < NITEMS, 2000);
    if (dev->itemcount == NITEMS && dev->nreaders == 0)
      return 0;
  }

  /* acquire semaphore for altering scull_buffer vars
   * (return -1 if fail) */
  if (down_interruptible(&dev->sem))
    return -1;

  /* read item from the calling user's buffer into our buffer
   * (return -1 if fail) */
  if (copy_from_user(dev->wp, buf, count))
    return -1;

  /* if all went well, update our write pointer and increment the
   * item count */
  dev->wp += count;
  if (dev->wp >= dev->end)
    dev->wp = dev->buffer;

  dev->itemcount++;

  /* release semaphore notify any readers that there's an item available
   * then return the size of the item we just wrote into our buffer */
  up(&dev->sem);
  wake_up_interruptible(&dev->inq);
  return count;
}

/* The file operations for the buffer device
 * (some are overlayed with bare scull) */
struct file_operations scull_buffer_fops = {
    .owner = THIS_MODULE,
    .llseek = no_llseek,
    .read = scull_b_read,
    .write = scull_b_write,
    .open = scull_b_open,
    .release = scull_b_release,
};

/* set up a cdev entry. */
static void scull_b_setup_cdev(struct scull_buffer *dev, int index) {
  int err, devno = scull_b_devno + index;

  cdev_init(&dev->cdev, &scull_buffer_fops);
  dev->cdev.owner = THIS_MODULE;
  err = cdev_add(&dev->cdev, devno, 1);

  /* Fail gracefully if need be */
  if (err)
    printk(KERN_NOTICE "Error %d adding timedbuffer%d", err, index);
}

/* The cleanup function is used to handle initialization failures as well.
 * Thefore, it must be careful to work correctly even if some of the items
 * have not been initialized */
void scull_b_cleanup_module(void) {
  if (!scull_b_devices)
    return; /* nothing else to release */

  cdev_del(&scull_b_devices[0].cdev);
  kfree(scull_b_devices[0].buffer);

  kfree(scull_b_devices);
  unregister_chrdev_region(scull_b_devno,
                           1); // only one device to be unregistered
}

int scull_b_init_module(void) {
  int result;
  dev_t dev = 0;

  /* Get a range of minor numbers to work with, asking for a dynamic
   * major unless directed otherwise at load time. */
  if (scull_major) {
    dev = MKDEV(scull_major, scull_minor);
    result = register_chrdev_region(dev, 1, "timedbuffer");
  } else {
    result = alloc_chrdev_region(&dev, scull_minor, 1, "timedbuffer");
    scull_major = MAJOR(dev);
  }
  if (result < 0) {
    printk(KERN_WARNING "scull_b_init: can't get major %d\n", scull_major);
    return 0;
  }

  scull_b_devno = dev;
  scull_b_devices = kmalloc(sizeof(struct scull_buffer),
                            GFP_KERNEL); // only one device to be created
  if (scull_b_devices == NULL) {
    unregister_chrdev_region(dev, 1);
    return 0;
  }
  memset(scull_b_devices, 0, sizeof(struct scull_buffer));
  init_waitqueue_head(&(scull_b_devices[0].inq));
  init_waitqueue_head(&(scull_b_devices[0].outq));
  init_MUTEX(&scull_b_devices[0].sem);
  scull_b_setup_cdev(scull_b_devices, 0);

  return 1;
}

module_init(scull_b_init_module);
module_exit(scull_b_cleanup_module);
