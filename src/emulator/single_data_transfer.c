// Imported Files
#include "single_data_transfer.h"

// Methods
// Returns the base register from the instruction
uint8_t obtainBaseReg(uint32_t instruction) {
  return obtainFourBitsAtLSB(instruction, 16);
}

// Returns the source/destination register from the instruction
uint8_t obtainSrcDestReg(uint32_t instruction) {
  return obtainFourBitsAtLSB(instruction, 12);
}

// Returns true (1) if the 'immediate offset' bit is not set
bool isImmediateOffset(uint32_t instruction) {
  return !getBits(instruction, 25, 1);
}

// Returns the shifted register value
uint32_t obtainShiftedReg(state_t *state, uint32_t instruction) {
  uint32_t unshiftedValue =
          state->registers[obtainFourBitsAtLSB(instruction, 0)];
  uint8_t shiftType = (instruction & (0x3 << 5)) >> 5;
  uint8_t shiftDegree = (instruction & (0x1f << 7)) >> 7;
  return shift(unshiftedValue, shiftDegree, shiftType);
}

// Returns the offset from the instruction
uint32_t obtainOffset(state_t *state, uint32_t instruction) {
  if (isImmediateOffset(instruction)) {
    int MASK = 0xfff;
    return (instruction & MASK);
  } else {
    return obtainShiftedReg(state,instruction);
  }
}

// Returns true (1) if the 'preindexing' bit is not set
bool isPreIndexing(uint32_t instruction) {
  return getBits(instruction, 24, 1);
}

// Returns true (1) if the 'load' bit is not set
bool isLoad(uint32_t instruction) {
  return getBits(instruction, 20, 1);
}

// Returns true (1) if the 'up' bit is not set
bool isUp(uint32_t instruction) {
  return getBits(instruction, 23, 1);
}

// Returns true (1) if the memory address is within the GPIO section
bool isGPIO(uint32_t address) {
  return address >= GPIO_MEMORY_START
          && address <= GPIO_MEMORY_START + GPIO_PINS_BYTES;
}

void handleGPIO(state_t *state, uint32_t instruction, uint32_t memoryAddress) {
  if (isLoad(instruction)) {
    state->registers[obtainSrcDestReg(instruction)] = memoryAddress;
  }
}

void single_data_transfer_execute(state_t* state,uint32_t instruction) {
  int32_t offset = obtainOffset(state, instruction);
  int32_t memoryAddress = state->registers[obtainBaseReg(instruction)];

  if(!isUp(instruction)) {
    offset = -(offset);
  }

  if (isPreIndexing(instruction)) {
    memoryAddress += offset;
  } else {
    state->registers[obtainBaseReg(instruction)] += offset;
  }

  // Check for GPIO instructions
  if (isGPIO(memoryAddress)) {
    uint8_t pinSet = (memoryAddress % GPIO_MEMORY_START) / 4;
    printf("One GPIO pin from %d to %d has been accessed\n",
            pinSet * 10, (pinSet * 10) + 9);
    handleGPIO(state, instruction, memoryAddress);
    return;
  } else if (memoryAddress == GPIO_CLEAR_M_ADDRESS) {
    // Clear GPIO Pins
    printf("PIN OFF\n");
    return;
  } else if (memoryAddress == GPIO_SET_M_ADDRESS) {
    // Set GPIO Pins
    printf("PIN ON\n");
    return;
  }

  if (memoryAddress < 0 || memoryAddress > MEMORY_SIZE) {
    printf("Error: Out of bounds memory access at address 0x%08x\n",
            memoryAddress);
  } else if (isLoad(instruction)) {
    state->registers[obtainSrcDestReg(instruction)]
            = readWordAtMSB(state, memoryAddress);
  } else {
    writeWordAtMSB(state, memoryAddress,
            state->registers[obtainSrcDestReg(instruction)]);
  }
}
