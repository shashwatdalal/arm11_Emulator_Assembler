#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

// Imported Files
#include "util.h"

// Constant Values
#define ROTATE_RIGHT_OP 3

// Opcode Enumeration
enum opcode {
  AND = 0,
  EOR = 1,
  SUB = 2,
  RSB = 3,
  ADD = 4,
  TST = 8,
  TEQ = 9,
  CMP = 10,
  ORR = 12,
  MOV = 13,
};

// Methods
void data_processing_execute(state_t *state, uint32_t instruction);

#endif
