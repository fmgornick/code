#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#define MSGSIZE 128

#define key 4061
int send(void);

struct my_msgbuf {
  long mtype;
  char mtext[MSGSIZE];
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Need a parameter 's' or 'r'.\n");
    return -1;
  }

  struct my_msgbuf buf;
  int msqid = 0;
  char szTemp[1024];

  // connect to the queue

  if (strcmp(argv[1], "s") == 0) {
    printf("I will create message queue and keep sending messages.\n");
    msqid = msgget(key, IPC_CREAT | 0666);

    if (msqid == -1) {
      perror("msgget: msgget failed");
      return -1;
    }

    printf("Message queueid : %d\n", msqid);

    while (1) {
      printf("Input message : ");
      scanf("%s", szTemp);

      buf.mtype = 1;
      strcpy(buf.mtext, szTemp);
      buf.mtext[strlen(szTemp)] = '\0';

      if (msgsnd(msqid, &buf, sizeof(struct my_msgbuf), 0) == -1) {
        perror("msgop: msgsnd failed");
        break;
      }
    }
  } else if (strcmp(argv[1], "r") == 0) {
    int nReadByte = 0;

    printf("I will open message queue and keep reading messages.\n");
    msqid = msgget(key, 0666);

    if (msqid == -1) {
      printf("there is no available queue for now\n");
    } else {
      while (1) {
        nReadByte = msgrcv(msqid, &buf, sizeof(struct my_msgbuf), 1, 0);
        if (nReadByte == -1) {
          break;
        }

        buf.mtext[nReadByte] = '\0';
        printf("Got message: %s\n", buf.mtext);
      }
    }
  } else {
    printf("Parameter should be 's' or 'r'.\n");
  }

  msgctl(msqid, IPC_RMID, NULL);
  return 0;
}
