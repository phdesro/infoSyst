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
int ts_peek(SymbolTab * tab);

// pop last memorized address 
int ts_pop(SymbolTab * tab);

/**
 * push new symbol to tab
 * @return : 0 if success, 1 if already exist, 0 if full table
 */
ErrorSymbolTab ts_push(SymbolTab * tab, char * symstr, TypeSymbol type);

// pop the last symbol from tab, return the popped symbol
Symbol * ts_popSymbol(SymbolTab * tab);


// print out the tab with format json
void ts_print(SymbolTab * tab);

//
int ts_exists(SymbolTab * tab, char * symstr, int depth);

int ts_getAdr(SymbolTab * tab, char * symstr);
