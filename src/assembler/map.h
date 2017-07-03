#ifndef ARM11_38_MAP_H
#define ARM11_38_MAP_H

// Imported Files
#include "definitions.h"

// Function Table Methods
ft_t *initFunctionTable(void);
void freeFunctionTable(ft_t *map);
void ftPut(ft_t *map, char *key, functionPtr value);
functionPtr ftGet(ft_t *map, char *key);

// Symbol Table Methods
st_t *initSymbolTable(void);
void freeSymbolTable(st_t *map);
void stPut(st_t *map, char *key, uint32_t value);
uint32_t stGet(st_t *map, char *key);

#endif //ARM11_38_MAP_H
