#ifndef ARM11_38_SINGLE_DATA_TRANSFER_H
#define ARM11_38_SINGLE_DATA_TRANSFER_H

// Imported Files
#include "data_processing.h"
#include "linked_list.h"

// Constant Values
#define PC 15

// Methods
uint32_t assembleLDR(inst_t *instruction);
uint32_t assembleSTR(inst_t *instruction);

#endif //ARM11_38_SINGLE_DATA_TRANSFER_H
