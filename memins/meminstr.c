#include "meminstr.h"
// ================ private ================ //

Node * new_Node(Instruction * instruction) {
	Node * node = malloc(sizeof(Node));
	node->instruction = instruction;
	node->next = NULL;
	return node;
}

/**
 * Get node(index) in linked list of index
 * @param node
 * @param index >= 0
 * @return Node *
 */
Node * n_get(Node * node, int index) {
	if(index < 0)	{
		printf("[MemoireInstr error] access to node %d \n", index);
		exit(1);
	}

	if(!index) // index == 0
		return node;

	return n_get(node->next, index - 1);
}

// ================ public ================ //

MemoireInstr * new_MemoireInstr() {
	MemoireInstr * mem = malloc(sizeof(MemoireInstr));

	// instruction list
	mem->first = NULL;
	mem->last = NULL;

	// waiting jump list
	mem->first_jump = NULL;
	mem->last_jump = NULL;

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

	if(mem->first == NULL)
		mem->first = node;

	if(mem->last != NULL)
		mem->last->next = node;

	mem->last = node;

	// see a new waiting jump -> push to waiting jump list
	if(i_isWaitingJump(instruction)) {

		Node * jump = new_Node(instruction);

		if(mem->last_jump != NULL)
			mem->last_jump->next = jump;

		mem->last_jump = jump;
	}

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

/**
 * Find the corresponding jump, update its jmpc with address and delete it out
 * @param mem
 * @param address
 * @param distance
 */
void mi_fill_jump(MemoireInstr * mem, int address, int distance) {

	// find jump node
	Node * jump_node = n_get(mem->first_jump, distance);

	// update it
	i_setAddress(jump_node->instruction, address);

	// now delete node

}