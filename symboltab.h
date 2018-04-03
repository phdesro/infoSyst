#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"

#define TABMAX 255

typedef struct  {
    Symbol*	symbols[TABMAX];
	int 	index;
	int 	last_adr;
} SymbolTab;

// Constructor
SymbolTab * new_SymbolTab();

// get last memorized address 
int last_adr(SymbolTab * tab);

/**
 * push new symbol to tab
 * @return : new added symbol if success, NULL if error (already in table)
 */
Symbol * pushSymbol(SymbolTab * tab, char * symstr, TypeSymbol type);

// pop the last symbol from tab, return the popped symbol
Symbol * popSymbol(SymbolTab * tab);

// print out the tab with format json
void printSymbolTab(SymbolTab * tab);

/*================== PRIVATE ========================*/

// get index in table from tab
// return -1 if not exist
int getIndexSymbolTab(SymbolTab * tab, char * symstr);
