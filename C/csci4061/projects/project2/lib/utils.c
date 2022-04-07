#include "../include/utils.h"
#include <stdio.h>
#include <string.h>

#define wordSize 128
#define mapperMsgKey 69
#define reducerMsgKey 70
#define masterTag 99999

char *getChunkData(int mapperID) {
  // message struct
  struct msgBuffer message;
  // open message queue
  int msqid = msgget(mapperMsgKey, 0666);
  // error checking
  if (msqid == -1) {
    perror("ERROR: msgget failed");
    return NULL;
  }

  // receive chunk from master
  int len = msgrcv(msqid, &message, MSGSIZE, mapperID, 0);
  if (len == -1) {
    // report error if receive fails
    perror("ERROR: msgrcv failed");
    return NULL;
  }

  // check for end message
  if (strcmp(message.msgText, "END") == 0) {
    message.msgType = masterTag;
    strcpy(message.msgText, "ACK");
    // send ACK to master
    if (msgsnd(msqid, &message, strlen(message.msgText) + 1, 0) == -1) {
      // report error if send fails
      perror("ERROR: msgsnd failed");
      return NULL;
    }
    // return null if END received
    return NULL;
  }

  // the buffer containing our actual message, program calling this function
  // frees the memory, so we don't need to worry about this
  char *chunk = (char *)malloc(strlen(message.msgText));
  strcpy(chunk, message.msgText);
  // return message
  return chunk;
}

// Return the next word as an output parameter.
// Return 1: it reads a word. Return 0: it reaches the end of the
// stream.
int getNextWord(int fd, char *buffer) {
  char word[100];
  memset(word, '\0', 100);
  int i = 0;
  while (read(fd, &word[i], 1) == 1) {
    if (word[i] == ' ' || word[i] == '\n' || word[i] == '\t') {
      strcpy(buffer, word);
      word[i + 1] = '\0';
      return 1;
    }
    if (word[i] == 0x0) {
      break;
    }
    i++;
  }
  strcpy(buffer, word);
  return 0;
}

void sendChunkData(char *inputFile, int nMappers) {
  // message struct
  struct msgBuffer message;
  // the id of the queue
  int msqid = 0;
  // the buffer containing our actual message
  char chunk[chunkSize];
  memset(chunk, '\0', chunkSize);
  // containes next word in file
  char word[wordSize];
  memset(chunk, '\0', wordSize);
  // file descriptor
  int fd;
  // check if file opens properly
  if ((fd = open(inputFile, O_RDONLY)) == -1) {
    perror("ERROR: failed to open file");
    return;
  }
  // current mapper we're going to send our message to
  int mapperNum = 1;

  // create the message queue
  msqid = msgget(mapperMsgKey, IPC_CREAT | 0666);
  // error checking
  if (msqid == -1) {
    perror("ERROR: msgget failed");
    return;
  }

  while (getNextWord(fd, word)) {
    // if chunk is full
    if (strlen(word) + strlen(chunk) > chunkSize) {
      // copy chunk into our message struct
      strcpy(message.msgText, chunk);
      message.msgText[strlen(chunk)] = '\0';
      // assign our mapper number
      message.msgType = mapperNum;
      // send message to message queue
      if (msgsnd(msqid, &message, strlen(message.msgText) + 1, 0) == -1) {
        // report error if send fails
        perror("ERROR: msgsnd failed");
        break;
      }
      // increment mapperNum to send message to new mapper.  If mapperNum is
      // nMappers, then we're at the last mapper, so circle back to 1
      if (mapperNum == nMappers) {
        mapperNum = 1;
      } else {
        mapperNum++;
      }
      // reset the chunk for next mapper
      memset(chunk, '\0', chunkSize);
      strcpy(chunk, word);
    } else {
      strcat(chunk, word);
    }
  }

  // last buffer write
  if (strlen(chunk) > 0) {
    strcpy(message.msgText, chunk);
    message.msgType = mapperNum;
    if (msgsnd(msqid, &message, strlen(message.msgText) + 1, 0) == -1) {
      perror("ERROR: msgsnd failed");
    }
  }

  // copy END message into buffer
  strcpy(message.msgText, "END");
  mapperNum = 1;
  while (mapperNum <= nMappers) {
    // assign type to mapper num
    message.msgType = mapperNum;
    // send END message to mappers
    if (msgsnd(msqid, &message, strlen(message.msgText) + 1, 0) == -1) {
      // report error if send fails
      perror("ERROR: msgsnd failed");
      break;
    }
    mapperNum++;
  }

  mapperNum = 1;
  while (mapperNum <= nMappers) {
    // assign mepperNum to type
    message.msgType = mapperNum;
    // wait to receive ACK message from mappers
    int len = msgrcv(msqid, &message, MSGSIZE, masterTag, 0);
    if (len == -1) {
      // report error if receive fails
      perror("ERROR: msgrcv failed");
      break;
    }

    // check to see if ACK was sent from mappers
    // if ACK sent, move to next mapper, otherwise loop back
    if (strcmp(message.msgText, "ACK") == 0) {
      mapperNum++;
    }
  }
  // delete message queue
  msgctl(msqid, IPC_RMID, NULL);
  // close file
  close(fd);
}

// hash function to divide the list of word.txt files across reducers
// http://www.cse.yorku.ca/~oz/hash.html
int hashFunction(char *key, int reducers) {
  unsigned long hash = 0;
  int c;

  while ((c = *key++) != '\0')
    hash = c + (hash << 6) + (hash << 16) - hash;

  return (hash % reducers);
}

