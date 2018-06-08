#include "symboltab.h"

#include <stdio.h>
#include <stdlib.h>

int main()	{

	printf("========================== test symbol tab ============================\n");

	SymbolTab * tab = new_SymbolTab();
	printf("\nEmpty table =======================\n");
	ts_print(tab);

	printf("\nPush symbol_1 =======================\n");
	ts_push(tab,"symbol_1", s_int, 0);
	ts_print(tab);

	printf("\nPush symbol_2, push symbol_3, pop =======================\n");
	ts_push(tab,"symbol_2", s_float, 0);
	ts_push(tab,"symbol_3", s_char, 0);
	ts_pop(tab);
	ts_print(tab);

	printf("\nPush symbol_2 =======================\n");
	ts_push(tab,"symbol_2", s_int, 0);
	ts_print(tab);

	return 0;
}
