#ifndef OPCODE_H
#define OPCODE_H

typedef enum {

	// 3 params
	op_add,
	op_mul,
	op_div,
	op_sub,
	
	op_equ,
	op_inf,
	op_infe,
	op_sup,
	op_supe,
	op_dif,

	// 2 params
	op_cop,
	op_afc,
	op_load,
	op_store,

	op_jmpc,

	// 1 param
	op_jmp

} OpCode;

char * op_string(OpCode op);

#endif

