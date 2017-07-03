// Imported Files
#include "util.h"

// Methods
uint8_t getRegAddr (char *string){
  string++;
  return (int) atoi (string);
}

ft_t *populateFunctionTable(void) {
  ft_t *functionTable = initFunctionTable();
  ftPut(functionTable,"add",&assembleADD);
  ftPut(functionTable,"sub",&assembleSUB);
  ftPut(functionTable,"rsb",&assembleRSB);
  ftPut(functionTable,"and",&assembleAND);
  ftPut(functionTable,"eor",&assembleEOR);
  ftPut(functionTable,"orr",&assembleORR);
  ftPut(functionTable,"mov",&assembleMOV);
  ftPut(functionTable,"tst",&assembleTST);
  ftPut(functionTable,"teq",&assembleTEQ);
  ftPut(functionTable,"cmp",&assembleCMP);
  ftPut(functionTable,"mul",&assembleMUL);
  ftPut(functionTable,"mla",&assembleMLA);
  ftPut(functionTable,"ldr",&assembleLDR);
  ftPut(functionTable,"str",&assembleSTR);
  ftPut(functionTable,"beq",&assembleBEQ);
  ftPut(functionTable,"bne",&assembleBNE);
  ftPut(functionTable,"bge",&assembleBGE);
  ftPut(functionTable,"blt",&assembleBLT);
  ftPut(functionTable,"bgt",&assembleBGT);
  ftPut(functionTable,"ble",&assembleBLE);
  ftPut(functionTable,"b",&assembleB);
  ftPut(functionTable,"lsl",&assembleLSL);
  ftPut(functionTable,"andeq",&assembleANDEQ);
  return functionTable;
}

uint32_t *initOutputArray(int size) {
  uint32_t *outputArray = malloc(sizeof(uint32_t) * size);
  if(outputArray == NULL) {
    return 0;
  }
  return outputArray;
}

void freeOutputArray(uint32_t *array) {
  free(array);
}

void freeInstructionStruct(inst_t *instruction){
  free(instruction->opcode);
  free(instruction->arg1);
  free(instruction->arg2);
  free(instruction->arg3);
  free(instruction->arg4);
  free(instruction);
}
