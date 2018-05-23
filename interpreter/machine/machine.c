#include "machine.h"

Machine * new_Machine() {
	Machine * tmp = malloc(sizeof(Machine));

	tmp->data_memory = malloc(sizeof(int) * PADDING);
	tmp->max_data = PADDING;
	tmp->current_data = 0;

	tmp->instruction_memory = new_MemoireInstr();
}

int m_set_reg(Machine * machine, int reg, int value) {
	if(reg >= NB_REG)	{
		printf("Access to register %d", reg);
		return 0;
	}
	machine->regs[reg] = value;
	return 1;
}

int m_store_reg(Machine * machine, int reg, int address) {

	// in case addres > max + PADDING
	// we need to extends more than 1 time, but this is not really necessary
	while(address >= machine->max_data) {
		// extends memory
		int * tmp = malloc(sizeof(int) * (machine->max_data + PADDING));
		for(int i = 0; i < machine->max_data; i++)
			tmp[i] = machine->data_memory[i];

		free(machine->data_memory);
		machine->data_memory = tmp;
	}

	machine->data_memory[address] = machine->regs[reg];
}

int m_load_reg(Machine * machine, int reg, int address) {
	if(address > machine->current_data) {
		printf("Core dump: segmentation false");
		return 0;
	}
	machine->regs[reg] = machine->data_memory[address];
}