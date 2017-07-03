#ifndef ASSEMBLE_C
#define ASSEMBLE_C

// Imported Files
#include "io.h"
#include "tokenizer.h"

// Methods
// Main executable method of the assembler
int main(int argc, char **argv) {
  // Initialization of data types
  ft_t *functionTable = populateFunctionTable();
  st_t *symbolTable = initSymbolTable();
  llist_t *constantValues = initLinkedList();

  // First iteration
  char *inputFileName = *(argv + 1);
  llist_t *instructionList
          = readSourceAndBuildSymbolTable(inputFileName, symbolTable);

  // Second iteration
  int size = instructionList->size;
  uint32_t *outputArray = initOutputArray(size);
  for (uint32_t i = 0; i < size; i++) {
    inst_t *instruction
           = tokenize((char*)llistPop(instructionList),
                      4 * i, symbolTable, constantValues);
    instruction->numOfInstructions = size;

    uint32_t currentBinary
           = ftGet(functionTable, instruction->opcode)(instruction);
    outputArray[i] = currentBinary;
    free(instruction);
  }
  char *outputFileName = *(argv + 2);
  printOutput(outputArray, constantValues, outputFileName, size);

  // Free memory
  freeOutputArray(outputArray);
  freeFunctionTable(functionTable);
  freeSymbolTable(symbolTable);
  freeLinkedList(instructionList);
  freeLinkedList(constantValues);
}

#endif
