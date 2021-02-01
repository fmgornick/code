#include <stdio.h>
#include <stddef.h>
#include "hashset.h"

long  hashcode(char key[]) {
  return 0;
}
int   next_prime(int num) {
  return 0;
}

void  hashset_init(hashset_t *hs, int table_size) {
  return;
}
int   hashset_add(hashset_t *hs, char item[]) {
  return 0;
}
int   hashset_contains(hashset_t *hs, char key[]) {
  return 0;
}
void  hashset_expand(hashset_t *hs) {
  return;
}
void  hashset_free_fields(hashset_t *hs) {
  return;
}

void  hashset_write_items_ordered(hashset_t *hs, FILE *out) {
  return;
}
void  hashset_show_structure(hashset_t *hs) {
  return;
}
void  hashset_save(hashset_t *hs, char *filename) {
  return;
}
int   hashset_load(hashset_t *hs, char *filename) {
  return 0;
}
