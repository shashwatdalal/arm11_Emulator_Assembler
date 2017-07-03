// Imported Files
#include "special.h"

// Methods
uint32_t assembleLSL(inst_t* instructions) {
  //store temporary variables
  char *expression = malloc(sizeof(char) * 20);
  char *Rn = instructions->arg1;

  strcpy(expression, "lsl ");
  strcat(expression, instructions->arg2);

  // map lsl Rn <#exp> to mov Rn, Rn, lsl <#exp>
  // opcode for mov
  instructions->arg1 = Rn;
  instructions->arg2 = Rn;
  instructions->arg3 = expression;
  return assembleMOV(instructions);
}
uint32_t assembleANDEQ(inst_t *instructions) {
  return 0;
}
