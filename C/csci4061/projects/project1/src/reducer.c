#include "../include/reducer.h"
#include <stdio.h>
#define FILE_SIZE 260

// create a key value node
finalKeyValueDS *createFinalKeyValueNode(char *word, int count) {
  finalKeyValueDS *newNode = (finalKeyValueDS *)malloc(sizeof(finalKeyValueDS));
  strcpy(newNode->key, word);
  newNode->value = count;
  newNode->next = NULL;
  return newNode;
}

// insert or update an key value
finalKeyValueDS *insertNewKeyValue(finalKeyValueDS *root, char *word,
                                   int count) {
  finalKeyValueDS *tempNode = root;
  if (root == NULL)
    return createFinalKeyValueNode(word, count);
  while (tempNode->next != NULL) {
    if (strcmp(tempNode->key, word) == 0) {
      tempNode->value += count;
      return root;
    }
    tempNode = tempNode->next;
  }
  if (strcmp(tempNode->key, word) == 0) {
    tempNode->value += count;
  } else {
    tempNode->next = createFinalKeyValueNode(word, count);
  }
  return root;
}

// free the DS after usage. Call this once you are done with the writing of DS
// into file
void freeFinalDS(finalKeyValueDS *root) {
  if (root == NULL)
    return;

  finalKeyValueDS *tempNode = root->next;
  ;
  while (tempNode != NULL) {
    free(root);
    root = tempNode;
    tempNode = tempNode->next;
  }
}

// reduce function
void reduce(char *key) {
  // open inputted file
  FILE *fd = fopen(key, "r");
  // try to read whole file into chunkData buffer, otherwise do a 1025 byte
  // chunk
  char chunkData[chunkSize];
  // placeholder for our actual word
  char *word;
  // variable representing # of occurrences of our word
  int count = 0;

  // read file into chunkData (loop if there's more than 1024 bytes)
  while (fread(chunkData, 1, chunkSize, fd) != 0) {
    int i = 0;
    char *buffer;
    int firstWord = 1;
    // read buffer word by word
    while ((buffer = getWord(chunkData, &i)) != NULL) {
      // if we're at the first word, then it's our actual word, and not numbers
      if (firstWord) {
        word = buffer;
        firstWord = 0;
      } else
        // otherwise, convert the string into an integer and add it to our count
        count += atoi(buffer);
    }
  }
  // once we've gone through the whole file, we can update our key value pair
  words = insertNewKeyValue(words, word, count);
}

// write the contents of the final intermediate structure
// to output/ReduceOut/Reduce_reducerID.txt
void writeFinalDS(int reducerID) {

  char filename[FILE_SIZE];
  sprintf(filename, "output/ReduceOut/Reduce_%d.txt", reducerID);
  FILE *fd = fopen(filename, "w");
  for (finalKeyValueDS *word = words; word != NULL; word = word->next) {
    fprintf(fd, "%s %d\n", word->key, word->value);
  }
  fclose(fd);
  freeFinalDS(words);
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Less number of arguments.\n");
    printf("./reducer reducerID");
  }

  // ###### DO NOT REMOVE ######
  // initialize
  int reducerID = strtol(argv[1], NULL, 10);

  // Print statement for reducer, comment this for final submission
  // printf("Reducer id : %d \n", reducerID);

  // ###### DO NOT REMOVE ######
  // master will continuously send the word.txt files
  // alloted to the reducer
  char key[MAXKEYSZ];

  while (getInterData(key, reducerID))
    reduce(key);

  // You may write this logic. You can somehow store the
  // <key, value> count and write to Reduce_reducerID.txt file
  // So you may delete this function and add your logic
  writeFinalDS(reducerID);

  return 0;
}
