#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "search.h"

// added functions to make timing easier
double array_timer(int *array, int length, int searches);
double list_timer(list_t *list, int length, int searches);
double bas_timer(int *array, int length, int searches);
double bst_timer(bst_t *tree, int length, int searches);

int main (int argc, char *argv[]) {
  // if wrong number of arguments display this
  if (argc < 4 || argc > 5) {
    printf("\nusage: ./search_benchmark <minpow> <maxpow> <repeats> [which]\n");
    printf(" which is a combination of:\n");
    printf("  a : Linear Array Search\n");
    printf("  l : Linked List Search\n");
    printf("  b : Binary Array Search\n");
    printf("  t : Binary Tree Search\n");
    printf("  (default all)\n\n");
    return 1;
  }


  int minpow = atoi(argv[1]);
  int maxpow = atoi(argv[2]);
  int repeats = atoi(argv[3]);
  char *mode = argv[4];

  // this will be the length of the structures
  int length;
  // this will be the number of searches done in the structures
  int searches;
  // values to hold how long it took
  double array_time, list_time, bas_time, bst_time;

  // calculate the time for each struct
  for (int i=minpow; i<=maxpow; i++) {
    // pow doesn't work for whatever reason so I just used bit shifting
    length = 2 << (i-1);
    searches = 2 * length * repeats;

    // initialize all the structs
    int *array = make_evens_array(length);
    list_t *list = make_evens_list(length);
    bst_t *tree = make_evens_tree(length);

    // calculate time for each
    array_time = array_timer(array, length, searches);
    list_time = list_timer(list, length, searches);
    bas_time = bas_timer(array, length, searches);
    bst_time = bst_timer(tree, length, searches);

    // free up all the structs
    free(array);
    list_free(list);
    bst_free(tree);

    // 'albt'
    if (argc == 4 || (strchr(mode,'a') != NULL && strchr(mode,'l') != NULL && strchr(mode,'b') != NULL && strchr(mode,'t') != NULL)) {
      // first line of display, this spacing looks the prettiest imo
      if (i == minpow) printf("\n%10s %10s %12s %12s %12s %12s\n","LENGTH","SEARCHES","array","list","binary","tree");
      // lines containing the data of the functions
      printf("%10d %10d %12.4e %12.4e %12.4e %12.4e\n",length,searches,array_time,list_time,bas_time,bst_time);
    }

    // everything from now on is basically the same as the if statement above
    // with a couple alterations, so I won't add unneccessary comments
    // 'alb'
    else if (strchr(mode,'a') != NULL && strchr(mode,'l') != NULL && strchr(mode,'b') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s %12s\n","LENGTH","SEARCHES","array","list","binary");
      printf("%10d %10d %12.4e %12.4e %12.4e\n",length,searches,array_time,list_time,bas_time);
    }

    // 'alt'
    else if (strchr(mode,'a') != NULL && strchr(mode,'l') != NULL && strchr(mode,'t') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s %12s\n","LENGTH","SEARCHES","array","list","tree");
      printf("%10d %10d %12.4e %12.4e %12.4e\n",length,searches,array_time,list_time,bst_time);
    }

    // 'abt'
    else if (strchr(mode,'a') != NULL && strchr(mode,'b') != NULL && strchr(mode,'t') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s %12s\n","LENGTH","SEARCHES","array","binary","tree");
      printf("%10d %10d %12.4e %12.4e %12.4e\n",length,searches,array_time,bas_time,bst_time);
    }

    // 'lbt'
    else if (strchr(mode,'l') != NULL && strchr(mode,'b') != NULL && strchr(mode,'t') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s %12s\n","LENGTH","SEARCHES","list","binary","tree");
      printf("%10d %10d %12.4e %12.4e %12.4e\n",length,searches,list_time,bas_time,bst_time);
    }

    // 'al'
    else if (strchr(mode,'a') != NULL && strchr(mode,'l') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s\n","LENGTH","SEARCHES","array","list");
      printf("%10d %10d %12.4e %12.4e\n",length,searches,array_time,list_time);
    }

    // 'ab'
    else if (strchr(mode,'a') != NULL && strchr(mode,'b') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s\n","LENGTH","SEARCHES","array","binary");
      printf("%10d %10d %12.4e %12.4e\n",length,searches,array_time,bas_time);
    }

    // 'at'
    else if (strchr(mode,'a') != NULL && strchr(mode,'t') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s\n","LENGTH","SEARCHES","array","tree");
      printf("%10d %10d %12.4e %12.4e\n",length,searches,array_time,bst_time);
    }

    // 'lb'
    else if (strchr(mode,'l') != NULL && strchr(mode,'b') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s\n","LENGTH","SEARCHES","list","binary");
      printf("%10d %10d %12.4e %12.4e\n",length,searches,list_time,bas_time);
    }

    // 'lt'
    else if (strchr(mode,'l') != NULL && strchr(mode,'t') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s\n","LENGTH","SEARCHES","list","tree");
      printf("%10d %10d %12.4e %12.4e\n",length,searches,list_time,bst_time);
    }

    // 'bt'
    else if (strchr(mode,'b') != NULL && strchr(mode,'t') != NULL) {
      if (i == minpow) printf("\n%10s %10s %12s %12s\n","LENGTH","SEARCHES","binary","tree");
      printf("%10d %10d %12.4e %12.4e\n",length,searches,bas_time,bst_time);
    }

    // 'a'
    else if (strcmp(mode,"a") == 0) {
      if (i == minpow) printf("\n%10s %10s %12s\n","LENGTH","SEARCHES","array");
      printf("%10d %10d %12.4e\n",length,searches,array_time);
    }

    // 'l'
    else if (strcmp(mode,"l") == 0) {
      if (i == minpow) printf("\n%10s %10s %12s\n","LENGTH","SEARCHES","list");
      printf("%10d %10d %12.4e\n",length,searches,list_time);
    }

    // 'b'
    else if (strcmp(mode,"b") == 0) {
      if (i == minpow) printf("\n%10s %10s %12s\n","LENGTH","SEARCHES","binary");
      printf("%10d %10d %12.4e\n",length,searches,bas_time);
    }

    // 't'
    else if (strcmp(mode,"t") == 0) {
      if (i == minpow) printf("\n%10s %10s %12s\n","LENGTH","SEARCHES","tree");
      printf("%10d %10d %12.4e\n",length,searches,bst_time);
    }

    // if incorrect letters typed, give this error and exit
    else {
      printf("\nmake sure to type 'a', 'l', 'b', and/or 't'\n\n");
      return 1;
    }
  }
  printf("\n");
  return 0;
}

