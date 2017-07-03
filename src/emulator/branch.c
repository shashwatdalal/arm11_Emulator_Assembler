// Imported Files
#include "branch.h"

// Methods
// Changes the value of the PC register
void branch_execute(state_t* state, uint32_t instruction) {
  uint32_t offset = (instruction & OFFSET_MASK) << 2;
  if (offset >> (OFFSET_SIZE - 1) == 1) {
    // Offset is negative
    offset += SIGN_EXTENSION_MASK;
  }
  state->registers[PC] += offset - PIPELINE_OFFSET;
  state->isJump = 1;
}
