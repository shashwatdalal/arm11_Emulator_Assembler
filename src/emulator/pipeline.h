#ifndef PIPELINE_H
#define PIPELINE_H

// Imported Files
#include "io.h"
#include "branch.h"
#include "data_processing.h"
#include "multiply.h"
#include "single_data_transfer.h"

// Methods
uint32_t fetch(state_t *state);
void incrementPC(state_t *state);
inst_t decode(state_t *state, uint32_t instruction);
void execute(state_t *state, uint32_t instruction, inst_t instructionType);

#endif
