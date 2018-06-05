#ifndef INFOSYST_MACHINE_H
#define INFOSYST_MACHINE_H

#include <stdlib.h>
#include "../../memins/meminstr.h"

#define MEMORY_PADDING 20
#define SYSTEM 8 		// bits
#define NB_REGISTER 10

#define M_NOT_INIT	-2147483646
#define M_UNDEFINED -2147483647

/**
 * Virtual machine having :
 * - register bank
 * - instruction memory
 * - memory in hard disk
 */
typedef struct {
	int regs[NB_REGISTER];

	// instruction memory
	Instruction ** instruction_memory;
	int max_instruction;
	int current_instruction;

	int program_counter;

	// data memory
	int * data_memory;
	int max_data;
//	int current_data;
	//TODO stack and heap?

} Machine;

// include here so that we avoid error when executer need to know machine structure
#include "../executer/executer.h"

Machine * new_Machine();

void m_load_instruction(Machine * machine, Instruction * instruction);

void m_launch(Machine * machine);

/**
 * Set value into a register
 * @param machine
 * @param reg
 * @param value
 * @return 1 if success, 0 if fail
 */
int m_set_reg(Machine * machine, int reg, int value);

/**
 * Store value in register to a data memory at a specific address
 * @param machine
 * @param reg
 * @param address
 * @return 1 if success, 0 if fail
 */
int m_store_reg(Machine * machine, int reg, int address);

/**
 * Get value from a data address and set it into the register
 * @param machine
 * @param reg
 * @param address
 * @return 1 if success, 0 if fail
 */
int m_load_reg(Machine * machine, int reg, int address);

/**
 * Affect the address to pc in order to make a jump
 * @param machine
 * @param address
 * @return
 */
int m_jump(Machine * machine, int address);

int m_echo(Machine * machine, int reg);

/**
 * Display virtual machine
 * @param machine
 */
void m_print(Machine * machine);

#endif //INFOSYST_MACHINE_H
