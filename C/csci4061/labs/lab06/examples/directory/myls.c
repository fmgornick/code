/*================================
 * C Program to which emulates the 
 * ls command.
 * ===============================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>


int main (int argc, char *argv[])
{
  DIR *dpntr; // So where is the DIR defined?
  struct dirent *dentry; // Look up dirent.h

  if (argc > 2)
    {
      printf ("Usage:  %s  [directory-name]\n", argv[0]);
      exit (1);
    }

/* =====================================
 * The opendir(), readdir() system calls
 * =====================================*/
  
  if (argc == 2)
    dpntr = opendir (argv[1]);
  else
    dpntr = opendir (".");

  if (dpntr == 0) // opendir() returns a 0 on failure!
    {
      fprintf (stderr, "Error in opening directory:  %s ", argv[1]);
      perror ("argv[0]");
    }

  dentry = readdir (dpntr); // Look up the behaviour of readdir() 

/*========================================
 * Here you will learn how to loop through
 * the contents of a directory.
 * =======================================*/
  
  while (dentry != 0) 
    {
      printf ("%s\n", dentry->d_name); // Remember, dentry is a pointer to the dirent structure.
      //printf("%ld\n", dentry->d_ino);
      dentry = readdir (dpntr);
    }
  closedir(dpntr);
}

// end main();
