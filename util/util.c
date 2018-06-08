#include "util.h"

/**
 * Generate ASM for "Arithmetic Expressions".
 * Used to generate ADD, SUB, DIV, MUL, EQU, INF, INFE, SUP, SUPE, DIF
 * @param symbolTable
 * @param memInst
 * @param opCode
 */
void util_op(SymbolTab * symbolTable, MemoireInstr * memInst, OpCode opCode) {

	mi_push(memInst, new_Instruction(op_load, 1, ts_pop(symbolTable)));
	mi_push(memInst, new_Instruction(op_load, 0, ts_peek(symbolTable)));
	mi_push(memInst, new_Instruction(opCode, 0, 0, 1));
	mi_push(memInst, new_Instruction(op_store, ts_peek(symbolTable), 0));
}

/**
 * Copy file
 * @param from : location of source
 * @param to : location of destination
 */
void util_copy_file (char * from, char * to) {

	FILE * source = fopen(from, "r"),
			* target= fopen(to, "w");
	char ch;

	if(source == NULL) {
		printf("Copy failed : source not exist %s\n", from);
		return;
	}
	if(target == NULL) {
		printf("Copy failed : destination not exist %s\n", to);
		return;
	}

	while( ( ch = fgetc(source) ) != EOF )	fputc(ch, target);

	printf("Copy file from %s to %s\n", from, to);
	fclose(source);
	fclose(target);
}