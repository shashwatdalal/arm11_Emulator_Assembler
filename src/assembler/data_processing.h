#ifndef ARM11_38_DATA_PROCESSING_H
#define ARM11_38_DATA_PROCESSING_H

// Imported Files
#include "util.h"

// Methods
uint32_t assembleADD(inst_t *instruction);
uint32_t assembleSUB(inst_t *instruction);
uint32_t assembleRSB(inst_t *instruction);
uint32_t assembleAND(inst_t *instruction);
uint32_t assembleEOR(inst_t *instruction);
uint32_t assembleORR(inst_t *instruction);
uint32_t assembleMOV(inst_t *instruction);
uint32_t assembleTST(inst_t *instruction);
uint32_t assembleTEQ(inst_t *instruction);
uint32_t assembleCMP(inst_t *instruction);
uint16_t getOperand2WithShift(char *arg1, char *arg2);

#endif //ARM11_38_DATA_PROCESSING_H
