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
	op_jmp,

	// customized
	op_echo,		// print register content to console
	op_nop			// do nothing

} OpCode;

#define I_ADR_UNFILLED -2	// indicate a parameter is an yet undefined address
#define I_NO_PARAM -2147483648	// indicate empty in parameter

/**
 * Convert OpCode into a litteral asm string
 * @param op
 * @return string
 */
char * op_string(OpCode op);

/**
 * Get the number arguments needed following the OpCode
 * @param op
 * @return int
 */
int op_args(OpCode op);

char * op_binary(OpCode op);

#endif

