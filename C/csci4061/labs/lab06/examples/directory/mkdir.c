/*================================
 * C Program to create a directory 
 * with suitable permissions.
 * ===============================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
  long maxpath; // Can you find out what the maximum limit is?
  char *cwdNamePntr; 
  mode_t perms = 0740; // Default permissions for newly created directory

  if (argc != 2)
    {
      printf ("Usage: %s Directory-Path-Name\n ", argv[0]);
      exit (1);
    }

  if ((mkdir (argv[1], perms)) == 0) // mkdir() returns 0 when succesful. What does it return otherwise?
    {
      printf ("New directory created successfully.\n");
    }
  else
    {
      perror ("Error in directory creation");
    }
}
