#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>

#define DIM1 5
#define DIM2 7

#define NUMDIGPRNT 3
#define NUMDIGPRNTANS 4

#define MAT_MAX 10
#define MAT_MIN 1

#define new_max(x,y) (((x) >= (y)) ? (x) : (y))
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))

pthread_barrier_t barrier;

pthread_mutex_t answer_access 	= PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    int NUM_ROW;
    int NUM_CLM;
    int **data;
} matrix_t;

matrix_t matrix_1;
matrix_t matrix_2;
matrix_t one_thread_answer;
matrix_t multi_thread_answer;

void print_matrix(matrix_t to_print){
    for(int i = 0; i < to_print.NUM_ROW; i++){
        for(int j = 0; j <  to_print.NUM_CLM; j++){
            printf("%*d ", NUMDIGPRNT, to_print.data[i][j]);
        }
        printf("\n");
    }
}

void fill_matrix(matrix_t *to_fill){
    to_fill->data = malloc(to_fill->NUM_ROW * sizeof(int*));
    for(int i = 0; i < to_fill->NUM_ROW; i++){
        to_fill->data[i] = (int*)malloc(to_fill->NUM_CLM * sizeof(int));
        for(int j = 0; j < to_fill->NUM_CLM; j++){
            to_fill->data[i][j] = rand() % MAT_MAX + MAT_MIN;
        }
    }
}

void zero_matrix(matrix_t *to_zero){
    to_zero->data = malloc(to_zero->NUM_ROW * sizeof(int*));
    for(int i = 0; i < to_zero->NUM_ROW; i++){
        to_zero->data[i] = (int*)malloc(to_zero->NUM_CLM * sizeof(int));
        for(int j = 0; j < to_zero->NUM_CLM; j++){
            to_zero->data[i][j] = 0;
        }
    }
}

void free_matrix(matrix_t to_free){
    for(int i = 0; i < to_free.NUM_ROW; i++){
        free(to_free.data[i]);
    }
    free(to_free.data);
}

matrix_t single_thread_matmult(matrix_t mat1, matrix_t mat2){
    matrix_t answer;
    answer.NUM_ROW = mat1.NUM_ROW;
    answer.NUM_CLM = mat2.NUM_CLM;
    zero_matrix(&answer);

    //Compute Answer for printing
    for(int i = 0; i < mat1.NUM_ROW; i++){
        for(int j = 0; j < mat2.NUM_CLM; j++){
            for(int ii = 0; ii < mat1.NUM_CLM; ii++){
                answer.data[i][j] += mat1.data[i][ii] * mat2.data[ii][j];
            }
            
        }
    }

    

    for(int i = 0; i < new_max(mat1.NUM_ROW, mat2.NUM_ROW); i++){
        int space_offset = ((NUMDIGPRNT + 1) * (mat1.NUM_CLM + 1)) +2;
        if(i < mat1.NUM_ROW){
            space_offset = NUMDIGPRNT * 2;
            for(int j = 0; j <  mat1.NUM_CLM; j++){
                printf("%*d ", NUMDIGPRNT, mat1.data[i][j]);
            }
        }

        if(i == (int)(mat1.NUM_ROW / 2)){
            printf(" x ");
            space_offset -= 3;
        }

        if(i < mat2.NUM_ROW){
            for(int j = 0; j <  mat2.NUM_CLM; j++){
                if(j == 0)
                    printf("%*d ", space_offset, mat2.data[i][j]);
                else
                    printf("%*d ", NUMDIGPRNT, mat2.data[i][j]);
            }
        }

        space_offset = NUMDIGPRNTANS * 2;
        if(i == (int)(mat1.NUM_ROW / 2)){
            printf(" = ");
            space_offset -= 3;
        }

        //Print Answer
        if(i < answer.NUM_ROW){
            for(int j = 0; j <  answer.NUM_CLM; j++){
                if(j == 0)
                    printf("%*d ", space_offset, answer.data[i][j]);
                else
                    printf("%*d ", NUMDIGPRNTANS, answer.data[i][j]);
            }
        }
        printf("\n");
    }

    return answer;
}

