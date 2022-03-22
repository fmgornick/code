#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHMSZ     100

int main(int argc, char * argv[])
{   char c;
    int shmid;
    key_t key;
    char *shm,*s;
    
    //key of the shared memory
    key = 5678;
    
    //Create the segment.
    if((shmid=shmget(key,SHMSZ,IPC_CREAT|0666))<0){
        perror("shmid error");
    }
    
    //attach the shared memory
    if ((shm=shmat(shmid,NULL,0))==(char *)-1){
        perror("shmat");
    }
    
    //write something into the shared memory, you can use strcpy
    s=shm;
    for(c='a';c<='z';c++)
        *s++=c;
    *s=NULL;
    
    
    //waiting for the content to be read
    printf("waiting for the client to read...\n");
    while(*shm!='*')
        sleep(1);
    
    return 0;     
}

