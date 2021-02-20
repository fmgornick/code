// batt_sim.c: DO NOT MODIFY
//
// Battery dispplay simulator support functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batt.h"
#include <stdint.h>

#define BATT_MAX_BITS 30

// Convenience struct for representing the battery display  as characters 
typedef struct {
  char chars[7][32];
} batt_display;

// Tied to the battery, provides a measure of voltage in units of 0.01
// volts.
short BATT_VOLTAGE_PORT;

// Global variable used to control the battery display. Making changes
// to this variable will change the battery meter display. Type
// ensures 32 bits.
int32_t BATT_DISPLAY_PORT = 0;

// Lowest order bit indicates whether display should be in Volts (0)
// or Percent (1). C code should only read this port. Tied to a user
// button which will toggle the bit.
unsigned char BATT_STATUS_PORT = 0;

// +-^^^-+                         0 
// |     |  #  #   ####  ####      1                 
// |     |  #  #      #     #      2                 
// |#####|  ####   ####  ####  V   3                 
// |#####|     #   #        #      4                 
// |#####|     # o ####  ####      5                    
// +-----+                         6
// 01234567890123456789012345678901                       
// 0         1         2         3                                 

// position of decimal place is at row 4, col 17

batt_display init_display = {
  .chars = {
    "+-^^^-+                        ", 
    "|     |                        ",                 
    "|     |                        ",                 
    "|     |                        ",                 
    "|     |                        ",                 
    "|     |                        ",                    
    "+-----+                        ",
  }
};

// Reset batt_display to be empty 
void reset_batt_display(batt_display *batt){
  *batt = init_display;
}  

// Print an batt_display 
void internal_print_batt_display(batt_display *batt){
  for(int i=0; i<7; i++){
    printf("%s\n",batt->chars[i]);
  }
}  

// Data and functions to set the state of the batt display 

// Position and char in display 
typedef struct {
  int r,c; int ch;
} charpos;
    
// Collection of characters corresponding to one bit in the state being set 
typedef struct {
  int len;                      // number of chars corresponding to this bit
  charpos pos[5];               // position of chars for this bit
} charpos_coll;

// Correspondence of bit positions to which characters should be set 
charpos_coll bits2chars[BATT_MAX_BITS] = {
  { .len=4, .pos={{ 0,25,'#'},{ 1,25,'#'}, { 2,25,'#'},{ 3,25,'#'}} }, //  0
  { .len=4, .pos={{ 3,25,'#'},{ 4,25,'#'}, { 5,25,'#'},{ 6,25,'#'}} }, //  1
  { .len=4, .pos={{ 6,22,'#'},{ 6,23,'#'}, { 6,24,'#'},{ 6,25,'#'}} }, //  2
  { .len=4, .pos={{ 3,22,'#'},{ 4,22,'#'}, { 5,22,'#'},{ 6,22,'#'}} }, //  3
  { .len=4, .pos={{ 0,22,'#'},{ 1,22,'#'}, { 2,22,'#'},{ 3,22,'#'}} }, //  4
  { .len=4, .pos={{ 0,22,'#'},{ 0,23,'#'}, { 0,24,'#'},{ 0,25,'#'}} }, //  5
  { .len=4, .pos={{ 3,22,'#'},{ 3,23,'#'}, { 3,24,'#'},{ 3,25,'#'}} }, //  6

  { .len=4, .pos={{ 0,19,'#'},{ 1,19,'#'}, { 2,19,'#'},{ 3,19,'#'}} }, //  7  
  { .len=4, .pos={{ 3,19,'#'},{ 4,19,'#'}, { 5,19,'#'},{ 6,19,'#'}} }, //  8  
  { .len=4, .pos={{ 6,16,'#'},{ 6,17,'#'}, { 6,18,'#'},{ 6,19,'#'}} }, //  9  
  { .len=4, .pos={{ 3,16,'#'},{ 4,16,'#'}, { 5,16,'#'},{ 6,16,'#'}} }, // 10  
  { .len=4, .pos={{ 0,16,'#'},{ 1,16,'#'}, { 2,16,'#'},{ 3,16,'#'}} }, // 11  
  { .len=4, .pos={{ 0,16,'#'},{ 0,17,'#'}, { 0,18,'#'},{ 0,19,'#'}} }, // 12  
  { .len=4, .pos={{ 3,16,'#'},{ 3,17,'#'}, { 3,18,'#'},{ 3,19,'#'}} }, // 13  

  { .len=4, .pos={{ 0,12,'#'},{ 1,12,'#'}, { 2,12,'#'},{ 3,12,'#'}} }, // 14 
  { .len=4, .pos={{ 3,12,'#'},{ 4,12,'#'}, { 5,12,'#'},{ 6,12,'#'}} }, // 15 
  { .len=4, .pos={{ 6, 9,'#'},{ 6,10,'#'}, { 6,11,'#'},{ 6,12,'#'}} }, // 16 
  { .len=4, .pos={{ 3, 9,'#'},{ 4, 9,'#'}, { 5, 9,'#'},{ 6, 9,'#'}} }, // 17 
  { .len=4, .pos={{ 0, 9,'#'},{ 1, 9,'#'}, { 2, 9,'#'},{ 3, 9,'#'}} }, // 18 
  { .len=4, .pos={{ 0, 9,'#'},{ 0,10,'#'}, { 0,11,'#'},{ 0,12,'#'}} }, // 19 
  { .len=4, .pos={{ 3, 9,'#'},{ 3,10,'#'}, { 3,11,'#'},{ 3,12,'#'}} }, // 20 

  { .len=1, .pos={{ 4,28,'%'}}                                      }, // 21
  { .len=1, .pos={{ 3,28,'V'}}                                      }, // 22

  { .len=1, .pos={{ 6,14,'o'}}                                      }, // 23

  { .len=5,.pos={{5,1,'#'},{5,2,'#'},{5,3,'#'},{5,4,'#'},{5,5,'#'}} }, // 24
  { .len=5,.pos={{4,1,'#'},{4,2,'#'},{4,3,'#'},{4,4,'#'},{4,5,'#'}} }, // 25
  { .len=5,.pos={{3,1,'#'},{3,2,'#'},{3,3,'#'},{3,4,'#'},{3,5,'#'}} }, // 26
  { .len=5,.pos={{2,1,'#'},{2,2,'#'},{2,3,'#'},{2,4,'#'},{2,5,'#'}} }, // 27
  { .len=5,.pos={{1,1,'#'},{1,2,'#'},{1,3,'#'},{1,4,'#'},{1,5,'#'}} }, // 28
};


