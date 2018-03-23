#include "symbol.c"
#define TABMAX 255

typedef struct  {
    Symbol*	symbols[TABMAX];
	int 	index;
	int 	last_adr;
} SymbolTab;

SymbolTab * new_SymbolTab() {
	SymbolTab * tab = malloc(typeof(SymbolTab));
	tab->last_adr = 0;
	tab->index = -1;
	for(int i = 0; i < TABMAX; i++)	{
		symbols[i] = NULL;	
	}
}

int last_adr()	{
	return last_adr;
}

Symbol* pushSymbol(SymbolTab * tab, char * symbol)	{

	if(tab->index > TABMAX)	{
		printf("Symbol table full\n");
		return NULL;	
	}

	Symbol * symbol;
	tab->index++;
	symbol = new_Symbol(symbol);
	symbols[tab->index] = symbol;
	last_adr += sizeSymbol(symbol);
	return symbol;
}

Symbol * popSymbol(SymbolTab * tab)	{

	if(tab->index < 0)	{
		printf("Symbol table empty\n");
		return NULL;	
	}

	Symbol * symbol = symbols[tab->index];

	tab->last_adr -= sizeSymbol(symbol);
	tab->index--;
	return symbol;
}

void printSymbolTab(SymbolTab * tab) {
	printf("Symbol Tab : [\n");
	if(tab->index > -1)	{
		for(int i = 0; i < tab->index; i++)	{
			printf("\t");
			printSymbol(tab->symbols[i]);
			if(i > 0) printf(",\n"),
		}
	}	
	printf("]\n");
}

int main()	{
	SymbolTab * tab = new_SymbolTab();
	tab.pushSymbol("symbol_1");
	printSymbolTab(tab);
	return 0;
}
