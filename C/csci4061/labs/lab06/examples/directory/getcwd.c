/*=============================
 * C program which emulates the
 * behaviour of pwd command.
 * ============================*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  long maxpath;
  char *cwdNamePntr;

  if ((maxpath = pathconf ("/", _PC_PATH_MAX)) == -1)
    {
      perror ("Error while finding max pathlength");
      exit (1);
    }

  //printf("%ld\n",maxpath);
  if ((cwdNamePntr = (char *) malloc (maxpath + 1)) == NULL)
    {
      perror ("Error in allocating char array  for pathname");
      exit (1);
    }
/*======================================
 * Here you will learn how to use the
 * getcwd() system call. Always find out
 * what a system call returns on success
 * and failure!
 * =====================================*/
  char *x = getcwd(cwdNamePntr, maxpath); 
  //To show that x & cwdNamepntr are same and x is actually pointing to cwdNamePntr
  printf("%p\n",&(*x));
  printf("%p\n",&(*cwdNamePntr));
  if (x== NULL) // So we now know it returns NULL on failure!
  {
      perror ("Error in reading current working directory");
      exit (1);
  }

  printf ("Current working directory: %s \n", cwdNamePntr); // Here we go!

}

//end main();
