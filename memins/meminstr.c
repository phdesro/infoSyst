#include "meminstr.h"

MemoireInstr * new_MemmoireInstr() {
	MemoireInstr * mem = malloc(sizeof(MemmoireInstr));
	mem->first = NULL;
	mem->last = NULL;
	return mem;
}

void mi_push(MemoireInstr * mem, Instruction * instruction) {
	Node * node = new_Node()
}