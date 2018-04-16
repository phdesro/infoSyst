#include "util.h"

void util_cond(SymbolTab * symbolTable, MemoireInstr * memInst, OpCode opCode) {
	mi_push(memInst, new_Instruction2(op_load, 0, ts_pop(symbolTable)));
	mi_push(memInst, new_Instruction2(op_load, 1, ts_pop(symbolTable)));
	mi_push(memInst, new_Instruction3(opCode, 0, 0, 1));
}

void util_op(SymbolTab * symbolTable, MemoireInstr * memInst, OpCode opCode) {
	mi_push(memInst, new_Instruction2(op_load, 0, ts_pop(symbolTable)));
	mi_push(memInst, new_Instruction2(op_load, 1, ts_peek(symbolTable)));
	mi_push(memInst, new_Instruction3(opCode, 0, 1, 0));
	mi_push(memInst, new_Instruction2(op_store, ts_peek(symbolTable), 0));
}

