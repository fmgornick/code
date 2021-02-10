#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[128];               // name of student
  double score;                 // score on exam
} grade_t;
// struct which allows assignment of name/score such as in
//   best = curgrade;
//   printf("best is now: %s %f\n", best.name, best.score);

int main(int argc, char *argv[]){

  if(argc < 2){
    printf("usage: %s <filename>\n", argv[0]);
    printf("<filename> should have columns of names, numbers as in\n");
    printf("Darlene 91.0\n");
    printf("Angela  76.5\n");
    printf("Elliot  94.5\n");
    printf("Tyrell  87.5\n");
    printf("Dom     70.0\n");
    printf("Phillip 55.5\n");
    return 1;
  }

  FILE *fh = fopen(argv[1],"r");

  grade_t *best = malloc(sizeof(grade_t));
  best->score=0;
  

  grade_t *curr = malloc(sizeof(grade_t));
  while (fscanf(fh,"%s %lf\n",curr->name,&curr->score) != EOF) {
    if (curr->score > best->score) {
      best->score = curr->score;
      strcpy(best->name,curr->name);
    }
  }

  printf("Best score: %s %f\n",best->name,best->score);

  free(best);
  free(curr);
  fclose(fh);

  return 0;
}
