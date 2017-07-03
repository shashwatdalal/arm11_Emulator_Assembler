#ifndef EMULATE_C
#define EMULATE_C

// Imported Files
#include "pipeline.h"

// Methods
// Main executable method of the emulator
int main(int argc, char **argv) {
  state_t *state = newState();
  if (!state) {
    perror("state allocation failed");
    return EXIT_FAILURE;
  }

  char *fileName = *(argv + 1);

  if(!readBinaryIntoMem(state, fileName)) {
    deleteState(state);
    perror("ERROR: Unable to read file into memory");
    return EXIT_FAILURE;
  }

  uint32_t instructionToExecute;
  uint32_t instructionToDecode;
  inst_t instructionToExecuteType;

  while (!(state->isTerminated)) {

    // Reset isJump
    state->isJump = 0;

    // First iteration
    instructionToDecode = fetch(state);
    incrementPC(state);

    // Second iteration
    instructionToExecute = instructionToDecode;
    instructionToExecuteType = decode(state, instructionToDecode);
    instructionToDecode = fetch(state);
    incrementPC(state);

    while (!(state->isTerminated) && !(state->isJump)) {
      if (instructionToExecute != TERMINATION_CODE) {
        execute(state, instructionToExecute, instructionToExecuteType);
      } else {
        state->isTerminated = 1;
        break;
      }
      instructionToExecute = instructionToDecode;
      if (instructionToDecode != TERMINATION_CODE) {
        instructionToExecuteType = decode(state, instructionToDecode);
        instructionToDecode = fetch(state);
      }
      incrementPC(state);
    }
  }

  // Print final state
  printState(state);

  // Free memory
  deleteState(state);
  return EXIT_SUCCESS;
}

#endif
