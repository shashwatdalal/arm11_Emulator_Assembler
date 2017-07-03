#ifndef ARM11_38_SPECIAL_H
#define ARM11_38_SPECIAL_H

// Imported files
#include "data_processing.h"
#include "definitions.h"

// Methods
uint32_t assembleLSL(inst_t* instruction);
uint32_t assembleANDEQ(inst_t *instruction);

#endif //ARM11_38_SPECIAL_H
