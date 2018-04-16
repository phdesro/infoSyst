#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "opcode.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define I_NO_PARAM -1
#define I_ADR_UNFILLED -2

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
 */
void i_print(Instruction * instruction);


#endif