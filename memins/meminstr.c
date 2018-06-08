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

void n_delete(Node * node) {
	free(node);
	node = NULL;
}

// ================ public ================ //

MemoireInstr * new_MemoireInstr() {
	MemoireInstr * mem = malloc(sizeof(MemoireInstr));

	// instruction list
	mem->first = NULL;
	mem->last = NULL;

	// jump stack
	mem->first_jump = NULL;
	mem->last_jump = NULL;
	mem->nb_jump = 0;

	return mem;
}

/**
 * Add new instruction in memory, automatically update it's address
 * @param mem
 * @param instruction
 */
void mi_push(MemoireInstr * mem, Instruction * instruction) {

	mem->last_address += I_PADDING;
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

		if(mem->first_jump == NULL)
			mem->first_jump = jump;

		if(mem->last_jump != NULL)
			mem->last_jump->next = jump;

		mem->last_jump = jump;
		mem->nb_jump++;
	}

}

/**
 * Print memory state
 * @param mem
 * @param prefix "\t"
 */
void mi_print(MemoireInstr * mem) {

	printf("Memoire Instruction : {\n");


	// print instruction table
	printf("\tInstructions: [\n");
	Node * node = mem->first;
	while(node != NULL) {
		printf("\t\t");
		i_print(node->instruction);
		node = node->next;
	}
	printf("\t],\n");


	// print jump list
	printf("\tJumpStack: [\n");
	node = mem->first_jump;
	while(node != NULL) {
		printf("\t\t");
		i_print(node->instruction);
		node = node->next;
	}
	printf("\t]\n");


	printf("}\n");
}

/**
 * Find the corresponding jump, update its jmpc with address and delete it out
 * @param mem
 * @param address
 * @param distance
 */
void mi_fill_jump(MemoireInstr * mem, int distance) {

	// find jump node
	int id_node = mem->nb_jump - distance - 1;

	Node * jump_node = n_get(mem->first_jump, id_node);

	// update the instruction coressponding
//	i_setAddress(jump_node->instruction, mem->last_address + I_PADDING);
	i_setAddress(jump_node->instruction, mem->last_address );

	// delete node
	if(jump_node == mem->first_jump)	{
		mem->first_jump = jump_node->next;
	}	else {

		// TODO do we have this situation??
		Node * precedence = n_get(mem->first_jump, id_node -1);
		precedence->next = jump_node->next;
	}

	n_delete(jump_node);
	mem->nb_jump--;

}

/**
 * Fill the address of jump at a specific line in instruction memory.
 * Note that we patch juste before the target line in order to jump correctly
 * @param mem
 * @param line : the target instruction for the jump
 */
int mi_patch_jump(MemoireInstr * mem, int line) {
	Node * node = n_get(mem->first, (line - I_PADDING)/I_PADDING);


	if(node->instruction->operation != op_jmp && node->instruction->operation != op_jmpc) {
		printf("\n[Error] mi_patch_jump is trying to modify a not jump instruction: \n");
		i_print(node->instruction);
	}

	i_setAddress(node->instruction, mem->last_address);
}

/**
 * Translate the instruction memory in asm code an save it in file
 * @param mem
 * @param filename
 */
void mi_write(MemoireInstr * mem, char * filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		perror("Error opening file : ");
		return;
	}

	Node * node = mem->first;
	while(node != NULL) {
		fprintf(file, "%s\n", i_to_string(node->instruction));
		node = node->next;
	}

	fclose(file);
}