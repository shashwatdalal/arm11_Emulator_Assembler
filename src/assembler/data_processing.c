// Imported Files
#include "data_processing.h"

// Methods
// Calculate the right rotation for an immediate second operand
uint16_t rightRotate(uint32_t value) {
  uint16_t rotationDegree = 0;
  while (value >= 256) {
    uint8_t topBit = (value & 0x80000000) >> 31;
    value <<= 1;
    value |= topBit;
    rotationDegree++;
  }
  if (rotationDegree % 2) {
    // rotationDegree is odd
    uint8_t topBit = (value & 0x80000000) >> 31;
    value <<= 1;
    value |= topBit;
    rotationDegree++;
  }
  return (rotationDegree << 7) | ((uint8_t) value);
}

// Calculate the immediate value from its string representation
uint16_t getImmediateValue(char *string, bool rotate) {
  uint32_t unRotated;
  if (string[1] == 'x') {
    // Operand2 is in hexadecimal
    unRotated = strtol(string, NULL, 0);
  } else {
    // Operand2 is in decimal
    unRotated = atoi(string);
  }
  if (rotate) {
    return rightRotate(unRotated);
  } else {
    return unRotated;
  }
}

// Obtain the binary shift code
uint8_t getShiftType(char *string) {
  if (!strcmp(string, "lsl")) {
    return 0;
  }
  if (!strcmp(string, "lsr")) {
    return 1;
  }
  if (!strcmp(string, "asr")) {
    return 2;
  }
  if (!strcmp(string, "ror")) {
    return 3;
  }
  perror("shiftType @ \"data_processing.c\".getShiftType");
  return 0;
}

// Get the binary value from the string representation of operand2
uint16_t getOperand2NoShift(char *string) {
  if (*string == '#') {
    // Operand2 is an immediate operand
    string++;
    return getImmediateValue(string, true);
  } else if (*string == 'r') {
    // Operand2 is a register
    return getRegAddr(string);
  } else {
    perror("string format @ \"data_processing.c\".getOperand2NoShift");
    return 0;
  }
}

// Operand2 is a shifted value [optional]
uint16_t getOperand2WithShift(char *arg1, char *arg2) {
  uint16_t rm = getRegAddr(arg1);
  char stringAsArray[20];
  strcpy(stringAsArray, arg2);

  char *shiftType = strtok(stringAsArray, " ");
  char *shiftParameter = strtok(NULL, " ");

  if (*shiftParameter == '#') {
    // Shift parameter is immediate
    shiftParameter++;
    uint16_t immediateInt = getImmediateValue(shiftParameter, false);
    return ((immediateInt << 7) | (getShiftType(shiftType) << 5)) | rm;
  } else if (*shiftParameter == 'r') {
    // Shift parameter is a register
    uint16_t shiftedReg = getRegAddr(shiftParameter);
    return (((shiftedReg << 8) | (getShiftType(shiftType) << 5)) | 1 << 4) | rm;
  }
  perror("shiftParameter @ \"data_processing.c\".getOperand2WithShift");
  return 0;
}

// Initialise the instruction common to all opcodes
uint32_t initCommonInstr(uint8_t opcode, char *operand2) {
  // Cond = 1110
  uint32_t result = 0xE;
  // Set 2 bits to 0 by definition
  result <<= 2;
  // Set I if operand2 is immediate
  result = (result << 1) | (*operand2 == '#');
  // Set opcode
  result = (result << 4) | opcode;
  return result;
}

// Assemble instructions that compute results (Cond=1110 & S=0 by definition)
uint32_t asmblCase1NoShift(inst_t *instruction, uint8_t opcode) {
  uint8_t rd = getRegAddr(instruction->arg1);
  uint8_t rn = getRegAddr(instruction->arg2);
  char *operand2 = instruction->arg3;

  uint32_t result = initCommonInstr(opcode, operand2);
  // Set S to 0 by definition
  result <<= 1;
  // Set Rn
  result = (result << 4) | rn;
  // Set Rd
  result = (result << 4) | rd;
  // Set operand2
  result = (result << 12) | getOperand2NoShift(operand2);
  return result;
}

// Assemble instructions that compute results (Cond=1110 & S=0 by definition)
uint32_t asmblCase1WithShift(inst_t *instruction, uint8_t opcode) {
  uint8_t rd = getRegAddr(instruction->arg1);
  uint8_t rn = getRegAddr(instruction->arg2);
  char *operand2fst = instruction->arg3;
  char *operand2snd = instruction->arg4;

  uint32_t result = initCommonInstr(opcode, operand2fst);
  // Set S to 0 by definition
  result <<= 1;
  // Set Rn
  result = (result << 4) | rn;
  // Set Rd
  result = (result << 4) | rd;
  // Set operand2
  result = (result << 12) | getOperand2WithShift(operand2fst, operand2snd);
  return result;
}

