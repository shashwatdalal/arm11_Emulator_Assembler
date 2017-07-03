#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Imported Files
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Constant Values
#define MEMORY_SIZE 65536
#define GPIO_PINS_BYTES 12
#define GPIO_MEMORY_START 0x20200000
#define GPIO_CLEAR_M_ADDRESS 0x20200028
#define GPIO_SET_M_ADDRESS 0x2020001c

#define NUM_REGISTERS 17
#define NUM_USED_REGISTERS 13
#define PC 15
#define CPSR 16
#define TERMINATION_CODE 0

#define RD 19
#define RN 15
#define RS 11
#define RM 3

#define BYTES_IN_WORD 4
#define NUM_REG_BITS 4
#define ACCUMULATE 21
#define SET 20
#define SIGNBIT 31
#define MAX_BIT 31

#define SET_N_MASK 0x80000000
#define SET_Z_MASK 0x40000000
#define SET_C_MASK 0x20000000
#define SET_V_MASK 0x10000000

#define PIPELINE_OFFSET 4
#define OFFSET_MASK 0x00FFFFFF
#define OFFSET_SIZE 26
#define SIGN_EXTENSION_MASK 0xFC000000

// System State Struct
typedef struct armState {
  uint8_t *memory;
  uint32_t *registers;
  short isExecuting;
  short isFetching;
  short isDecoding;
  short isTerminated;
  short isJump;
} state_t;

// Instruction Code Enumeration
typedef enum instructions {
  DATA_PROCESSING,
  MULTIPLY,
  SINGLE_DATA_TRANSFER,
  BRANCH
} inst_t;

// Condition Code Enumeration
enum condition {
  EQ = 0,
  NE = 1,
  GE = 10,
  LT = 11,
  GT = 12,
  LE = 13,
  AL = 14,
};

// Shift-Type Enumeration
enum shiftType {
  LSL = 0,
  LSR = 1,
  ASR = 2,
  ROR = 3,
};

#endif
