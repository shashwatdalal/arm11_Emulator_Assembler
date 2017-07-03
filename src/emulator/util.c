// Imported Files
#include "util.h"

// Methods
// Create a new state for the emulator
state_t *newState(void) {
  state_t *state = malloc(sizeof(state_t));

  // Allocate real memory for emulator memory
  state->memory = malloc(sizeof(uint8_t) * (MEMORY_SIZE + GPIO_PINS_BYTES));
  if (!(state->memory)) {
    free(state);
      return NULL;
  }

  // Intialise all emulated memory to 0
  memset(state->memory, 0, MEMORY_SIZE + GPIO_PINS_BYTES);

  // Allocate real memory for emulator registers
  state->registers = malloc(sizeof(uint32_t) * NUM_REGISTERS);
  if (!(state->registers)) {
    free(state->memory);
    free(state);
    return NULL;
  }

  // Initialise all registers to 0
  memset(state->registers, 0, sizeof(uint32_t) * (NUM_REGISTERS));

  // Set PC to first memory address of emulator memory
  state->registers[PC] = 0;

  // Initialise state flags to 0
  state->isExecuting = 0;
  state->isFetching = 0;
  state->isDecoding = 0;
  state->isTerminated = 0;
  state->isJump = 0;

  return state;
}

// Free the memory of the state of the emulator
void deleteState(state_t *state) {
  free(state->registers);
  free(state->memory);
  free(state);
}

// Get a given number of bits from a given instruction
uint32_t getBits(uint32_t instruction, int startingIndex, int length) {
  uint32_t mask;
  if (startingIndex == MAX_BIT) {
    mask = 0xFFFFFFFF;
  } else {
    mask = (uint32_t) (1 << (startingIndex + 1)) - 1;
  }
  mask &= instruction;
  mask >>= (startingIndex - (length - 1));
  return mask;
}

// Set the CPSR flags of the system
void setCPSRFlags(state_t *state, uint8_t value, char flag) {
  switch (flag) {
    case 'N':
    case 'n':
      if (value) {
        state->registers[CPSR] |= SET_N_MASK;
      } else {
        state->registers[CPSR] &= ~SET_N_MASK;
      }
      return;
    case 'Z':
    case 'z':
      if (value) {
        state->registers[CPSR] |= SET_Z_MASK;
      } else {
        state->registers[CPSR] &= ~SET_Z_MASK;
      }
      return;
    case 'C':
    case 'c':
      if (value) {
        state->registers[CPSR] |= SET_C_MASK;
      } else {
        state->registers[CPSR] &= ~SET_C_MASK;
      }
      return;
    case 'V':
    case 'v':
      if (value) {
        state->registers[CPSR] |= SET_V_MASK;
      } else {
        state->registers[CPSR] &= ~SET_V_MASK;
      }
      return;
    default:
      perror("Unused Flag");
      state->isTerminated = 1;
      return;
  }
}

// Gets four bits of the given the instruction at LSB ... (LSB + 4)
uint8_t obtainFourBitsAtLSB(uint32_t instruction, uint8_t LSB) {
  int MASK = 0xF << LSB;
  return (instruction & MASK) >> LSB;
}

// Get word starting at the most significant bit onwards
uint32_t readWordAtMSB(state_t *state, uint32_t location) {
  uint32_t result = 0;
  for (int i = BYTES_IN_WORD - 1; i >=0 ; i--) {
    result += (state->memory[location + i] << (8 * (i)));
  }
  return result;
}

// Write word into memory from the most significant bit onwards
void writeWordAtMSB(state_t *state, uint32_t location, uint32_t word) {
  uint32_t mask = 0xFF;
  for (int i = 0; i < BYTES_IN_WORD; i++) {
    state->memory[location + i] = (uint8_t) (word & mask);
    word >>= 8;
  }
}

// Shift a value
uint32_t shift(uint32_t value, uint32_t shiftDegree, uint32_t shiftType) {
  uint32_t shiftedValue;
  switch (shiftType) {
    case LSL:
      return value << shiftDegree;
    case LSR:
      return value >> shiftDegree;
    case ASR:
      shiftedValue = value >> shiftDegree;
      uint32_t topBit = value >> (MAX_BIT);
      for (int i = 0; i < shiftDegree; i++) {
        shiftedValue = shiftedValue | (topBit << (MAX_BIT - i));
      }
      return shiftedValue;
    case ROR:
      shiftedValue = value;
      for (int i = 0; i < shiftDegree; i++) {
        shiftedValue = (shiftedValue >> 1) | ((shiftedValue & 1) << MAX_BIT);
      }
      return shiftedValue;
    default:
      perror("shiftType invalid @ \"util.c\".shift\n");
      return 0;
  }
}
