#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "opcode.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct {
	OpCode 	operation;
	int		address;
	int		param[3];
} Instruction;

#define I_PADDING 4

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

/**
 * Update address information for jump instruction (JMP, JMPC)
 * @param jump instruction
 * @param address
 */
void i_setAddress(Instruction * instruction, int address);

/**
 * Convert an instruction into a string
 * @param instruction
 * @return
 */
char * i_to_string(Instruction * instruction);

#endif