// Fletcher Gornick: gorni025@umn.edu

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int numOfEntries(char *path) {
  // TODO: Count the number of entries in path
  int count = 0;

  DIR *dir;
  if ((dir = opendir(path)) == NULL) {
    perror("failed to open directory");
    return -1;
  }

  struct dirent *de;
  while ((de = readdir(dir)) != NULL) {
    count++;
  }

  return count;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Pass the path as an argument to the program");
    exit(1);
  }
  char *path = argv[1];

  DIR *dir = opendir(path);
  if (dir == NULL) {
    printf("The path passed is invalid");
    return -1;
  }
  struct dirent *entry;

  /*
      TODO:
      Iterate through the elements in argv[1]
      1.Check DT_DIR and DT_REG
      2.What if the entry is "." and ".."

  */
  int numEntries = numOfEntries(path);

  for (int i = 0; i < numEntries; i++) {
    entry = readdir(dir);
    char name[1024];
    sprintf(name, "%s/%s", path, entry->d_name);

    if (entry->d_type == DT_REG) {
      struct stat st;
      stat(entry->d_name, &st);
      printf("Regular File: %s\n", entry->d_name);
      printf("\tOwner: %u\n", st.st_uid);
      printf("\tSize: %ld\n", st.st_size);
      printf("\tInode: %lu\n", st.st_ino);
    } else if (entry->d_type == DT_DIR) {
      printf("Directory: %s\n", entry->d_name);
      printf("\tEntries: %d\n", numOfEntries(name));
    } else {
      printf("Other: %s\n", entry->d_name);
    }
  }

  closedir(dir);
  return 0;
}
