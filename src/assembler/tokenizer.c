// Imported Files
#include "tokenizer.h"

// Methods
inst_t* allocInstruction(void){
  inst_t* instruction = malloc(sizeof(inst_t));
  instruction->arg1 = NULL;
  instruction->arg2 = NULL;
  instruction->arg3 = NULL;
  instruction->arg4 = NULL;
  return instruction;
}

void addArgToInstruction(inst_t *instruction, char *arg){
  if (instruction->arg1 == NULL){
    instruction->arg1 = malloc(sizeof(arg));
    strcpy(instruction->arg1, arg);
  } else if (instruction->arg2 == NULL){
    instruction->arg2 = malloc(sizeof(arg));
    strcpy(instruction->arg2, arg);
  } else if (instruction->arg3 == NULL){
    instruction->arg3 = malloc(sizeof(arg));
    strcpy(instruction->arg3, arg);
  } else {
    instruction->arg4 = malloc(sizeof(arg));
    strcpy(instruction->arg4, arg);
  }
}

void getArguments(char* arguments, inst_t* instruction){
  bool bracketOpen = false;
  char argument[20];
  int j = 0;
  int k = 0;
  for (int i = 0; arguments[i] != '\0'; i++) {
    if (arguments[i] == '['){
      bracketOpen = true;
    } else if (arguments[i] == ']'){
      bracketOpen = false;
    } else if (arguments[i] == ',' && !bracketOpen){
      addArgToInstruction(instruction, argument);
      memset(argument, '\0', j);
      j = 0;
      k++;
      continue;
    }
    if(arguments[i] != ' ' || bracketOpen || k == 3){
      argument[j] = arguments[i];
      j++;
    }
  }
  if (j > 0){
    argument[j] = 0;
    addArgToInstruction(instruction, argument);
  }
}

inst_t* tokenize(char *currentInstruction, int address, st_t *symbolTable, llist_t *constantValues){
  // printf("current instruction: %s\n",currentInstruction);
  inst_t* instruction = allocInstruction();
  int i = 0;
  char *opcode = malloc(5 * sizeof(char));
  for(i = 0; currentInstruction[i] != ' ';i++){
    opcode[i] = currentInstruction[i];
  }
  opcode[i] = 0;
  instruction->opcode = opcode;
  getArguments(&(currentInstruction[i]), instruction);
  instruction->memoryLocation = address;
  instruction->symbolTable = symbolTable;
  instruction->constantValues = constantValues;
  free(currentInstruction);
  return instruction;
}



// int main(void){
//
//    char *instr = "ldr [r1, r2], r0, r3, #122";
//    inst_t* struc = tokenize(instr, 0, NULL, NULL);
//    char *opcode = struc->opcode;
//    printf("%s-%s-%s-%s-%s\n",opcode, struc->arg1, struc->arg2,
//              struc->arg3, struc->arg4);
//
//  return 0;
// }
