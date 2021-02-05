#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "hashset.h"

// given
long  hashcode(char key[]) {
  union {
    char str[8];
    long num;
  } strnum;
  strnum.num = 0;

  for(int i=0; i<8; i++) {
    if(key[i] == '\0'){
      break;
    }
    strnum.str[i] = key[i];
  }
  return strnum.num;
}

// finds prime number
int   next_prime(int num) {
  int prime = num;
  int isPrime = 0;

  while (!isPrime) {
    // iterates from 2 to half the size of the number to cover every possible
    // dividend
    for (int i=2; i<=prime/2 && prime % i != 0; i++) {
      // break condition for while loop
      if (i == prime/2) isPrime = 1;
    }
    // increments if not prime
    if (isPrime == 0) prime++;
  }
  return prime;
}

// initializes each field of hashset to null
void  hashset_init(hashset_t *hs, int table_size) {
  hs->item_count = 0;
  hs->table_size = table_size;
  hs->table = malloc(table_size * sizeof(hashnode_t));
  // initializes each element in the table to NULL
  for (int i=0; i<table_size; i++) hs->table[i] = NULL;
  hs->order_first = NULL;
  hs->order_last = NULL;
}

// adds hashnode to hashset, return 1 if change was made
int   hashset_add(hashset_t *hs, char item[]) {
  // doesn't do anything if the node is already present
  if (hashset_contains(hs,item)) return 0;
  hashnode_t *node = malloc(sizeof(hashnode_t));
  // copy string input into hashnode item field
  strcpy(node->item,item);

  // special case where hashnode is the first in the set
  if (hs->item_count == 0) {
    node->table_next = NULL;
    node->order_next = NULL;

    hs->item_count++;
    hs->table[hashcode(item) % hs->table_size] = node;
    hs->order_first = node;
    hs->order_last = node;

    return 1;
  }

  else {
    // checks to see if bucket already contains a node, if not the current node
    // will not have a table_next field
    if (hs->table[hashcode(item) % hs->table_size] == NULL) node->table_next = NULL;
    // if there is already a node in the bucket, then set that as the
    // table_next field
    else node->table_next = hs->table[hashcode(item) % hs->table_size];
    node->order_next = NULL;

    hs->item_count++;
    hs->table[hashcode(item) % hs->table_size] = node;
    hs->order_last->order_next = node;
    hs->order_last = node;

    return 1;
  }
}

// check if the hashset contains a node with an item field matching key
int   hashset_contains(hashset_t *hs, char key[]) {
  // point to the table index would be located with the hash function
  hashnode_t *ptr = hs->table[hashcode(key) % hs->table_size];
  // iterate through every element of the hash table index
  while (ptr != NULL) {
    // compare the item field with key and return one if they match
    if (strcmp(ptr->item, key) == 0) return 1;
    ptr = ptr->table_next;
  }
  return 0;
}

// increase the size by the next prime number greater than 2 times it's
// original size
void  hashset_expand(hashset_t *hs) {
  hashset_t temp;
  // initialize hashset with new size
  hashset_init(&temp,next_prime(2*hs->table_size+1));
  hashnode_t *ptr = hs->order_first;

  // add all the elements in the original set to the new one
  while (ptr != NULL) {
    hashset_add(&temp,ptr->item);
    ptr = ptr->order_next;
  }

  // de-allocate all the memory associated with the old hashset
  hashset_free_fields(hs);
  *hs = temp;
}

// function used to free all the hashnode memory and that hashset's table
// memory.  Also initializes all the hashset fields to 0 or NULL
void  hashset_free_fields(hashset_t *hs) {
  hs->item_count = 0;
  hs->table_size = 0;
  hashnode_t *head = hs->order_first;
  hashnode_t *tail = hs->order_first;
  // iterate through hashnodes and free them
  while (head != NULL) {
    head = head->order_next;
    free(tail);
    tail = head;
  }
  hs->order_first = NULL;
  hs->order_last = NULL;
  // free the empty table
  free(hs->table);
}

// write all the hashnodes in the hashset to a file in the order they were
// added
void  hashset_write_items_ordered(hashset_t *hs, FILE *out) {
  hashnode_t *ptr = hs->order_first;
  int i = 1;
  // iterate through nodes until ptr reached them all
  while (ptr != NULL) {
    // write a line with the node information into the file
    fprintf(out,"%3d %s\n",i,ptr->item);
    ptr = ptr->order_next;
    i++;
  }
}

// prints out all the details of each field in the hashset as well as a visual
// representation of the hashset table with all the hashnodes
void  hashset_show_structure(hashset_t *hs) {
  printf("item_count: %d\n",hs->item_count);                    //item_count
  printf("table_size: %d\n",hs->table_size);                    //table_size
  if (hs->order_first == NULL) printf("order_first: NULL\n");   //order_first
  else printf("order_first: %s\n",hs->order_first->item);
  if (hs->order_last == NULL) printf("order_last : NULL\n");    //order_last
  else printf("order_last : %s\n",hs->order_last->item);
  printf("load_factor: %.4f\n",((float) hs->item_count) / ((float) hs->table_size)); //load_factor

  hashnode_t *ptr;
  char next[128];
  // iterate through hash table printing nodes in each index
  for (int i=0; i<hs->table_size; i++) {
    printf("[%2d] : ",i);
    ptr = hs->table[i];
    // print all the nodes in each index
    while (ptr != NULL) {
      if (ptr->order_next == NULL) strcpy(next,"NULL");
      else strcpy(next,ptr->order_next->item);
      printf("{%ld %s >>%s} ",hashcode(ptr->item),ptr->item,next);
      ptr = ptr->table_next;
    }
    printf("\n");
    
  }
}

// puts the hashset size and item count in the file and uses the
// hashset_write_items_ordered function to print the rest of the node info
void  hashset_save(hashset_t *hs, char *filename) {
  FILE *f = fopen(filename,"w");
  // exits if file cannot be opened
  if (f == NULL) {
    printf("ERROR: could not open file '%s'\n",filename);
    return;
  }
  // write in the table size and item count
  fprintf(f,"%d %d\n",hs->table_size,hs->item_count);
  // write in the rest of the information
  hashset_write_items_ordered(hs,f);
  fclose(f);
}

// takes a file and loads it's information into a new hashset, deleting all the
// previous information
int   hashset_load(hashset_t *hs, char *filename) {
  FILE *f = fopen(filename,"r");
  // exits if file cannot be opened
  if (f == NULL) {
    printf("ERROR: could not open file '%s'\n",filename);
    return 0;
  }

  // frees up all the memory in the hashset to put in new values
  hashset_free_fields(hs);
  int table_size;
  int item_count;
  int item_num;
  char name[128];
  // reads the first line of the file to get the size and count fields for the
  // hashset
  fscanf(f,"%d %d\n",&table_size,&item_count);
  hashset_init(hs,table_size);

  // iterates through each line and adds a new node with the given information
  // (basically just the name)
  for (int i=0; i<item_count; i++) {
    fscanf(f,"%3d %s\n",&item_num,name);
    hashset_add(hs,name);
  }
  fclose(f);
  return 1;
}

