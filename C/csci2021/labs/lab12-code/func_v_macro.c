// func_v_macro.c: demonstrate timing differences between using
// function calls and macros. The mget()/vset() functions and
// MGET()/VSET() macros behave the same but macros do not involve
// control jumps so lead to better efficiency without
// optimizations. Performing function inlining such as is done at gcc
// -O3 will lead to near identical performance as the bodies of the
// small functions will be inserted at their call sites just like the
// macros are. With minimal optimization such as -Og, one will observe
// timing differences between these versions.
// 
// Note: to see the results of the Preprocessor, compile via
// 
// > gcc -E func_v_macro.c > preprocessed.c
//
// and inspect the freshly created preprocessed.c file. The functions
// and main() code will be low down in the file the contents of many
// header files will be inserted above them.
// 
// Complete the TODO items to finish this file. Each item should only
// require 1 line of code to finish.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>               // for clock() and other functions
#include <stdio.h>
#include <sys/time.h>
#include "matvec.h"

int mget(matrix_t mat, int i, int j){
  return mat.data[i*mat.cols + j];
}
int vset(vector_t vec, int i, int x){
  return vec.data[i] = x;
}

void row_sums_function(matrix_t mat, vector_t sums){
  for(int i=0; i<mat.rows; i++){
    int sum = 0;
    for(int j=0; j<mat.cols; j++){
      // TODO: call provided Function to get a matrix element and add it to the sum
      sum += mget(mat,i,j);
    }
    // TODO: call provided Function to set a vector element to the current sum
    vset(sums,i,sum);
  }
}

#define MGET(mat,i,j) ((mat).data[((i)*((mat).cols)) + (j)])
#define VSET(vec,i,x) ((vec).data[(i)] = (x))

void row_sums_macro(matrix_t mat, vector_t sums){
  for(int i=0; i<mat.rows; i++){
    int sum = 0;
    for(int j=0; j<mat.cols; j++){
      // TODO: use the provided Macro to get a matrix element and add it to the sum
      sum += MGET(mat,i,j);
    }
    // TODO: use the provided Macro to set a vector element to the current sum
    VSET(sums,i,sum);
  }
}

void row_sums_direct(matrix_t mat, vector_t sums){
  int idx = 0;
  for(int i=0; i<mat.rows; i++){
    int sum = 0;
    for(int j=0; j<mat.cols; j++){
      // TODO: Directly access the data array at idx to get a matrix element
      sum += mat.data[idx + j];
    }
    idx += mat.cols;
    // TODO: Directly access the vector data array to set element i to the sum
    sums.data[i] = sum;
  }
}

#define REPEATS 50              // number of times to repeat the summing 


int main(int argc, char *argv[]){

  if(argc < 3){
    printf("usage: %s <rows> <cols> \n",argv[0]);
    return 1;
  }

  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);

  // Allocate the matrix and fill it in with 1,2,3,4...
  matrix_t mat;
  matrix_init(&mat, rows,cols);
  matrix_fill_sequential(mat);
  vector_t sums;

  // Variables for timing
  clock_t begin, end;
  double cpu_time;

  vector_init(&sums, mat.rows);
  begin = clock();
  for(int i=0; i<REPEATS; i++){
    row_sums_function(mat,sums);
  }
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%18s: %.4e secs\n","row_sums_function",cpu_time);    

  begin = clock();
  for(int i=0; i<REPEATS; i++){
    row_sums_macro(mat,sums);
  }
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%18s: %.4e secs\n","row_sums_macro",cpu_time);    

  vector_init(&sums, mat.rows);
  begin = clock();
  for(int i=0; i<REPEATS; i++){
    row_sums_direct(mat,sums);
  }
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%18s: %.4e secs\n","row_sums_direct",cpu_time);    

  matrix_free_data(&mat);
  vector_free_data(&sums);

  return 0;
}
