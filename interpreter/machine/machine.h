#ifndef INFOSYST_MACHINE_H
#define INFOSYST_MACHINE_H

#include <stdlib.h>
#include "../../memins/meminstr.h"


#define MEMORY_PADDING 255
#define SYSTEM 8 		// bits
#define NB_REGISTER 10

typedef struct {
	int regs[NB_REGISTER];

	// instruction memory
	MemoireInstr * instruction_memory;
	int current_instruction;

	// data memory
	int * data_memory;
	int max_data;
	int current_data;

} Machine;

Machine * new_Machine();

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

void m_print(Machine * machine);

#endif //INFOSYST_MACHINE_H
