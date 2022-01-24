#include "include/address.h"
#include "include/main.h"

void getAddress(char *address) {
  printf("Enter your address: ");
  fgets(address, maxLen, stdin);
  fflush(stdin);
}
/*
 * Write getAddress function
 * void getAddress(char * address);
 * Prints a prompt "Enter your address: " to get an address,
 * Reads in the user's address
 */
