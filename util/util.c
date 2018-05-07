#include "util.h"

void util_cond(SymbolTab * symbolTable, MemoireInstr * memInst, OpCode opCode) {

	// TODO: problem with while : we have i and tmp in symbol table, why do we pop twice here?? this makes i disappear!!
	// TODO: Solution : copy i as tmp before use util_cond (in Expression -> tID)
	mi_push(memInst, new_Instruction(op_load, 0, ts_pop(symbolTable)));
	mi_push(memInst, new_Instruction(op_load, 1, ts_pop(symbolTable)));
	mi_push(memInst, new_Instruction(opCode, 0, 0, 1));
}

void util_op(SymbolTab * symbolTable, MemoireInstr * memInst, OpCode opCode) {
	mi_push(memInst, new_Instruction(op_load, 0, ts_pop(symbolTable)));
	mi_push(memInst, new_Instruction(op_load, 1, ts_peek(symbolTable)));
	mi_push(memInst, new_Instruction(opCode, 0, 1, 0));
	mi_push(memInst, new_Instruction(op_store, ts_peek(symbolTable), 0));
}

