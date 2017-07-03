// Imported Files
#include "multiply.h"

// Methods
// Multiply the values specified by the instruction
void multiply_execute(state_t *state,uint32_t instruction) {
  // Get register values
  uint32_t rd = getBits(instruction, RD, NUM_REG_BITS);
  uint32_t rn = getBits(instruction, RN, NUM_REG_BITS);
  uint32_t rs = getBits(instruction, RS, NUM_REG_BITS);
  uint32_t rm = getBits(instruction, RM, NUM_REG_BITS);

  // R[rd] = R[rm] * R[rs] (+ R[rn])
  state->registers[rd] = state->registers[rm] * state->registers[rs] +
          (getBits(instruction, ACCUMULATE, 1) == 1)
          * state->registers[rn];

  // Set CPSR flags if the 'set' bit is 1
  if (getBits(instruction, SET, 1) == 1) {
    setCPSRFlags(state, getBits(state->registers[rd], SIGNBIT, 1), 'N');
    setCPSRFlags(state, (state->registers[rd] == 0), 'Z');
  }
}
