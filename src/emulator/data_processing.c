// Imported Files
#include "data_processing.h"

// Methods
// Returns true (1) if 'immediate operand' bit is set, 0 otherwise
bool isImmediateOperand(uint32_t instruction) {
  return getBits(instruction, 25, 1);
}

// Returns true (1) if 'set conditions' bit is set, 0 otherwise
bool setConditions(uint32_t instruction) {
  return ((instruction & (1 << 20)) >> 20) == 1;
}

// Set the 'C' flag of the CSPR to the carry out of the shift
void setCFlagFromShift(state_t *state, uint32_t unshiftedValue,
          uint32_t shiftDegree, uint8_t shiftType) {
  if (shiftDegree == 0) {
    setCPSRFlags(state, 0, 'C');
    return;
  }

  uint8_t value = 0;
  switch (shiftType) {
    case LSL:
      value = getBits(unshiftedValue, MAX_BIT - shiftDegree + 1, 1);
      break;
    case LSR:
    case ASR:
    case ROR:
      value = getBits(unshiftedValue, shiftDegree - 1, 1);
      break;
    default:
      perror("shiftType invalid @ \"data_processing.c\".setCFlagFromShift\n");
  }
  setCPSRFlags(state, value, 'C');
}

// Set the 'C' flag of the CSPR to the carry out of the ALU
void setCFlagFromALU(state_t *state, uint32_t first, uint32_t second,
          uint8_t opcode) {
  bool value;
  uint32_t result = first + second;
  switch (opcode) {
    case CMP:
    case SUB:
      value = !(second > first);
      break;
    case RSB:
      value = first > second;
      break;
    case ADD:
      value = first < result || second < result;
      break;
    default:
      return;
  }
  setCPSRFlags(state, value, 'C');
}

// Obtain the (shifted) second operand from the instruction
uint32_t obtainOperand2(state_t *state, uint32_t instruction, bool setC) {
  uint32_t unshiftedValue;
  uint8_t shiftDegree;
  uint8_t shiftType;
  if (isImmediateOperand(instruction)) {
    // Operand2 is an immediate value
    unshiftedValue = instruction & 0xFF;
    shiftDegree = obtainFourBitsAtLSB(instruction, 8) * 2;
    shiftType = ROTATE_RIGHT_OP;
  } else {
    // Operand2 is a register
    unshiftedValue = state->registers[obtainFourBitsAtLSB(instruction, 0)];
    shiftType = (instruction & (0x3 << 5)) >> 5;
    if ((instruction >> 4) & 1) {
      // Shift by register
      shiftDegree = state->registers[obtainFourBitsAtLSB(instruction, 8)];
    } else {
      // Shift by constant
      shiftDegree = (instruction & (0x1F << 7)) >> 7;
    }
  }
  uint32_t result = shift(unshiftedValue, shiftDegree, shiftType);

  // Set C flag to carry out of shift
  if (setC && setConditions(instruction)) {
    setCFlagFromShift(state, unshiftedValue, shiftDegree, shiftType);
  }

  return result;
}

// Set the 'Z' flag of the CSPR
void setZFlag(state_t *state, uint32_t value) {
  if (value) {
    setCPSRFlags(state, 0, 'Z');
  } else {
    setCPSRFlags(state, 1, 'Z');
  }
}

// Set the 'N' flag of the CSPR
void setNFlag(state_t *state, uint32_t value) {
  if (getBits(value, MAX_BIT, 1)) {
    setCPSRFlags(state, 1, 'N');
  } else {
    setCPSRFlags(state, 0, 'N');
  }
}

// Execute a data processing instruction
void data_processing_execute(state_t *state, uint32_t instruction) {
  uint8_t opcode = obtainFourBitsAtLSB(instruction, 21);
  uint32_t srcReg = state->registers[obtainFourBitsAtLSB(instruction, 16)];
  uint32_t result = 0;
  bool setCFlagToALU = false;
  bool toWrite = false;

  switch (opcode) {
    case AND:
      result = srcReg & obtainOperand2(state, instruction, true);
      toWrite = true;
      break;
    case EOR:
      result = srcReg ^ obtainOperand2(state, instruction, true);
      toWrite = true;
      break;
    case SUB:
      result = srcReg - obtainOperand2(state, instruction, false);
      toWrite = true;
      setCFlagToALU = true;
      break;
    case RSB:
      result = obtainOperand2(state, instruction, false) - srcReg;
      toWrite = true;
      setCFlagToALU = true;
      break;
    case ADD:
      result = srcReg + obtainOperand2(state, instruction, false);
      toWrite = true;
      setCFlagToALU = true;
      break;
    case TST:
      result = srcReg & obtainOperand2(state, instruction, true);
      break;
    case TEQ:
      result = srcReg ^ obtainOperand2(state, instruction, true);
      break;
    case CMP:
      result = srcReg - obtainOperand2(state, instruction, false);
      setCFlagToALU = true;
      break;
    case ORR:
      result = srcReg | obtainOperand2(state, instruction, true);
      toWrite = true;
      break;
    case MOV:
      result = obtainOperand2(state, instruction, true);
      toWrite = true;
      break;
    default:
      perror("Opcode invalid @ \"data_processing.c\".execute_dp\n");
  }

  // Write result to the destination register
  if (toWrite) {
    state->registers[obtainFourBitsAtLSB(instruction, 12)] = result;
  }

  // Set 'C' flag to carry flag of ALU
  if (setCFlagToALU & setConditions(instruction)) {
    uint32_t secondOperand = obtainOperand2(state, instruction, false);
    setCFlagFromALU(state, srcReg, secondOperand, opcode);
  }

  // Set 'Z' and 'N' flags
  if (setConditions(instruction)) {
    setZFlag(state, result);
    setNFlag(state, result);
  }
}
