#include "meminstr.h"
// ================ private ================ //

Node * new_Node(Instruction * instruction) {
	Node * node = malloc(sizeof(Node));
	node->instruction = instruction;
	node->next = NULL;
	return node;
}

// ================ public ================ //

MemoireInstr * new_MemoireInstr() {
	MemoireInstr * mem = malloc(sizeof(MemoireInstr));
	mem->first = NULL;
	mem->last = NULL;
	return mem;
}

/**
 * Add new instruction in memory, automatically update it's address
 * @param mem
 * @param instruction
 */
void mi_push(MemoireInstr * mem, Instruction * instruction) {

	mem->last_address += PADDING;
	instruction->address = mem->last_address;
	Node * node = new_Node(instruction);

	if(mem->first == NULL) {
		mem->first = node;	
	} 

	if(mem->last != NULL) {
		mem->last->next = node;	
	} 

	mem->last = node;
}

/**
 * Print memory state
 * @param mem
 */
void mi_print(MemoireInstr * mem) {
	printf("Memoire Instruction : [\n");

	Node * node = mem->first;
	while(node != NULL) {
		i_print(node->instruction);
		node = node->next;
	}

	printf("]\n");
}