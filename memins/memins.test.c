#include "meminstr.h"

#include <stdio.h>
#include <stdlib.h>

void basic_test(MemoireInstr * mem)	{
	printf("\nEmpty Mem =======================\n");
	mi_print(mem);

	printf("\nPush op_add =======================\n");
	mi_push(mem,new_Instruction(op_add, 0, 0 ,1));
	mi_print(mem);


	printf("\nPush op_afc 3, push op_store =======================\n");
	mi_push(mem, new_Instruction(op_afc, 0, 3));
	mi_push(mem, new_Instruction(op_store, 2, 2));
	mi_print(mem);
}

void if_test(MemoireInstr * mem) {

	printf("\nPush jump for if, then op mul =======================\n");
	mi_push(mem, new_Instruction(op_jmpc, I_ADR_UNFILLED, 0));
	mi_push(mem,new_Instruction(op_mul, 0, 0 ,1));

	printf("\nFill the jump and continue the instructions =======================\n");
	mi_fill_jump(mem, 0);
	mi_push(mem,new_Instruction(op_add, 0, 0 ,1));

	mi_print(mem);
}

void if_else_test(MemoireInstr * mem) {
	printf("\nPush first jump for if, then op mul =======================\n");
	mi_push(mem, new_Instruction(op_jmpc, I_ADR_UNFILLED, 0));
	mi_push(mem,new_Instruction(op_mul, 0, 0 ,1));
	mi_print(mem);


	printf("\nPush second jump in else =======================\n");
	mi_push(mem, new_Instruction(op_jmp, I_ADR_UNFILLED, 0));
	mi_print(mem);


	printf("\nFill the first jump =======================\n");
	mi_fill_jump(mem, 1);
	mi_print(mem);

	printf("\nPush an op_add and fill the last jump =======================\n");
	mi_push(mem,new_Instruction(op_add, 0, 0 ,1));
	mi_fill_jump(mem, 0);
	mi_print(mem);
}

int main()	{
	
	printf("========================== test memoire d'instructions ============================\n");		

	MemoireInstr * mem = new_MemoireInstr();

	basic_test(mem);

	if_else_test(mem);

	if_test(mem);

	mi_write(mem, "memins.test.asm");


	return 0;
}
