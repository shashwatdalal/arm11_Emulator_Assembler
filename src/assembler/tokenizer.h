#ifndef ARM11_38_TOKENIZER_H
#define ARM11_38_TOKENIZER_H

// Imported Files
#include "map.h"
#include "linked_list.h"

// Methods
inst_t* tokenize(char *currentInstruction, int address,
          st_t *symbolTable, llist_t *constantValues);

#endif //ARM11_38_TOKENIZER_H
