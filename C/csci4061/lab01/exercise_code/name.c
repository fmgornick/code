#include "include/main.h"
#include "include/name.h"

void getName(char * name) {
    printf("Enter your name: ");
    fgets(name, maxLen, stdin);
    fflush(stdin);
}