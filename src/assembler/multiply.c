// Imported Files
#include "multiply.h"

// Methods
uint32_t assembleMUL(inst_t *tokens){
  uint32_t rd = getRegAddr(tokens -> arg1);
  uint32_t rm = getRegAddr(tokens -> arg2);
  uint32_t rs = getRegAddr(tokens -> arg3);
  return DEFAULT_MUL_CODE + (rd << 16) + (rs << 8) + rm;
}

uint32_t assembleMLA(inst_t *tokens){
  uint32_t rd = getRegAddr(tokens -> arg1);
  uint32_t rm = getRegAddr(tokens -> arg2);
  uint32_t rs = getRegAddr(tokens -> arg3);
  uint32_t rn = getRegAddr(tokens -> arg4);
  return DEFAULT_MUL_CODE + (1 << 21) + (rd << 16) + (rn << 12) + (rs << 8) + rm;
}
