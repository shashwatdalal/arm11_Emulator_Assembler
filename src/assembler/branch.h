#ifndef ARM11_38_BRANCH_H
#define ARM11_38_BRANCH_H

// Imported Files
#include "map.h"

// Constant Values
#define DEFAULT_BRANCH_CODE (0xA << 24)
#define PIPELINE_OFFSET -8

// Methods
uint32_t assembleBEQ(inst_t *instruction);
uint32_t assembleBNE(inst_t *instruction);
uint32_t assembleBGE(inst_t *instruction);
uint32_t assembleBLT(inst_t *instruction);
uint32_t assembleBGT(inst_t *instruction);
uint32_t assembleBLE(inst_t *instruction);
uint32_t assembleB(inst_t *instruction);
uint32_t computeOffset(inst_t *instruction);

#endif //ARM11_38_BRANCH_H
