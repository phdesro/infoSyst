#include "executer.h"

int i_execute(Machine * machine, Instruction * instruction) {

	int p0 = instruction->param[0];
	int p1 = instruction->param[1];
	int p2 = instruction->param[2];


	switch(instruction->operation) {

		// arithmetics
		case op_add:
			return m_set_reg(machine, p0, machine->regs[p1] + machine->regs[p2]);
		case op_sub:
			return m_set_reg(machine, p0, machine->regs[p1] - machine->regs[p2]);
		case op_mul:
			return m_set_reg(machine, p0, machine->regs[p1] * machine->regs[p2]);
		case op_div:
			return m_set_reg(machine, p0, machine->regs[p1] / machine->regs[p2]);

		// logics
		case op_equ:
			return m_set_reg(machine, p0, machine->regs[p1] == machine->regs[p2]);
		case op_infe:
			return m_set_reg(machine, p0, machine->regs[p1] <= machine->regs[p2]);
		case op_inf:
			return m_set_reg(machine, p0, machine->regs[p1] < machine->regs[p2]);
		case op_sup:
			return m_set_reg(machine, p0, machine->regs[p1] > machine->regs[p2]);
		case op_supe:
			return m_set_reg(machine, p0, machine->regs[p1] >= machine->regs[p2]);
		case op_dif:
			return m_set_reg(machine, p0, machine->regs[p1] != machine->regs[p2]);

		case op_afc:
			return m_set_reg(machine, p0, p1);
		case op_load:
			return m_load_reg(machine, p0, p1);
		case op_store:
			return m_store_reg(machine, p0, p1);

		case op_jmpc:
			if(p1 != 0)
				return 1;
		case op_jmp:
			return m_jump(machine, p0);

		case op_echo:
			return m_echo(machine, p0);

		default:
			printf("Unsupported operation : %s\n", op_string(instruction->operation));
			return 0;

	}
}