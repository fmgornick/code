// reversal_benchmark.c: Tests 2 versions of an array reversal
// code. Add timing information to determine which is more efficient
// and optionally implement a further optimized version.

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void reverse_arr1(int *arr, long size){
  int *tmp = malloc(sizeof(int)*size);
  for(long i=0; i<size; i++){
    tmp[i] = arr[size-i-1];
  }
  for(long i=0; i<size; i++){
    arr[i] = tmp[i];
  }
  free(tmp);
}

void reverse_arr2(int *arr, long size){
  for(long i=0; i<size/2; i++){
    int tmp = arr[i];
    arr[i] = arr[size-i-1];
    arr[size-i-1] = tmp;
  }
}


void reverse_arr_OPTM(int *arr, long size){
  // OPTIONALLY IMPLEMENT/TEST
}

int main(int argc, char *argv[]){
  if(argc < 4){
    printf("usage: %s <min_pow2> <max_pow2> <repeats>\n",argv[0]);
    return 1;
  }
  int minsize = atoi(argv[1]);
  int maxsize = atoi(argv[2]);
  int repeats = atoi(argv[3]);

  printf("%12s %12s %12s\n","SIZE","rev1","rev2");
  for(long s=minsize; s<=maxsize; s++){
    long size = 1 << s;

    int *arr1 = malloc(sizeof(int)*size);
    int *arr2 = malloc(sizeof(int)*size);
    for(long i=0; i<size; i++){
      arr1[i] = i;
      arr2[i] = i;
    }

    clock_t begin, end;
    
    begin = clock();
    for(int i=0; i<repeats; i++){ // repeatedly run function
      reverse_arr1(arr1,size);
    }
    end = clock();
    double cpu_time_1 = ((double) end - begin) / CLOCKS_PER_SEC;
      
    begin = clock();
    for(int i=0; i<repeats; i++){ // repeatedly run function
      reverse_arr2(arr2,size);
    }
    end = clock();
    double cpu_time_2 = ((double) end - begin) / CLOCKS_PER_SEC;

    // check array contents are correct 
    if(repeats % 2 == 0){       // even # repeats: arrays ordered
      for(long i=0; i<size; i++){
        assert(arr1[i] == i);
        assert(arr2[i] == i);
      }
    }
    else{                       // odd # repeats: arrays reversed
      for(long i=0; i<size; i++){
        assert(arr1[i] == size-i-1);
        assert(arr2[i] == size-i-1);
      }
    }

    free(arr1);
    free(arr2);

    printf("%12ld %12lf %12lf\n",size,cpu_time_1,cpu_time_2);
  }

  return 0;
}
