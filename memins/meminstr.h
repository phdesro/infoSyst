#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"

#define PADDING 4

// ================ private ================ //
typedef struct Node {
	Instruction * instruction;
	struct Node * next;
} Node;

Node * new_Node();

// ================ public ================ //

typedef struct  {
    Node * first;
    Node * last;
    Node * jump;
    int last_address;
} MemoireInstr;

MemoireInstr * new_MemoireInstr();

/**
 * Add new instruction in memory, automatically update it's address
 * @param mem
 * @param instruction
 */
void mi_push(MemoireInstr * mem, Instruction * instruction);

/**
 * Print memory state
 * @param mem
 */
void mi_print(MemoireInstr * mem);