int getInterData(char *key, int reducerID) {
  // message struct
  struct msgBuffer message;
  // open message queue
  int msqid = msgget(reducerMsgKey, 0666);
  // error checking
  if (msqid == -1) {
    perror("ERROR: msgget failed");
    return -1;
  }

  // receive chunk from master
  int len = msgrcv(msqid, &message, MSGSIZE, reducerID, 0);
  if (len == -1) {
    // report error if receive fails
    perror("ERROR: msgrcv failed");
    return -1;
  }

  // check for end message
  if (strcmp(message.msgText, "END") == 0) {
    message.msgType = masterTag;
    strcpy(message.msgText, "ACK");
    // send ACK to master
    if (msgsnd(msqid, &message, strlen(message.msgText) + 1, 0) == -1) {
      // report error if send fails
      perror("ERROR: msgsnd failed");
      return -1;
    }
    // return 0 if END received
    return 0;
  }

  // coppy file path into key
  strcpy(key, message.msgText);

  // if no END message recieved, then return 1
  return 1;
}

void shuffle(int nMappers, int nReducers) {
  // message struct
  struct msgBuffer message;
  // open message queue
  int msqid = msgget(reducerMsgKey, IPC_CREAT | 0666);
  // error checking
  if (msqid == -1) {
    perror("ERROR: msgget failed");
    return;
  }

  // traverse the directory of each Mapper and send the word filepath to the
  // reducers
  for (int i = 1; i <= nMappers; i++) {
    // retreive path to mapper directory (DYNAMIC, so we must free later)
    char *mapDirPath = createMapDir(i);

    // create directory object
    DIR *mapDir = opendir(mapDirPath);
    if (mapDir == NULL) {
      perror("ERROR: path passed is invalid");
      return;
    }
    // current file in directory
    struct dirent *file;
    // go until we've checked every file in the directory
    while ((file = readdir(mapDir)) != NULL) {
      // make sure it's a regular word file
      if (file->d_type == DT_REG) {
        // clear out message buffer
        memset(message.msgText, '\0', MSGSIZE);
        // set message text to file path
        strcpy(message.msgText, mapDirPath);
        strcat(message.msgText, "/");
        strcat(message.msgText, file->d_name);
        // set message type to reducer ID from hash function
        message.msgType = hashFunction(file->d_name, nReducers) + 1;
        // send message
        if (msgsnd(msqid, &message, strlen(message.msgText) + 1, 0) == -1) {
          // report error if send fails
          perror("ERROR: msgsnd failed");
          break;
        }
      }
    }

    // free dynamically allocated mapper directory path
    free(mapDirPath);
    // close mapper directory once we've sent our message
    closedir(mapDir);
  }

  // copy END message into buffer
  strcpy(message.msgText, "END");
  for (int j = 1; j <= nReducers; j++) {
    // assign type to reducer ID
    message.msgType = j;
    // send END message to mappers
    if (msgsnd(msqid, &message, strlen(message.msgText) + 1, 0) == -1) {
      // report error if send fails
      perror("ERROR: msgsnd failed");
      break;
    }
  }

  for (int k = 1; k <= nReducers; k++) {
    // assign type to reducer ID
    message.msgType = k;
    // wait to receive ACK message from reducers
    int len = msgrcv(msqid, &message, MSGSIZE, masterTag, 0);
    if (len == -1) {
      // report error if receive fails
      perror("ERROR: msgrcv failed");
      break;
    }

    // check to see if ACK was sent from reducers
    // if ACK sent, move to next reducer, otherwise loop back
    if (strcmp(message.msgText, "ACK") != 0) {
      k--;
    }
  }

  // delete message queue
  msgctl(msqid, IPC_RMID, NULL);
}

// check if the character is valid for a word
int validChar(char c) {
  return (tolower(c) >= 'a' && tolower(c) <= 'z') || (c >= '0' && c <= '9');
}

char *getWord(char *chunk, int *i) {
  char *buffer = (char *)malloc(sizeof(char) * chunkSize);
  memset(buffer, '\0', chunkSize);
  int j = 0;
  while ((*i) < strlen(chunk)) {
    // read a single word at a time from chunk
    if (chunk[(*i)] == '\n' || chunk[(*i)] == ' ' || !validChar(chunk[(*i)]) ||
        chunk[(*i)] == 0x0) {
      buffer[j] = '\0';
      if (strlen(buffer) > 0) {
        (*i)++;
        return buffer;
      }
      j = 0;
      (*i)++;
      continue;
    }
    buffer[j] = chunk[(*i)];
    j++;
    (*i)++;
  }
  if (strlen(buffer) > 0)
    return buffer;
  return NULL;
}

void createOutputDir() {
  mkdir("output", ACCESSPERMS);
  mkdir("output/MapOut", ACCESSPERMS);
  mkdir("output/ReduceOut", ACCESSPERMS);
}

char *createMapDir(int mapperID) {
  char *dirName = (char *)malloc(sizeof(char) * 100);
  memset(dirName, '\0', 100);
  sprintf(dirName, "output/MapOut/Map_%d", mapperID);
  mkdir(dirName, ACCESSPERMS);
  return dirName;
}

void removeOutputDir() {
  pid_t pid = fork();
  if (pid == 0) {
    char *argv[] = {"rm", "-rf", "output", NULL};
    if (execvp(*argv, argv) < 0) {
      printf("ERROR: exec failed\n");
      exit(1);
    }
    exit(0);
  } else {
    wait(NULL);
  }
}

void bookeepingCode() {
  removeOutputDir();
  sleep(1);
  createOutputDir();
}
