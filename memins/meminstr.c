#include "meminstr.h"

MemoireInstr * new_MemoireInstr() {
	MemoireInstr * mem = malloc(sizeof(MemoireInstr));
	mem->first = NULL;
	mem->last = NULL;
	return mem;
}

void mi_push(MemoireInstr * mem, Instruction * instruction) {

	Node * node = new_Node(instruction);

	if(mem->first == NULL) {
		mem->first = node;	
	} 

	if(mem->last != NULL) {
		mem->last->next = node;	
	} 

	mem->last = node;
}

void mi_print(MemoireInstr * mem) {
	printf("Memoire Instruction : [\n");


	Node * node = mem->first;
	while(node != NULL) {
		i_print(node->instruction);
		node = node->next;
	}

	printf("]\n");

}

// private

Node * new_Node(Instruction * instruction) {
	Node * node = malloc(sizeof(Node));
	node->instruction = instruction;
	node->next = NULL;
	return node;
}
