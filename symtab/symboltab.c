#include "symboltab.h"

SymbolTab * new_SymbolTab() {
	SymbolTab * tab = malloc(sizeof(SymbolTab));
	tab->last_adr = -1;
	tab->index = -1;
	for(int i = 0; i < TABMAX; i++)	{
		tab->symbols[i] = NULL;	
	}
}

/**
 * Get last memorized address
 * @param tab
 * @return
 */
int ts_peek(SymbolTab * tab)	{
	return tab->last_adr;
}

/**
 * Pop last memorized address, the last element will be deleted and index will be updated
 * @param tab
 * @return last address
 */
int ts_pop(SymbolTab * tab)	{
	int last_adr = ts_peek(tab);
	Symbol * sym = ts_popSymbol(tab);	
	s_delete(sym);
	return last_adr;
}

/**
 * Delete symbol greater then this depth
 * @param depth
 */
void ts_clean_depth(SymbolTab * tab, int depth) {
	int i;
	for(i = tab->index; i >= 0 && tab->symbols[i]->depth >= depth; i--) {
		Symbol * sym = tab->symbols[i];
		s_delete(sym);
	}
	tab->index = i;
}

/**
 * push new symbol to tab
 * @param tab
 * @param symstr
 * @param type
 * @param depth
 * @return
 */
ErrorSymbolTab ts_push(SymbolTab * tab, char * symstr, TypeSymbol type, int depth)	{

	// assert: st is full
	if(tab->index > TABMAX - 2)	{
		printf("\n[error] symbol table is full\n");
		return st_full;
	}

	// assert: symbol already existed
	for(int i = 0; i <= tab->index; i++) {
		int not_tmp = !strcmp(tab->symbols[i]->symbol, "tmp") == 0;
		int same_name = strcmp(tab->symbols[i]->symbol, symstr) == 0;
		int same_depth = tab->symbols[i]->depth == depth;

		if(not_tmp && same_name && same_depth) {

			printf("\n[error] %s already existed\n", symstr);
			return st_existed;
		}
	}

	// compute last_adr
	if(tab->last_adr < 0)
		tab->last_adr = 0;
	else {
		tab->last_adr += s_size(tab->symbols[tab->index]);
	}

	Symbol * symbol = new_Symbol(symstr, type, tab->last_adr, depth);

	tab->index++;	
	tab->symbols[tab->index] = symbol;

	return st_success;
}

/**
 * Pop the last symbol from tab
 * @param tab
 * @return the last symbol
 */
Symbol * ts_popSymbol(SymbolTab * tab)	{

	if(tab->index < 0)	{
		printf("Symbol table empty\n");
		return NULL;	
	}

	Symbol * symbol = tab->symbols[tab->index];

	tab->last_adr -= s_size(symbol);
	tab->index--;
	return symbol;
}

/**
 * Print out the tab with JSON format
 * @param tab
 */
void ts_print(SymbolTab * tab) {

	printf("Symbol Table : {\n");
	printf("\tsize : %d,\n", tab->index + 1);
	printf("\tlast_adr : %d,\n", tab->last_adr);
	printf("\t[\n");
	if(tab->index > -1)	{
		for(int i = 0; i <= tab->index; i++)	{
			printf("\t\t");
			s_print(tab->symbols[i]);
			if(i > 0) 
				printf(",");
			printf("\n");
		}
	}	
	printf("\t]\n");
	printf("}\n");
}

/**
 * Check if symbol within depth exists already in table
 * @param tab
 * @param symstr
 * @param depth
 * @return 1 existing, 0 inexisting
 */
int ts_exists(SymbolTab * tab, char * symstr, int depth) {
	if(tab->index == -1)
		return 0;

	for(int i = 0; i <= tab->index; i++) {
		if(s_equals(tab->symbols[i], symstr, depth))
			return 1;	
	}

	return 0;
}

/**
 * Get addess of the closest symbol in SymbolTab that has the highest existing depth
 * @param tab
 * @param symstr
 * @return > 0 if found, else -1
 */
int ts_getAdr(SymbolTab * tab, char * symstr)	{
	if(tab->index < 0)	{
		return -1;	
	}
	
	for(int i = tab->index; i >= 0; i--) {
		if(s_equals(tab->symbols[i], symstr, -1))	{
			return tab->symbols[i]->adr;
		}
	}
	return -1;
}
