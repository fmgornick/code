// I basically copied this outline from lab 2, but that's what you suggested
// so I figured I would cite my source
#include <stdio.h>
#include <string.h>
#include "hashset.h"

int main(int argc, char *argv[]) {
  int echo = 0;
  // check if this is run with the 'echo' command or just through stdin
  if (argc > 1 && strcmp("-echo",argv[1]) == 0) echo = 1;

  // prints all the commands that you can input
  printf("Hashset Application\n");
  printf("Commands:\n");
  printf("  hashcode <item>  : prints out the numeric hash code for the given key (does not change the hash set)\n");
  printf("  contains <item>  : prints the value associated with the given item or NOT PRESENT\n");
  printf("  add <item>       : inserts the given item into the hash set, reports existing items\n");
  printf("  print            : prints all items in the hash set in the order they were addded\n");
  printf("  structure        : prints detailed structure of the hash set\n");
  printf("  clear            : reinitializes hash set to be empty with default size\n");
  printf("  save <file>      : writes the contents of the hash set to the given file\n");
  printf("  load <file>      : clears the current hash set and loads the one in the given file\n");
  printf("  next_prime <int> : if <int> is prime, prints it, otherwise finds the next prime and prints it\n");
  printf("  expand           : expands memory size of hash set to reduce its load factor\n");
  printf("  bye              : exit the program\n");

  // gets assigned to user input
  char cmd[128];
  hashset_t hs;
  // 1 if function ran properly or 0 otherwise
  int success;
  // initialize hashset to default size (5)
  hashset_init(&hs, HASHSET_DEFAULT_TABLE_SIZE);

  // referring to the if (echo) statements, it just prints to the screen what
  // was in the file that was used to run a test
  while (1) {
    // application prompt
    printf("HS|> ");
    // check to see if user exited
    success = fscanf(stdin,"%s",cmd);
    if (success == EOF) {
      printf("\n");
      break;
    }

    // runs hashcode command
    if (strcmp("hashcode",cmd) == 0) {
      fscanf(stdin,"%s",cmd);
      if (echo) printf("hashcode %s\n",cmd);
      printf("%ld\n",hashcode(cmd));
    }

    // runs hashset_contains command
    else if (strcmp("contains",cmd) == 0) {
      fscanf(stdin,"%s",cmd);
      if (echo) printf("contains %s\n",cmd);

      success = hashset_contains(&hs,cmd);
      // says it found the string if contains evaluates to 1
      if (success) printf("FOUND: %s\n",cmd);
      // says it's not present otherwise
      else printf("NOT PRESENT\n");
    }

    // runs hashset_add function
    else if (strcmp("add",cmd) == 0) {
      fscanf(stdin,"%s",cmd);
      if (echo) printf("add %s\n",cmd);

      success = hashset_add(&hs,cmd);
      // if item is already in hashset you will be notified
      if (!success) printf("Item already present, no changes made\n");
    }

    // no print command in hashset_funcs.c so I just implemented a short one
    // here (I probably could have use hashset_write_items_ordered but idc
    else if (strcmp("print",cmd) == 0) {
      if (echo) printf("print\n");
      // point to first node in hashset
      hashnode_t *ptr = hs.order_first;
      int i = 1;
      // iterate through numbering them all off and printing result to screen
      while (ptr != NULL) {
        printf("%3d %s\n",i,ptr->item);
        ptr = ptr->order_next;
        i++;
      }
    }

    // runs hashset_show_structure command
    else if (strcmp("structure",cmd) == 0) {
      if (echo) printf("structure\n");
      // this will print a ton of information to the screen described in
      // hashset_funcs
      hashset_show_structure(&hs);
    }

    // clears up all the memory and re-initializes it
    else if (strcmp("clear",cmd) == 0) {
      if (echo) printf("clear\n");
      // free memory
      hashset_free_fields(&hs);
      // re-initialize
      hashset_init(&hs,HASHSET_DEFAULT_TABLE_SIZE);
    }

    // runs the hashset_save command
    else if (strcmp("save",cmd) == 0) {
      fscanf(stdin,"%s",cmd);
      if (echo) printf("save %s\n",cmd);
      hashset_save(&hs,cmd);
    }

    // runs the hashset_load command
    else if (strcmp("load",cmd) == 0) {
      fscanf(stdin,"%s",cmd);
      if (echo) printf("load %s\n",cmd);
      success = hashset_load(&hs,cmd);
      // if file could not be loaded, print failure to the screen
      if (!success) printf("load failed\n");
    }

    // finds the next prime after an inputed number
    else if (strcmp("next_prime",cmd) == 0) {
      // using num instead of cmd because cmd is a string
      int num;
      fscanf(stdin,"%d",&num);
      if (echo) printf("next_prime %d\n",num);
      printf("%d\n",next_prime(num));
    }

    // runs the hashset_expand command
    else if (strcmp("expand",cmd) == 0) {
      if (echo) printf("expand\n");
      hashset_expand(&hs);
    }

    // exits the program
    else if (strcmp("bye",cmd) == 0) {
      if (echo) printf("bye\n");
      break;
    }

    // notifies you if you misspelled something
    else {
      if (echo) printf("%s\n",cmd);
      printf("unknown command %s\n",cmd);
    }

  }

  // free all the remaining memory
  hashset_free_fields(&hs);
  return 0;
}
