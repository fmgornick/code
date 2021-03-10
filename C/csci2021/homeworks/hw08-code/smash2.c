// smash1.c: demonstrates problems with the function call stack
#include <stdio.h>
#include <stdlib.h>
void fill_seq(int *a);
void demo();

int main(){
  printf("About to do the demo\n");
  demo();
  printf("Demo Complete\n");
  return 0;
}

void demo(){
  int *arr = malloc(sizeof(int)*4);

  fill_seq(arr);

  for(int i=0; i<4; i++){
    printf("[%d]: %d\n",i,arr[i]);
  }
  free(arr);
}

#define END 8
void fill_seq(int *a){
  for(int i=0; i<END; i++){
    a[i] = (i+1)*2;
  }
}
    
