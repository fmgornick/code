#include <stdio.h>

int dodiv(int numer, int denom, int *quot, int *rem);
// equivalent to
// *quot = numer / div;
// *rem  = numer % div;

int main(){
  int numer = 42;
  int denom = 11;
  int quot;
  int rem;

  int result = dodiv(numer, denom, &quot, &rem);

  printf("%d / %d = %d rem %d\n",numer,denom,quot,rem);
  // Should be
  //   42 / 11 = 3 rem 9
  // if assembly is correct

  return 0;
}


  
