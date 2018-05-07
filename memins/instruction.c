#include "instruction.h"

/**
 * Instancy a new instruction, parameter value will be detected itself
 * @param operation
 * @param  int[1-3]
 * @return new instruction
 */
Instruction * new_Instruction(OpCode operation, ...) {
	Instruction * instr = malloc(sizeof(Instruction));
	instr->operation = operation;

	int nbargs = op_args(operation);
	va_list(args);

	#pragma GCC diagnostic ignored "-Wvarargs"
	va_start(args, nbargs); // a warning here because we don't pass the nbargs in argument, but here we don't need to
	#pragma GCC diagnostic pop

	instr->param[0] = va_arg(args, int);
	instr->param[1] = nbargs < 2 ? -1 : va_arg(args, int);
	instr->param[2] = nbargs < 3 ? -1 : va_arg(args, int);
	if(nbargs > 3)	{
		printf("error %d arguments dans new_Instruction()", nbargs);
		exit(1);
	}

	va_end(args);

	return instr;

}

/**
 * Print instruction
 * @param instruction
 */
void i_print(Instruction * ins) {

	printf("@%d: ", ins->address);

	printf("{ %s ", op_string(ins->operation));

	for(int i = 0; i < 3; i++) {
		if(ins->param[i] >= 0)
			printf(", %d ", ins->param[i]);
		else if(ins->param[i] == I_ADR_UNFILLED)
			printf(", ##@## ");
	}

	printf(" }\n");
}

/**
 * Check if instruction is a waiting jump to be filled
 * @param instruction
 * @return true/false
 */
int i_isWaitingJump(Instruction * instruction) {
	return (instruction->operation == op_jmpc || instruction->operation == op_jmp )
		   && instruction->param[0] == I_ADR_UNFILLED;
}

void i_setAddress(Instruction * instruction, int address) {
	instruction->param[0] = address;
}