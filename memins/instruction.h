typedef struct {
	OpCode 	operation;
	int		address;
	int		param[3];
} Instruction;

Instruction * new_Instruction(OpCode operation, int param1, int param2, int param3);

Instruction * new_Instruction(OpCode operation, int param1, int param2);

Instruction * new_Instruction(OpCode operation, int param1);

char * i_code(Instruction * instruction);

Instruction * instr = Instruction(qsdfqsdf);