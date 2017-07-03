#ifndef ARM11_38_MULTIPLY_H
#define ARM11_38_MULTIPLY_H

// Imported Files
#include "util.h"

// Constant Files
#define DEFAULT_MUL_CODE (0xE << 28) + (0x9 << 4)

// Methods
uint32_t assembleMUL(inst_t *instruction);
uint32_t assembleMLA(inst_t *instruction);

#endif //ARM11_38_MULTIPLY_H
