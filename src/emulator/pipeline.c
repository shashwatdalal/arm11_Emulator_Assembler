// Imported Files
#include "pipeline.h"

// Methods
// Checks the 'cond' bits to see if the instruction can be executed
bool correctCondition(uint8_t flags, uint8_t cond) {
  switch (cond) {
    case AL:
      return true;
    case EQ:
      return ((0x04 & flags) == 0x04);
    case NE:
      return ((0x04 & flags) == 0);
    case GE:
      return ((0x09 & flags) == 0) || ((0x09 & flags) == 9);
    case LT:
      return !correctCondition(flags, GE);
    case GT:
      return ((0x04 & flags) == 0) && correctCondition(flags, GE);
    case LE:
      return correctCondition(flags, EQ) || !correctCondition(flags, GE);
    default:
      perror("cond invalid @ \"pipeline.c\".correctCondition\n");
      return false;
  }
}

// Fetch the instruction located at the PC register value
uint32_t fetch(state_t *state) {
  return readWordAtMSB(state, state->registers[PC]);
}

// Increment the PC register
void incrementPC(state_t *state) {
  state->registers[PC] += BYTES_IN_WORD;
}

// Decode an instruction
inst_t decode(state_t *state, uint32_t instruction) {
  uint32_t mask = 0x0fc00060;
  if ((instruction & mask) == 0
          && ((1 << 4) & instruction) != 0
          && ((1 << 7) & instruction) != 0) {
    return MULTIPLY;
  }
  mask = 1 << 26;
  if ((instruction & mask) != 0
          && (instruction & (mask << 1)) == 0) {
    return SINGLE_DATA_TRANSFER;
  }
  mask = 1 << 25;
  if ((instruction & mask) != 0
          && (instruction & (mask << 1)) == 0
          && (instruction & (mask << 2)) != 0) {
    return BRANCH;
  }
  return DATA_PROCESSING;
}

// Execute an instruction
void execute(state_t *state, uint32_t instruction, inst_t instructionType) {
  uint8_t flags = (state->registers[CPSR]) >> 28;
  uint8_t cond = instruction >> 28;
  if (correctCondition(flags, cond)) {
    switch (instructionType) {
      case DATA_PROCESSING:
        data_processing_execute(state, instruction);
        break;
      case MULTIPLY:
        multiply_execute(state, instruction);
        break;
      case SINGLE_DATA_TRANSFER:
        single_data_transfer_execute(state, instruction);
        break;
      case BRANCH:
        branch_execute(state, instruction);
        break;
    }
  }
}
