#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "opcode.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct {
	OpCode 	operation;
	int		address;
	int		param[3];
} Instruction;

/**
 * Instancy a new instruction, parameter value will be detected itself
 * @param operation
 * @param  int[1-3]
 * @return new instruction
 */
Instruction * new_Instruction(OpCode operation, ...);

/**
 * Print instruction
 * @param instruction
 * @param prefix "\t"
 */
void i_print(Instruction * instruction);

/**
 * Check if instruction is a waiting jump to be filled
 * @param instruction
 * @return true/false
 */
int i_isWaitingJump(Instruction * instruction);

void i_setAddress(Instruction * instruction, int address);

#endif