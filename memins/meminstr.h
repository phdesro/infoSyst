#include "instruction.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	Instruction * instruction;
	struct Node * next;
} Node;

typedef struct  {
    Node * first;
    Node * last;
} MemoireInstr;

MemoireInstr * new_MemoireInstr();

void mi_push(MemoireInstr * mem, Instruction * instruction);

void mi_print(MemoireInstr * mem);

// private

Node * new_Node();

