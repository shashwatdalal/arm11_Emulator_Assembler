#include "io.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 69
#define BYTES_IN_WORD 4
#define BINARY_SIZE 40
#define MAX_NUMBER_OF_INSTRUCTIONS 100

void printOutput(uint32_t *outputArray, llist_t *constantValues,
          char *outputFileName, uint32_t numOfInstructions) {
  FILE *fileptr;
  fileptr = fopen(outputFileName, "wb+");
  fwrite(outputArray, sizeof(uint32_t), numOfInstructions, fileptr);
  int size = constantValues->size;
  for (int i = 0; i < size; i++) {
    void *constValPtr = llistPop(constantValues);
    fwrite(constValPtr, sizeof(uint32_t), 1, fileptr);
    free(constValPtr);
  }
  fclose(fileptr);
}

int hasLabel(char *buffer) {
  return buffer[strlen(buffer) - 1] == ':';
}

char *getLabel(char *buffer) {
  buffer[strlen(buffer) - 1] = 0;
  return buffer;
}

llist_t *readSourceAndBuildSymbolTable(char *fileName, st_t *symbolTable) {
  FILE *file = fopen(fileName, "r");
  char *buffer[MAX_NUMBER_OF_INSTRUCTIONS];
  if (file == NULL) {
    perror("Unable to open file");
    return NULL;
  }
  llist_t *listOfInstructions = initLinkedList();
  uint32_t address = 0;
  int i = 0;
  buffer[0] = malloc(sizeof(char) * BUFFER_SIZE);
  while (fgets(buffer[i], BUFFER_SIZE, file) != NULL) {
    buffer[i][strlen(buffer[i]) - 1] = 0;
    if (hasLabel(buffer[i])) {
      stPut(symbolTable, getLabel(buffer[i]), address);
    } else if (strlen(buffer[i]) > 0) {
      llistEnqueue(listOfInstructions, (void *) buffer[i]);
      address += BYTES_IN_WORD;
    }
    i++;
    buffer[i] = malloc(sizeof(char) * BUFFER_SIZE);
  }
  fclose(file);
  return listOfInstructions;
}
