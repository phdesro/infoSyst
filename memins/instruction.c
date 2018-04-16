#include "instruction.h"

Instruction * new_Instruction1(OpCode operation, int param1) {
	Instruction * instr = malloc(sizeof(Instruction));
	instr->operation = operation;
	instr->param[0] = param1;
	instr->param[1] = -1;
	instr->param[2] = -1;
}

Instruction * new_Instruction2(OpCode operation, int param1, int param2) {
	Instruction * instr = malloc(sizeof(Instruction));
	instr->operation = operation;
	instr->param[0] = param1;
	instr->param[1] = param2;
	instr->param[2] = -1;
}

Instruction * new_Instruction3(OpCode operation, int param1, int param2, int param3) {
	Instruction * instr = malloc(sizeof(Instruction));
	instr->operation = operation;
	instr->param[0] = param1;
	instr->param[1] = param2;
	instr->param[2] = param3;
}

void i_print(Instruction * ins) {
	printf("\t{ %s ,  %d", op_string(ins->operation), ins->param[0]);
	if(ins->param[1] >= 0)	printf(", %d", ins->param[1]);
	if(ins->param[2] >= 0)	printf(", %d", ins->param[2]);
	printf(" }\n");
}
