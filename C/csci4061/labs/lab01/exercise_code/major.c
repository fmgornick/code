#include "include/major.h"
#include "include/main.h"

void getMajor(char *major) {
  printf("Enter your major: ");
  fgets(major, maxLen, stdin);
  fflush(stdin);
}

