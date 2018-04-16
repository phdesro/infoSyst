#include <stdio.h>
#include <stdlib.h>

#include "opcode.h"

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct {
	OpCode 	operation;
	int		address;
	int		param[3];
} Instruction;

Instruction * new_Instruction1(OpCode operation, int param1);
Instruction * new_Instruction2(OpCode operation, int param1, int param2);
Instruction * new_Instruction3(OpCode operation, int param1, int param2, int param3);

void i_print(Instruction * instruction);

#endif

