#ifndef ARM11_38_IO_H
#define ARM11_38_IO_H

// Imported Files
#include "linked_list.h"
#include "map.h"
#include "util.h"

// Methods
void printOutput(uint32_t *outputArray, llist_t *constantValues,
          char *outputFileName, uint32_t numOfInstructions);
llist_t *readSourceAndBuildSymbolTable(char *fileName, st_t *symbolTable);

#endif //ARM11_38_IO_H
