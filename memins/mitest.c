#include "meminstr.h"
#include <stdio.h>
#include <stdlib.h>

int main()	{
	
	printf("========================== test memoire d'instructions ============================\n");		

	MemoireInstr * mem = new_MemoireInstr();
	printf("\nEmpty Mem =======================\n");	
	mi_print(mem);

	printf("\nPush op_add =======================\n");	
	mi_push(mem,new_Instruction(op_add, 0, 0 ,1));
	mi_print(mem);


	printf("\nPush op_afc 3, push op_store =======================\n");	
	mi_push(mem, new_Instruction(op_afc, 0, 3));
	mi_push(mem, new_Instruction(op_store, 2, 2));
	mi_print(mem);
	
/*
	printf("\nPush symbol_2 =======================\n");	
	ts_push(tab,"symbol_2");
	ts_print(tab);*/

	return 0;
}
