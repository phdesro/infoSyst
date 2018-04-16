#include "opcode.h"

/**
 * Convert OpCode into a litteral asm string
 * @param op
 * @return string
 */
char * op_string(OpCode op) {
	switch(op) {
	case op_add:	return "ADD";
	case op_sub:	return "SUB";
	case op_mul:	return "MUL";
	case op_div:	return "DIV";
	case op_equ:	return "EQU";
	case op_inf:	return "INF";
	case op_infe:	return "INFE";
	case op_sup:	return "SUP";
	case op_supe:	return "SUPE";
	case op_cop:	return "COP";
	case op_afc:	return "AFC";
	case op_load:	return "LOAD";
	case op_store:	return "STORE";
	case op_jmpc:	return "JMPC";
	case op_jmp:	return "JMP";
	default:
		return "###unknown###";
	}
}

/**
 * Get the number arguments needed following the OpCode
 * @param op
 * @return int
 */
int op_args(OpCode op) {
	switch(op) {
		case op_add: case op_sub: case op_mul: case op_div: case op_equ: case op_inf : case op_infe: case op_sup: case op_supe:
			return 3;
		case op_cop: case op_afc: case op_load: case op_store: case op_jmpc:
			return 2;
		case op_jmp:
			return 1;
		default:
			return -1;
	}

}