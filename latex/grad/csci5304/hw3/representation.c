#include <stdio.h>
#include <stdlib.h>

union {
  double d;
  unsigned char c[sizeof(double)];
} d;

void double_representation(double x) {
  char rep[25];

  d.d = x;
  for (int i = 0; i < sizeof d; ++i) {
    sprintf(rep + i * 3, " %02x", d.c[sizeof d - 1 - i]);
  }
  printf("%s\n", rep);
}

int main(int argc, char *argv[]) {
  char *ptr;
  double x = strtod(argv[1], &ptr);
  printf("%f\n", x);
  double_representation(x);
  return 0;
}
