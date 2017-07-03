#ifndef UTIL_H
#define UTIL_H

// Imported Files
#include "definitions.h"

// Methods
state_t *newState(void);
void deleteState(state_t *state);
void setCPSRFlags(state_t *state, uint8_t value, char flag);
uint32_t getBits(uint32_t instruction, int startingIndex, int length);
uint8_t obtainFourBitsAtLSB(uint32_t instruction, uint8_t LSB);
uint32_t readWordAtMSB(state_t *state, uint32_t location);
void writeWordAtMSB(state_t *state, uint32_t location, uint32_t word);
uint32_t shift(uint32_t value, uint32_t shiftDegree, uint32_t shiftType);

#endif
