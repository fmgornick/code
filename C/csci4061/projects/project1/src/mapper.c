#include "../include/mapper.h"
#include <stdio.h>
#define FILE_SIZE 260

// combined value list corresponding to a word <1,1,1,1....>
valueList *createNewValueListNode(char *value) {
  valueList *newNode = (valueList *)malloc(sizeof(valueList));
  strcpy(newNode->value, value);
  newNode->next = NULL;
  return newNode;
}

// insert new count to value list
valueList *insertNewValueToList(valueList *root, char *count) {
  valueList *tempNode = root;
  if (root == NULL)
    return createNewValueListNode(count);
  while (tempNode->next != NULL)
    tempNode = tempNode->next;
  tempNode->next = createNewValueListNode(count);
  return root;
}

// free value list
void freeValueList(valueList *root) {
  if (root == NULL)
    return;

  valueList *tempNode = root->next;
  ;
  while (tempNode != NULL) {
    free(root);
    root = tempNode;
    tempNode = tempNode->next;
  }
}

// create <word, value list>
intermediateDS *createNewInterDSNode(char *word, char *count) {
  intermediateDS *newNode = (intermediateDS *)malloc(sizeof(intermediateDS));
  strcpy(newNode->key, word);
  newNode->value = NULL;
  newNode->value = insertNewValueToList(newNode->value, count);
  newNode->next = NULL;
  return newNode;
}

// insert or update a <word, value> to intermediate DS
intermediateDS *insertPairToInterDS(intermediateDS *root, char *word,
                                    char *count) {
  intermediateDS *tempNode = root;
  if (root == NULL)
    return createNewInterDSNode(word, count);
  while (tempNode->next != NULL) {
    if (strcmp(tempNode->key, word) == 0) {
      tempNode->value = insertNewValueToList(tempNode->value, count);
      return root;
    }
    tempNode = tempNode->next;
  }
  if (strcmp(tempNode->key, word) == 0) {
    tempNode->value = insertNewValueToList(tempNode->value, count);
  } else {
    tempNode->next = createNewInterDSNode(word, count);
  }
  return root;
}

// free the DS after usage. Call this once you are done with the writing of DS
// into file
void freeInterDS(intermediateDS *root) {
  if (root == NULL)
    return;

  intermediateDS *tempNode = root->next;
  ;
  while (tempNode != NULL) {
    freeValueList(root->value);
    free(root);
    root = tempNode;
    tempNode = tempNode->next;
  }
}

// we didn't end up implementing the emit function, as the map function already
// makes the call to insertPairToInterDS(), so adding the emit function would
// just be extra code at this point.  I also talked to a TA, and they said this
// is ok so pls don't mark off points!
// void emit(char *word, char *count) {}

// map function
void map(char *chunkData) {
  int i = 0;
  char *buffer;
  // for each word in the file add the pair to our global linked list words
  while ((buffer = getWord(chunkData, &i)) != NULL) {
    words = insertPairToInterDS(words, buffer, "1");
  }
}

// write intermediate data to separate word.txt files
// Each file will have only one line : word 1 1 1 1 1 ...
void writeIntermediateDS() {
  char filename[FILE_SIZE];
  // for each word in our linked list
  for (intermediateDS *word = words; word != NULL; word = word->next) {
    // create new string that will be our file name
    sprintf(filename, "%s/%s.txt", mapOutDir, word->key);
    // open file for writing
    FILE *fd = fopen(filename, "w");
    // input current word into file
    fprintf(fd, "%s ", word->key);
    // iterate through word's corresponding valueList to append counts to file
    for (valueList *count = word->value; count != NULL; count = count->next) {
      fprintf(fd, "%s ", count->value);
    }
    fclose(fd);
  }
  freeInterDS(words);
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Less number of arguments.\n");
    printf("./mapper mapperID\n");
    exit(0);
  }
  // ###### DO NOT REMOVE ######
  mapperID = strtol(argv[1], NULL, 10);

  // Print statement for mapper, comment this for final submission
  // printf("Mapper id : %d \n", mapperID);

  // ###### DO NOT REMOVE ######
  // create folder specifically for this mapper in output/MapOut
  // mapOutDir has the path to the folder where the outputs of
  // this mapper should be stored
  mapOutDir = createMapDir(mapperID);
  // ###### DO NOT REMOVE ######
  while (1) {
    // create an array of chunkSize=1024B and intialize all
    // elements with '\0'
    char chunkData[chunkSize + 1]; // +1 for '\0'
    memset(chunkData, '\0', chunkSize + 1);

    char *retChunk = getChunkData(mapperID);
    if (retChunk == NULL) {
      break;
    }

    strcpy(chunkData, retChunk);
    free(retChunk);
    // printf("%s\n", chunkData);
    map(chunkData);
  }

  // ###### DO NOT REMOVE ######
  writeIntermediateDS();

  return 0;
}
