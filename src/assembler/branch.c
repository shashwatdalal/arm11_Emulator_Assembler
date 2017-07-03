#include "branch.h"

//Methods
//Computes offset between label and current memory location
uint32_t computeOffset(inst_t *tokens){
	uint32_t labelAddr = stGet(tokens->symbolTable, tokens->arg1);
	uint32_t currentAddr = tokens->memoryLocation;
	// Negate current address by converting to two's complement
	int32_t signedOffset = labelAddr - currentAddr + PIPELINE_OFFSET;
	// Sign contraction from 32-bit to 26-bit
	uint32_t unsignedOffset = signedOffset & (0x03FFFFFF);
	// Shift right by 2
	unsignedOffset = unsignedOffset >> 2;
	return unsignedOffset;
}

uint32_t assembleBEQ(inst_t *tokens){
	uint32_t binary = DEFAULT_BRANCH_CODE;
	uint32_t offset = computeOffset(tokens);
	return binary + offset;
 }

uint32_t assembleBNE(inst_t *tokens){
	uint32_t binary = DEFAULT_BRANCH_CODE + (0x1 << 28);
	uint32_t offset = computeOffset(tokens);
	return binary + offset;
}

uint32_t assembleBGE(inst_t *tokens){
	uint32_t binary = DEFAULT_BRANCH_CODE + (0xA << 28);
	uint32_t offset = computeOffset(tokens);
	return binary + offset;
}

uint32_t assembleBLT(inst_t *tokens){
	uint32_t binary = DEFAULT_BRANCH_CODE + (0xB << 28);
	uint32_t offset = computeOffset(tokens);
	return binary + offset;
}

uint32_t assembleBGT(inst_t *tokens){
	uint32_t binary = DEFAULT_BRANCH_CODE + (0xC << 28);
	uint32_t offset = computeOffset(tokens);
	return binary + offset;
}

uint32_t assembleBLE(inst_t *tokens){
	uint32_t binary = DEFAULT_BRANCH_CODE + (0xD << 28);
	uint32_t offset = computeOffset(tokens);
	return binary + offset;
}

uint32_t assembleB(inst_t *tokens){
	uint32_t binary = DEFAULT_BRANCH_CODE + (0xE << 28);
	uint32_t offset = computeOffset(tokens);
	return binary + offset;
}
