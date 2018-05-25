#include "machine.h"

Machine * new_Machine() {
	Machine * tmp = malloc(sizeof(Machine));

	tmp->data_memory = malloc(sizeof(int) * MEMORY_PADDING);
	tmp->max_data = MEMORY_PADDING;
	tmp->current_data = 0;

	tmp->max_instruction = MEMORY_PADDING;
	tmp->instruction_memory = malloc(sizeof(Instruction *) * MEMORY_PADDING);
	tmp->current_instruction = 0;

	tmp->program_counter = 0;
	return tmp;
}

void m_load_instruction(Machine * machine, Instruction * instruction) {



	if(machine->current_instruction >= machine->max_instruction) {
		// extends memory
		Instruction ** tmp = malloc(sizeof(Instruction *) * (machine->max_instruction + MEMORY_PADDING));
		for(int i = 0; i < machine->max_instruction; i++)
			tmp[i] = machine->instruction_memory[i];

		free(machine->instruction_memory);
		machine->instruction_memory = tmp;
		machine->max_instruction += MEMORY_PADDING;
	}

	machine->instruction_memory[machine->current_instruction] = instruction;
	machine->current_instruction++;
}

void m_launch(Machine * machine) {

	while(machine->program_counter <= machine->current_instruction) {
		printf("LOLOLOLO %d \n", machine->program_counter);
		i_execute(machine, machine->instruction_memory[machine->program_counter]);
		machine->program_counter ++;
	}
}

int m_set_reg(Machine * machine, int reg, int value) {
	if(reg >= NB_REGISTER)	{
		printf("Access to register %d", reg);
		return 0;
	}
	machine->regs[reg] = value;
	return 1;
}

int m_store_reg(Machine * machine, int reg, int address) {

	// in case addres > max + MEMORY_PADDING
	// we need to extends more than 1 time, but this is not really necessary
	while(address >= machine->max_data) {
		// extends memory
		int * tmp = malloc(sizeof(int) * (machine->max_data + MEMORY_PADDING));
		for(int i = 0; i < machine->max_data; i++)
			tmp[i] = machine->data_memory[i];

		free(machine->data_memory);
		machine->data_memory = tmp;
		machine->max_data += MEMORY_PADDING;
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

void m_print(Machine * machine) {

	printf("Virtual machine : {\n");

	// register bank
	printf("\tRegisters (0 -> %d) : [", NB_REGISTER - 1);
	for(int i = 0; i < NB_REGISTER -1; i++) {
		printf("%d, ", machine->regs[i]);
	}
	printf("%d]\n", machine->regs[NB_REGISTER - 1]);

	// memory instruction
	for(int i = 0; i < machine->current_instruction; i++) {
		i_print(machine->instruction_memory[i]);
	}

	printf("}\n");
}