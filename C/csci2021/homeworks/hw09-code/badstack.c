// badstack.c: C version of buggy assembly code in badstack_asm.s;
// this version works correctly as the compiler automatically creates
// space for local variables in main().

#include <stdio.h>

void inc_larger(int *x, int *y);

int main(){
  int a=2, b=3, c=6, d=7;
  inc_larger(&a, &b);
  inc_larger(&c, &d);
  printf("%d, %d, %d, %d, who do we appreciate?\n", a, b, c, d);
  printf("Compilers! Compilers! Yeeeeaaah COMPILERS!\n");
  return 0;
}

void inc_larger(int *x, int *y){
  if(*x >= *y){
    *x += 1;
  }
  else{
    *y += 1;
  }
}
  
