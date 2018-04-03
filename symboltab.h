#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"

#define TABMAX 255

typedef struct  {
    Symbol*	symbols[TABMAX];
	int 	index;
	int 	last_adr;
} SymbolTab;

typedef enum {st_success, st_full, st_existed} ErrorSymbolTab;

// Constructor
SymbolTab * new_SymbolTab();

// get last memorized address 
int last_adr(SymbolTab * tab);

/**
 * push new symbol to tab
 * @return : 0 if success, 1 if already exist, 0 if full table
 */
ErrorSymbolTab pushSymbol(SymbolTab * tab, char * symstr, TypeSymbol type);

// pop the last symbol from tab, return the popped symbol
Symbol * popSymbol(SymbolTab * tab);

// print out the tab with format json
void printSymbolTab(SymbolTab * tab);

/*================== PRIVATE ========================*/

// get index in table from tab
// return -1 if not exist
int getIndexSymbolTab(SymbolTab * tab, char * symstr);