uint32_t asmblCase1(inst_t *instruction, uint8_t opcode) {
  if (instruction->arg4 == NULL) {
    return asmblCase1NoShift(instruction, opcode);
  } else {
    return asmblCase1WithShift(instruction, opcode);
  }
}

// Assemble instructions that compute results (Cond=1110 & S=0 by definition)
uint32_t asmblCase2NoShift(inst_t *instruction, uint8_t opcode) {
  uint8_t rd = getRegAddr(instruction->arg1);
  char *operand2 = instruction->arg2;

  uint32_t result = initCommonInstr(opcode, operand2);
  // Set S to 0 by definition
  result <<= 1;
  // Set Rn to 0 as it is not considered for this opcode
  result <<= 4;
  // Set Rd
  result = (result << 4) | rd;
  // Set operand2
  result = (result << 12) | getOperand2NoShift(operand2);
  return result;
}

// Assemble instructions that compute results (Cond=1110 & S=0 by definition)
uint32_t asmblCase2WithShift(inst_t *instruction, uint8_t opcode) {
  uint8_t rd = getRegAddr(instruction->arg1);
  char *operand2fst = instruction->arg2;
  char *operand2snd = instruction->arg3;

  uint32_t result = initCommonInstr(opcode, operand2fst);
  // Set S to 0 by definition
  result <<= 1;
  // Set Rn to 0 as it is not considered for this opcode
  result <<= 4;
  // Set Rd
  result = (result << 4) | rd;
  // Set operand2
  result = (result << 12) | getOperand2WithShift(operand2fst, operand2snd);
  return result;
}

uint32_t asmblCase2(inst_t *instruction, uint8_t opcode) {
  if (instruction->arg3 == NULL) {
    return asmblCase2NoShift(instruction, opcode);
  } else {
    return asmblCase2WithShift(instruction, opcode);
  }
}

// Assemble instructions that compute results (Cond=1110 & S=0 by definition)
uint32_t asmblCase3NoShift(inst_t *instruction, uint8_t opcode) {
  uint8_t rn = getRegAddr(instruction->arg1);
  char *operand2 = instruction->arg2;

  uint32_t result = initCommonInstr(opcode, operand2);
  // Set S to 0 by definition
  result = (result << 1) | 1;
  // Set Rn
  result = (result << 4) | rn;
  // Set Rd to 0 as it is not considered for this opcode
  result <<= 4;
  // Set operand2
  result = (result << 12) | getOperand2NoShift(operand2);
  return result;
}

// Assemble instructions that compute results (Cond=1110 & S=0 by definition)
uint32_t asmblCase3WithShift(inst_t *instruction, uint8_t opcode) {
  uint8_t rn = getRegAddr(instruction->arg1);
  char *operand2fst = instruction->arg2;

  uint32_t result = initCommonInstr(opcode, operand2fst);
  // Set S to 0 by definition
  result = (result << 1) | 1;
  // Set Rn
  result = (result << 4) | rn;
  // Set Rd to 0 as it is not considered for this opcode
  result <<= 4;
  // Set operand2
  result = (result << 12) | getOperand2NoShift(operand2fst);
  return result;
}

uint32_t asmblCase3(inst_t *instruction, uint8_t opcode) {
  if (instruction->arg3 == NULL) {
    return asmblCase3NoShift(instruction, opcode);
  } else {
    return asmblCase3WithShift(instruction, opcode);
  }
}

uint32_t assembleADD(inst_t *instruction) {
  return asmblCase1(instruction, 4);
}

uint32_t assembleSUB(inst_t *instruction) {
  return asmblCase1(instruction, 2);
}

uint32_t assembleRSB(inst_t *instruction) {
  return asmblCase1(instruction, 3);
}

uint32_t assembleAND(inst_t *instruction) {
  return asmblCase1(instruction, 0);
}

uint32_t assembleEOR(inst_t *instruction) {
  return asmblCase1(instruction, 1);
}

uint32_t assembleORR(inst_t *instruction) {
  return asmblCase1(instruction, 12);
}

uint32_t assembleMOV(inst_t *instruction) {
  return asmblCase2(instruction, 13);
}

uint32_t assembleTST(inst_t *instruction) {
  return asmblCase3(instruction, 8);
}

uint32_t assembleTEQ(inst_t *instruction) {
  return asmblCase3(instruction, 9);
}

uint32_t assembleCMP(inst_t *instruction) {
  return asmblCase3(instruction, 10);
}
