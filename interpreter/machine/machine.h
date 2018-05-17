#ifndef INFOSYST_MACHINE_H
#define INFOSYST_MACHINE_H

#include <stdlib.h>
#include "../../memins/meminstr.h"

#define PADDING 255
#define SYSTEM 8 // bits

typedef struct {
	int regs[10];

	// instruction memory
	MemoireInstr * instruction_memory;
	int current_instruction;

	// data memory
	int * data_memory;
	int max_data;
	int current_data;

} Machine;

Machine * new_Machine();

void m_set_reg(Machine * machine, int reg, int value);

void m_store_reg(Machine * machine, int reg, int address);

void m_load_reg(Machine * machine, int reg, int address);

#endif //INFOSYST_MACHINE_H
