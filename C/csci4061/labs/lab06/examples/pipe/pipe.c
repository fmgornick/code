#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
   
   int pipefds[2];
   char writemessage[20]={"Hello world!"};
   char readmessage[20];
   
   
   if (pipe(pipefds) == -1) {
      printf("Unable to create pipe\n");
      return 1;
   }
   
   printf("Writing to pipe - %s\n", writemessage);
   if(write(pipefds[1], writemessage, sizeof(writemessage)) < 0){
      perror("Bad write \n");
      exit(1);
   }

   if(read(pipefds[0], readmessage, sizeof(readmessage)) < 0 ){
      perror("Bad read \n");
      exit(1);
   }

   printf("Read from pipe – Message is %s\n", readmessage);

   return 0;
}