void *multiplier_thread(void *arg)
{
    //Figure out which column this thread is in charge of
    int col_index =  *(int*)arg;

    int local[multi_thread_answer.NUM_ROW][multi_thread_answer.NUM_CLM];

    //Compute a portion of the matrix multiplication locally
    for(int i = 0; i < multi_thread_answer.NUM_ROW; i++){
        for(int j = 0; j < multi_thread_answer.NUM_CLM; j++){
            local[i][j] = matrix_1.data[i][col_index] * matrix_2.data[col_index][j];
        }
    }

    //Acquire a lock to the answer data and sum the data within there
    pthread_mutex_lock(&answer_access);
    for(int i = 0; i < multi_thread_answer.NUM_ROW; i++){
        for(int j = 0; j < multi_thread_answer.NUM_CLM; j++){
            multi_thread_answer.data[i][j] += local[i][j];
        }
    }
    pthread_mutex_unlock(&answer_access);

    //TODO Barrier here to "check-in" with the verification thread (pthread_barrier_wait)
    pthread_barrier_wait(&barrier);

}

void *verify_matrix(void *arg)
{
    //TODO barrier synchronization here so the answer is not checked until all threads have summed (pthread_barrier_wait)
    pthread_barrier_wait(&barrier);


    //Acquire the answer lock to be safe and sum the results
    bool was_match = true;
    pthread_mutex_lock(&answer_access);
    for(int i = 0; i < one_thread_answer.NUM_ROW; i++){
        for(int j = 0; j < one_thread_answer.NUM_CLM; j++){
            if(one_thread_answer.data[i][j] != multi_thread_answer.data[i][j]){
                printf("ERROR! Matrix mismatch at index (%d,%d) Good Value [%d] Bad Value [%d]\n", i, j, one_thread_answer.data[i][j], multi_thread_answer.data[i][j]);
                was_match = false;
            }
        }
    }
    pthread_mutex_unlock(&answer_access);

    if(!was_match){
        printf("ERROR: Matrices did not match, race condition detected\n");
        printf("\n=============== WRONG Answer ====================\n");    
        print_matrix(multi_thread_answer);
        printf("====================================================\n\n");
    }else{
        printf("SUCCESS: Matrices matched\n");
        printf("\n=============== YOUR  Answer ======================\n");    
        print_matrix(multi_thread_answer);
        printf("====================================================\n\n");
    }

}

int main(int argc, char **argv){

    //Random seed based on time of day
    srand(time(NULL));

    //Init and fill matrix 1 size(DIM1 x DIM2)
    matrix_1.NUM_ROW    = DIM1;
    matrix_1.NUM_CLM    = DIM2;
    fill_matrix(&matrix_1);

    //Init and fill matrix 2 size(DIM2 x DIM1)
    matrix_2.NUM_ROW    = DIM2;
    matrix_2.NUM_CLM    = DIM1;
    fill_matrix(&matrix_2);

    //Retrieve Single Thread Answer (correct answer)
    printf("\n=============== Correct Answer ==================\n");    
    one_thread_answer = single_thread_matmult(matrix_1, matrix_2);
    printf("====================================================\n\n");

    //Initialize multi_thread answer matrix
    multi_thread_answer.NUM_ROW = matrix_1.NUM_ROW;
    multi_thread_answer.NUM_CLM = matrix_2.NUM_CLM;
    zero_matrix(&multi_thread_answer);

    /*TODO initialize your pthread_barrier
    *   Hint: Use the matrix_1.NUM_CLM + 1 as the number of threads since we want to synchronize on all worker threads and the verification thread
    *         (aka use num_threads)
    */
    int num_threads = matrix_1.NUM_CLM + 1;
    pthread_barrier_init(&barrier, NULL, num_threads);



    //Create verification thread  --> This thead will try and compare your answer to the correct answer
    pthread_t verification_thread;
    if(pthread_create(&verification_thread, NULL, verify_matrix, NULL)!=0){
        fprintf(stderr,"Error creating verification thread\n");
        exit(1);
    }

    //Create multiplier threads
    pthread_t multiplier_threads[matrix_1.NUM_CLM];  
    int index_arr[matrix_1.NUM_CLM];
    for(int i = 0; i < matrix_1.NUM_CLM; i++){
        index_arr[i] = i;
        if(pthread_create(&multiplier_threads[i], NULL, multiplier_thread, &index_arr[i])!=0){
            fprintf(stderr,"Error creating multiplier thread\n");
            exit(1);
        }
    }

    //Join verification thread
    if(pthread_join(verification_thread, NULL)!= 0){
        fprintf(stderr,"Error joining verification thread\n");
        exit(1);
    }
    
    //Join multiplier threads
    for(int i = 0; i < matrix_1.NUM_CLM; i++){
       if(pthread_join(multiplier_threads[i], NULL)!= 0){
            fprintf(stderr,"Error joining multiplier thread\n");
            exit(1);
       }
    }

    
    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(one_thread_answer);
    free_matrix(multi_thread_answer);

    //TODO destroy the barrier that was initalized
    pthread_barrier_destroy(&barrier);
}


