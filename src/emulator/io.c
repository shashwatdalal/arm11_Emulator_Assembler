// Imported File
#include "io.h"

// Methods
// Print the state of each register
void printRegisters(state_t *state) {
  printf("Registers:\n");
  for (int i = 0; i < NUM_USED_REGISTERS; i++) {
    if(i < LOWEST_DOUBLE_DIGIT){
      printf("$%d  : %10d (0x%08x)\n", i, state->registers[i], state->registers[i]);
    } else {
      printf("$%d : %10d (0x%08x)\n", i, state->registers[i], state->registers[i]);
    }
  }
  printf("PC  : %10u", state->registers[PC]);
  printf(" (0x%08x)\n", state->registers[PC]);
  printf("CPSR: %10d (0x%08x)\n", state->registers[CPSR], state->registers[CPSR]);
}

// Print the state of memory if it is non-zero
void printMemory(state_t *state) {
  printf("Non-zero memory:\n");
  for (int i = 0; i < (MEMORY_SIZE / BYTES_IN_WORD); i += 4) {
    if (readWordAtMSB(state, i) != 0) {
      // Switch from Big-Endian to Small-Endian
      printf("0x%08x: 0x", i );
      for (int j = 0; j < BYTES_IN_WORD; j++) {
        printf("%02x",  state->memory[i+j]);
      }
      printf("\n");
    }
  }
}

// Print the state of the emulator
void printState(state_t *state) {
  printRegisters(state);
  printMemory(state);
}

// Read a binary file into memory, returning 1 if it is successful
int readBinaryIntoMem(state_t *state, char *fileName) {
  FILE *file_ptr;
  file_ptr = fopen(fileName, "rb");
  if (!file_ptr) {
    perror("ERROR: Unable to read file");
    return 0;
  }

  uint8_t *buffer = malloc(sizeof(uint8_t));
  if (!buffer) {
    perror("ERROR: Unable to Allocate Buffer");
    return 0;
  }

  for (int i = 0; fread(buffer, sizeof(*buffer), 1, file_ptr) == 1; i++) {
    state->memory[i] = *buffer;
  }

  free(buffer);
  fclose(file_ptr);
  return 1;
}