// these functions all basically act the same but for different structures
// finds time for linear array search
double array_timer(int *array, int length, int searches) {
  // initialize clock variables
  clock_t begin, end;
  // set the beginning before the function runs
  begin = clock();
  for (int i=0; i<searches; i++) linear_array_search(array, length, i);
  // find the time after the function ends
  end = clock();
  // calculate and return the final time
  return ((double) (end - begin)) / CLOCKS_PER_SEC;
}

// finds time for linked list search
double list_timer(list_t *list, int length, int searches) {
  clock_t begin, end;
  begin = clock();
  for (int i=0; i<searches; i++) linkedlist_search(list, length, i);
  end = clock();
  return ((double) (end - begin)) / CLOCKS_PER_SEC;
}

// finds time for binary array search
double bas_timer(int *array, int length, int searches) {
  clock_t begin, end;
  begin = clock();
  for (int i=0; i<searches; i++) binary_array_search(array, length, i);
  end = clock();
  return ((double) (end - begin)) / CLOCKS_PER_SEC;
}

// finds time for binary tree search
double bst_timer(bst_t *tree, int length, int searches) {
  clock_t begin, end;
  begin = clock();
  for (int i=0; i<searches; i++) binary_tree_search(tree, length, i);
  end = clock();
  return ((double) (end - begin)) / CLOCKS_PER_SEC;
}
