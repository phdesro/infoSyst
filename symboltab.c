#include "symboltab.h"

SymbolTab * new_SymbolTab() {
	SymbolTab * tab = malloc(sizeof(SymbolTab));
	tab->last_adr = 0;
	tab->index = -1;
	for(int i = 0; i < TABMAX; i++)	{
		tab->symbols[i] = NULL;	
	}
}

int last_adr(SymbolTab * tab)	{
	return tab->last_adr;
}

ErrorSymbolTab pushSymbol(SymbolTab * tab, char * symstr, TypeSymbol type)	{
	
	if(getIndexSymbolTab(tab, symstr) > -1) {
		// printf("Symbol already existed\n");
		// return NULL;
		return st_existed;
	}

	if(tab->index > TABMAX)	{
		// printf("Symbol table full\n");
		// return NULL;	
		return st_full;
	}

	Symbol * symbol;
	tab->index++;
	symbol = new_Symbol(symstr, type);
	
	tab->symbols[tab->index] = symbol;
	tab->last_adr += sizeSymbol(symbol);

	return st_success;
}

Symbol * popSymbol(SymbolTab * tab)	{

	if(tab->index < 0)	{
		printf("Symbol table empty\n");
		return NULL;	
	}

	Symbol * symbol = tab->symbols[tab->index];

	tab->last_adr -= sizeSymbol(symbol);
	tab->index--;
	return symbol;
}

void printSymbolTab(SymbolTab * tab) {

	printf("Symbol Tab : {\n");
	printf("\tsize : %d,\n", tab->index + 1);
	printf("\tlast_adr : %d,\n", tab->last_adr);
	printf("\t[\n");
	if(tab->index > -1)	{
		for(int i = 0; i <= tab->index; i++)	{
			printf("\t\t");
			printSymbol(tab->symbols[i]);
			if(i > 0) 
				printf(",");
			printf("\n");
		}
	}	
	printf("\t]\n");
	printf("}\n");
}

/*================== PRIVATE ========================*/
int getIndexSymbolTab(SymbolTab * tab, char * symstr) {
	
	if(tab->index == -1)
		return -1;

	for(int i = 0; i <= tab->index; i++) {
		if(equalsSymbol(tab->symbols[i], symstr))
			return i;	
	}

	return -1;
}

/*
int main()	{
	
	printf("========================== test symbol tab ============================\n");		

	SymbolTab * tab = new_SymbolTab();
	printf("\nEmpty table =======================\n");	
	printSymbolTab(tab);

	printf("\nPush symbol_1 =======================\n");	
	pushSymbol(tab,"symbol_1");
	printSymbolTab(tab);

	printf("\nPush symbol_2, push symbol_3, pop =======================\n");	
	pushSymbol(tab,"symbol_2");
	pushSymbol(tab,"symbol_3");
	popSymbol(tab);	
	printSymbolTab(tab);

	printf("\nPush symbol_2 =======================\n");	
	pushSymbol(tab,"symbol_2");
	printSymbolTab(tab);

	return 0;
}*/
