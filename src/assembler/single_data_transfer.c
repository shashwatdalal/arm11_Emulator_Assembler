// Imported Values
#include "single_data_transfer.h"

// Methods
// Convert a string to its integer value
int stringToValue(char* string){
  if(string[0] == '-'){
    string += 1;
    return (int) -strtol(string, NULL, 0);
  }else {
    return (int) strtol(string, NULL, 0);
  }
}

// Split a string into its arguments
char** splitArgs(char* string){
  char ** array = calloc(3, sizeof(char*));
  int k = 0;
  for (int i = 1; string[i] != 0; i++) {
    char* arg = calloc(10, sizeof(char));
    for (int j = 0; string[i] != ']' && string[i] != ','; i++) {
      if(string[i] != ' ' || k == 2){
        arg[j] = string[i];
        j++;
      }
    }
    array[k] = arg;
    k++;
  }
  return array;
}

// Build the final instruction from components
uint32_t buildInstruction(bool isImm, bool isPre, bool isUp, bool isLoad,
                          uint8_t rn, uint8_t rd, uint16_t op2){
  uint32_t result = 0;
  result =  (0x39 << 26)
          + (((int)isImm) << 25) + (((int)isPre) << 24) + (((int)isUp) << 23)
          + (((int)isLoad) << 20)
          + (rn << 16) + (rd << 12) + op2;
  return result;
}

uint32_t handleConstantLoad(inst_t* instruction){
  int argValue = stringToValue(&(instruction->arg2[1]));
  if (argValue <= 0xFF && argValue > 0){
    instruction->arg2[0] = '#';
    return assembleMOV(instruction);
  }
  int32_t offset = (instruction->numOfInstructions) * 4
                      - instruction->memoryLocation - 8
                      + (instruction->constantValues->size) * 4;
  uint32_t binary = (0xF) << 23;
  binary += 1 << 20;
  int destReg = stringToValue(&(instruction->arg1[1]));
  bool isImm = false;
  bool isPre = true;
  bool isUp = true;
  bool isLoad = true;
  if (argValue < 0){
    argValue = -(argValue);
    isUp = false;
  }
  uint32_t* argPtr = malloc(sizeof(uint32_t));
  *argPtr = argValue;
  llistEnqueue(instruction->constantValues, (void*) argPtr);
  return buildInstruction(isImm,isPre,isUp,isLoad,PC,destReg,offset);
}

uint32_t handleReg (char* arg1, char** op2Components, bool isPre, bool isLoad){
  bool isImm = false;
  bool isUp = true;
  int destReg = stringToValue(&(arg1[1]));
  int baseReg = stringToValue(&(op2Components[0][1]));
  int operand2 = 0;
  if(op2Components[2] != NULL){
    //If third component is not null then operand 2 must be a shifted register
    isImm = true;
    operand2 = getOperand2WithShift(op2Components[1],op2Components[2]);
  }else if (op2Components[1] != 0){
    //If  at least two components to second argument
    if (op2Components[1][0] == '-'){
      isImm = true;
      isUp = false;
      operand2 = stringToValue(&(op2Components[1][2]));
       //Gets negative of register number
    } else {
       //arg2components[0] is either # or r
       isImm = (op2Components[1][0] == 'r');
       operand2 = stringToValue(&(op2Components[1][1]));
       //operand2 either set to value of immediate offset or register number
       if(operand2 < 0){
         //Only possible is operand2 is immediate
         isUp = false;
         operand2 = -(operand2);
       }
    }
  }
  return buildInstruction(isImm,isPre,isUp,isLoad,baseReg,destReg,operand2);
}

uint32_t handlePreIndexReg(inst_t* instruction, bool isLoad){
  char** arg2components = splitArgs(instruction->arg2);
  return handleReg(instruction->arg1,arg2components, true, isLoad);
}

uint32_t handlePostIndexReg(inst_t* instruction, bool isLoad){
  char** op2components = malloc(3 * sizeof(char*));
  instruction->arg2[0] = 0;
  ++instruction->arg2;
  op2components[0] = malloc(sizeof(instruction->arg2)-sizeof(char));
  strcpy(op2components[0],instruction->arg2);
  op2components[0][strlen(op2components[0]) -1] = 0;
  op2components[1] = instruction->arg3;
  if (instruction->arg4 != NULL){
    op2components[2] = instruction->arg4;
  }
  return handleReg(instruction->arg1,op2components,false,isLoad);
}

uint32_t assembleLDR(inst_t* instruction){
  if (instruction->arg2[0] == '='){
    return handleConstantLoad(instruction);
  } else if (instruction->arg3 == NULL){
    return handlePreIndexReg(instruction, true);
  } else {
    return handlePostIndexReg(instruction, true);
  }
}

uint32_t assembleSTR(inst_t* instruction){
  if (instruction->arg3 == NULL){
    return handlePreIndexReg(instruction, false);
  } else {
    return handlePostIndexReg(instruction, false);
  }
}
