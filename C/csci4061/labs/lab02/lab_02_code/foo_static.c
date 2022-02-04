#include <math.h>
#include <stdio.h>

void foo(void) {
  static int x = 0;
  printf("x is %d\n", x);
  x++;
}

int main() {
  foo();
  foo();
  foo();
  return 0;
}
