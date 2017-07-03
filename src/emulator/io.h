#ifndef IO_H
#define IO_H

// Imported Files
#include "util.h"

// Constant Values
#define LOWEST_DOUBLE_DIGIT 10

// Methods
void printState(state_t *state);
int readBinaryIntoMem(state_t *state, char *fileName);

#endif
