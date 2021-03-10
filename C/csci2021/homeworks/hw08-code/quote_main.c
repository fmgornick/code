#include <string.h>
#include <stdio.h>

// Defined in list_data.c
int max_size();
char *get_it(int i);

char *correct = "C++ makes it harder, but when you do, it blows away your whole leg.";

int main(){
  printf("Complete this sentence by C++ creator Bjarne Stroustrup:\n");
  printf("C makes it easy to shoot yourself in the foot; ...\n");
  printf("\n");
  printf("enter a number from 0 to %d: ",max_size());
  int index = 0;
  int res = scanf("%d",&index);
  printf("\n");
  if(res != 1){
    printf("No, no: enter a NUMBER\n");
    return 1;
  }
  char *selected = get_it(index);
  printf("%d: %s\n",index,selected);
  int diff = strcmp(selected,correct);
  printf("\n");
  if(diff == 0){
    printf("Correct!\n");
  }
  else{
    printf("Have a nice tall glass of ... NOPE.\n");
  }
  return 0;
}

