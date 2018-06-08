#include "machine.h"

Machine * new_Machine() {
	Machine * tmp = malloc(sizeof(Machine));

	for(int i = 0; i < NB_REGISTER; i++)	tmp->regs[i] = M_NOT_INIT;

	tmp->data_memory = malloc(sizeof(int) * MEMORY_PADDING);
	tmp->max_data = MEMORY_PADDING;
	for(int i = 0; i < tmp->max_data; i++) {
		tmp->data_memory[i] = M_UNDEFINED;
	}
//	tmp->current_data = 0;

	tmp->max_instruction = MEMORY_PADDING;
	tmp->instruction_memory = malloc(sizeof(Instruction *) * MEMORY_PADDING);
	tmp->current_instruction = -1;
	tmp->address = 0;

	tmp->program_counter = 0;
	return tmp;
}

void m_load_instruction(Machine * machine, Instruction * instruction) {

	if(machine->current_instruction >= machine->max_instruction - 1) {
		// extends memory
		Instruction ** tmp = malloc(sizeof(Instruction *) * (machine->max_instruction + MEMORY_PADDING));
		for(int i = 0; i < machine->max_instruction; i++)
			tmp[i] = machine->instruction_memory[i];

		free(machine->instruction_memory);
		machine->instruction_memory = tmp;
		machine->max_instruction += MEMORY_PADDING;
	}

	machine->current_instruction++;
	instruction->address = machine->address;
	machine->instruction_memory[machine->current_instruction] = instruction;
	machine->address += I_PADDING;

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

	//TODO need a proper version:
	address = address / 16;

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
	return 1;
}

int m_load_reg(Machine * machine, int reg, int address) {

	//TODO need a proper version:
	address = address / 16;

	if(address > machine->max_data) {
		printf("Segmentation false: Trying to access to data %d while machine data space is only %d\n", address, machine->max_data);
		machine->regs[reg] = machine->data_memory[address];
		return 0;
	}
	machine->regs[reg] = machine->data_memory[address];
	return 1;
}

int m_jump(Machine * machine, int address) {
	if(address/I_PADDING > machine->current_instruction) {
		printf("Segmentation false: Trying to exec instruction at @%d while only have %d instructions (max address %d)\n", address, machine->current_instruction, machine->address - I_PADDING);
		return 0;
	}
	machine->program_counter = address/I_PADDING - 1;
	return 1;
}

void m_launch(Machine * machine) {

	while(machine->program_counter <= machine->current_instruction) {
		if(!i_execute(machine, machine->instruction_memory[machine->program_counter])) {
			printf("Error when execute instruction ");
			i_print(machine->instruction_memory[machine->program_counter]);
			break;
		}
		machine->program_counter++;
	}

	printf("Execution terminated\n");
}

int m_echo(Machine * machine, int reg) {
	if(reg >= NB_REGISTER) {
		printf("Access to register %d", reg);
		return 0;
	}
	printf("%d\n", machine->regs[reg]);
	return 1;
}

void m_print(Machine * machine) {

	printf("Virtual machine : {\n");
	printf("\tmax_data: %d,\n", machine->max_data);
//	printf("\tcurrent_data: %d,\n", machine->current_data);
	printf("\tmax_instruction: %d,\n", machine->max_instruction);
	printf("\tcurrent_instruction: %d,\n", machine->current_instruction);

	// register bank
	printf("\tRegisters (0 -> %d) : [", NB_REGISTER - 1);
	for(int i = 0; i < NB_REGISTER; i++) {
		if(i > 0) printf(", ");

		switch(machine->regs[i]) {
			case M_UNDEFINED:
				printf("UUUU");
				break;
			case M_NOT_INIT:
				printf("XXXX");
				break;
			default:
				printf("%d", machine->regs[i]);
				break;
		}
	}
	printf("],\n");

	// instruction memory
	printf("\tInstruction memory: [\n");
	for(int i = 0; i <= machine->current_instruction; i++) {
		printf("\t\t");
		i_print(machine->instruction_memory[i]);
	}
	printf("\t]\n");

	// data memory
	printf("\tData memory: [ ");
	for(int i = 0; i < machine->max_data; i++) {
		if(i > 0)
			printf(", ");

		switch( machine->data_memory[i]) {
			case M_UNDEFINED:
				printf("UUUU");
				break;
			case M_NOT_INIT:
				printf("XXXX");
				break;
			default:
				printf("%d",  machine->data_memory[i]);
				break;
		}
	}
	printf("]\n");

	printf("}\n");
}