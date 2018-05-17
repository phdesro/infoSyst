#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"

#ifndef MEMINSTR_H
#define MEMINSTR_H

#define PADDING 4

// ================ private ================ //
typedef struct Node {
	Instruction * instruction;
	struct Node * next;
} Node;

Node * new_Node();

/**
 * Get node(index) in linked list of index
 * @param node
 * @param index >= 0
 * @return Node *
 */
Node * n_get(Node * node, int index);	// TODO: Should we get and remove the node right away?

void n_delete(Node * node);

// ================ public ================ //

typedef struct  {

    Node * first;		// first instruction node in table
    Node * last;		// last instruction node in table

    Node * first_jump;		// first jump in waiting filled jump list (jump list)
	Node * last_jump;		// last jump in jump list
	int nb_jump;			// nb of jump, use when calculate the distance

    int last_address;	// address of the lastest instruction (aka. in last)

	// structure is like the following:
	// MemoireInstr
	//	| first (node) -> node -> node -> ... -> last
	//	| first jump (node) -> node (uncompleted jump) -> node -> ... -> last jump
	//	| last address
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

/**
 * Fill the current address to jump
 * @param mem
 * @param address
 * @param move_cursor
 */
void mi_fill_jump(MemoireInstr * mem, int distance);

/**
 * Translate the instruction memory in asm code an save it in file
 * @param mem
 * @param filename
 */
void mi_write(MemoireInstr * mem, char * filename);

#endif