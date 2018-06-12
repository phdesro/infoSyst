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
	case op_echo: 	return "ECHO";
	case op_nop: 	return "NOP";
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
		case op_jmp: case op_echo:
			return 1;
		case op_nop:
			return 0;
		default:
			return -1;
	}

}

char * op_binary(OpCode op) {
	switch(op) {
		case op_add:	return "01";
		case op_sub:	return "03";
		case op_mul:	return "02";
		case op_div:	return "04";
		case op_equ:	return "09";
		case op_inf:	return "0A";
		case op_infe:	return "0B";
		case op_sup:	return "0C";
		case op_supe:	return "0D";
		case op_cop:	return "05";
		case op_afc:	return "06";
		case op_load:	return "07";
		case op_store:	return "08";
		case op_jmpc:	return "0F";
		case op_jmp:	return "0E";

		case op_echo: 	return "10";
		case op_nop: 	return "00";
		default:
			return "XX";
	}
}