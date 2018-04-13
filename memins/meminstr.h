#include "instruction.h"
#include "opcode.h"

typedef struct  {
    Node * first;
    Node * last;
} MemoireInstr;

typedef struct {
	Instruction * instruction;
	Node * next;
} Node;

MemoireInstr * new_MemmoireInstr();

void mi_push(MemoireInstr * mem, Instruction * instruction);

void print(MemoireInstr * mem);