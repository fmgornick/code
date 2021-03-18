#include <stdio.h>

int posneg(int *ptr);
// Determines if pointer to given int has a positive or
// negative value. Returns 0 for positive, 1 for negative.
// Defined in posneg.s assembly file.

int main(){
  int neg_one  = -1;
  int pos_five = 5;
  int neg_two  = -2;

  int *ptr = &pos_five;
  int result = posneg(ptr);
  if(result==0){
    printf("five is positive\n");
  }
  else{
    printf("five is negative\n");
  }

  if( posneg(&neg_one) ){
    printf("minus one is negative\n");
  }
  else{
    printf("minus one is positive\n");
  }

  return 0;
}