// Assumes ints are at least 32 bits for disp
void set_batt_display(batt_display *batt, int disp){
  int i,j;
  int mask = 0x1;
  reset_batt_display(batt);
  for(i=0; i<BATT_MAX_BITS; i++){
    //    printf("Checking %d\n",i);
    if( disp & (mask << i) ){ // ith bit set, fill in characters 
      //      printf("%d IS SET\n",i);
      charpos_coll coll = bits2chars[i];
      //      printf("Coll len: %d\n",coll.len);
      for(j=0; j<coll.len; j++){
        //        printf("Inner iter %d\n",j);
        charpos pos = coll.pos[j];
        batt->chars[pos.r][pos.c] = pos.ch;
        // print_batt_display(batt);
      }
    }
  }
}


// Use the global BATT_DISPLAY_PORT to print the battery display
void print_batt_display(){
  batt_display batt;
  set_batt_display(&batt, BATT_DISPLAY_PORT);
  internal_print_batt_display(&batt);
  return;
}



#define NCLUSTERS 7
int clusters[NCLUSTERS] = {
  3, 5, 1, 2, 7, 7, 7,
};

// Generate a string version of the bits which clusters the bits based
// on the logical groupings in the problem
char *bitstr(int x, int bits){
  static char buffer[512];
  int idx = 0;
  int clust_idx = 0;
  int clust_break = clusters[0];
  for(int i=0; i<bits; i++){
    if(i==clust_break){
      buffer[idx] = ' ';
      idx++;
      clust_idx++;
      clust_break += clusters[clust_idx];
    }
    buffer[idx] = x & (1 << (31-i)) ? '1' : '0';
    idx++;
  }
  buffer[idx] = '\0';
  return buffer;
}

// Creates a string of bit indices matching the clustering pattern
// above
char *bitstr_index(int bits){
  static char buffer[512];
  char format[256];
  int pos = 0;
  int idx = bits;
  for(int i=0; i<NCLUSTERS; i++){
    idx -= clusters[i];
    if(clusters[i] > 1){
      sprintf(format, "%s%dd ","%",clusters[i]);
      pos += sprintf(buffer+pos, format, idx);
    }
    else{                       // cluster of 1 bit gets no index
      pos += sprintf(buffer+pos, "  ");
    }
  }
  buffer[pos-1] = '\0';         // eliminate trailing space
  return buffer;
}

// // Print the most signficant (right-most) to least signficant bit in
// // the integer passed in 
// void showbits(int x){
//   int i;
//   int mask = 0x1;
//   for(i=INT_BITS-1; i>=0; i--){
//     int shifted_mask = mask << i;
//     if(shifted_mask & x){
//       putchar('1');
//     } else {
//       putchar('0');
//     }
//   }
//   // Equivalent short version 
//   //    (x&(1<<i)) ? putchar('1'): putchar('0');
// }


// // Alternate printing format
// void print_intbits(int num){
//   char bits[32+8+1] = {};       // 32 1/0, 8 spaces, 1 \0
//   int idx = 0;
//   for(int i=0; i<32; i++){
//     if(i>0 && i%4==0){
//       bits[idx] = ' ';
//       idx++;
//     }
//     bits[idx] = num & (1 << (31-i)) ? '1' : '0';
//     idx++;
//   }
//   printf("bits:  %s\n",bits);
//   printf("index: %s\n",bit_indexes);
// }

// // Generate a string version of the bits, doesn't work well when bits
// // is not divisible by 4
// char *bitstr(int x, int bits){
//   static char buffer[512];
//   int idx = 0;
//   for(int i=0; i<bits; i++){
//     if(i>0 && i%4==0){
//       buffer[idx] = ' ';
//       idx++;
//     }
//     buffer[idx] = x & (1 << (31-i)) ? '1' : '0';
//     idx++;
//   }
//   buffer[idx] = '\0';
//   return buffer;
// }


// // Generate index string for bits, doesn't work well when 
// // bits is not divisible by 4
// char *bitstr_index(int bits){
//   static char buffer[512];
//   int idx = 0;
//   for(int i=0; i<bits; i+=4){
//     idx += sprintf(buffer+idx,"%4d ",bits-i-4);
//   }
//   buffer[idx-1] = '\0';         // eliminate trailing space
//   return buffer;
// }


