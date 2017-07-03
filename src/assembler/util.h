#ifndef ARM11_38_UTIL_H
#define ARM11_38_UTIL_H

// Imported Files
#include "definitions.h"
#include "data_processing.h"
#include "branch.h"
#include "multiply.h"
#include "single_data_transfer.h"
#include "special.h"

// Methods
ft_t *populateFunctionTable(void);
uint32_t *initOutputArray(int size);
void freeOutputArray(uint32_t *array);
uint8_t getRegAddr (char *string);

#endif //ARM11_38_UTIL_H
