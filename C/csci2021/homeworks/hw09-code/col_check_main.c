#include <stdio.h>

typedef struct{
  int cur;
  int step;
} colinfo_t;

int col_check(colinfo_t info);

int main(){
  int err;
  colinfo_t info;

  info.cur=5; info.step=7;
  err = col_check(info);
  printf("info{cur: %2d, step: %2d}, err = 0x%x\n",
         info.cur,info.step,err);
    

  info.cur=0; info.step=3;
  err = col_check(info);
  printf("info{cur: %2d, step: %2d}, err = 0x%x\n",
         info.cur,info.step,err);

  info.cur=7; info.step=0;
  err = col_check(info);
  printf("info{cur: %2d, step: %2d}, err = 0x%x\n",
         info.cur,info.step,err);

  info.cur=7; info.step=-2;
  err = col_check(info);
  printf("info{cur: %2d, step: %2d}, err = 0x%x\n",
         info.cur,info.step,err);

  info.cur=0; info.step=-2;
  err = col_check(info);
  printf("info{cur: %2d, step: %2d}, err = 0x%x\n",
         info.cur,info.step,err);

  info.cur=1; info.step=6;
  err = col_check(info);
  printf("info{cur: %2d, step: %2d}, err = 0x%x\n",
         info.cur,info.step,err);

  info.cur=1; info.step=0;
  err = col_check(info);
  printf("info{cur: %2d, step: %2d}, err = 0x%x\n",
         info.cur,info.step,err);

  info.cur=1; info.step=-4;
  err = col_check(info);
  printf("info{cur: %2d, step: %2d}, err = 0x%x\n",
         info.cur,info.step,err);

  return 0;
}
