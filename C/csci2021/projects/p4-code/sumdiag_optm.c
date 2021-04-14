// optimized versions of matrix diagonal summing
#include "matvec.h"

// You can write several different versions of your optimized function
// in this file and call one of them in the last function.

int sumdiag_OPTM(matrix_t mat, vector_t vec) {
  // check if vector length matches the number of diagonals
  if(vec.len != (mat.rows + mat.cols -1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }
  // create variables for all the struct values so we don't need to enter the
  // struct each time a value is needed 
  int len=vec.len, rows=mat.rows, cols=mat.cols;
  // initialize vector array
  for (int i=0; i<len; i++) VSET(vec,i,0);

  // check if there's an even number of columns
  if (cols % 2 == 0) {
    for (int r=0; r<rows; r++) {
      for (int c=0; c<cols-1; c+=2) {
        // computer can add two values at a time because these operations are 
        // parallel
        vec.data[c - r + cols - 1] += MGET(mat,r,c);
        vec.data[c - r + cols] += MGET(mat,r,c+1);
      }
    }
  }

  // if there's an odd number of columns, you must do one less iterations
  // through the columns, then do a last one outside of the inner for loop
  else {
    for (int r=0; r<rows; r++) {
      for (int c=0; c<cols-2; c+=2) {
        vec.data[c - r + cols - 1] += MGET(mat,r,c);
        vec.data[c - r + cols] += MGET(mat,r,c+1);
      }
      // didn't do last column so this must be added
      vec.data[len - r - 1] += MGET(mat,r,cols-1);
    }
  }

  return 0;
}

