/*
 * Recitation section number: 013
 * Your name                    (email address): gorni025@umn.edu
 * Partner name (if applicable) (email address): joh18218@umn.edu
 */

#include "include/main.h"
#include "include/address.h"
#include "include/major.h"
#include "include/name.h"

int main() {

  char name[maxLen];
  char address[maxLen];
  char major[maxLen];

  printf("Hi there! \nTell me more about you.\n");
  getName(name);
  getAddress(address);
  getMajor(major);

  printf("Thanks for your information!\n");
  printf("Your name: %s", name);
  printf("Your address: %s", address);
  printf("Your major: %s", major);
  printf("Bye!\n");

  return 0;
}
