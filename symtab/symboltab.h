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

/**
 * Get last memorized address
 * @param tab
 * @return
 */
int ts_peek(SymbolTab * tab);

/**
 * Pop last memorized address, the last element will be deleted and index will be updated
 * @param tab
 * @return last address
 */
int ts_pop(SymbolTab * tab);

/**
 * push new symbol to tab
 * @return : enum ErrorSymbolTab (st_success, st_full, st_existed)
 */
ErrorSymbolTab ts_push(SymbolTab * tab, char * symstr, TypeSymbol type);

/**
 * Pop the last symbol from tab
 * @param tab
 * @return the last symbol
 */
Symbol * ts_popSymbol(SymbolTab * tab);

/**
 * Print out the tab with JSON format
 * @param tab
 */
void ts_print(SymbolTab * tab);

/**
 * Check if symbol within depth exists already in table
 * @param tab
 * @param symstr
 * @param depth
 * @return 1 existing, 0 inexisting
 */
int ts_exists(SymbolTab * tab, char * symstr, int depth);

/**
 * Get addess of the closest symbol in SymbolTab that has the highest existing depth
 * @param tab
 * @param symstr
 * @return > 0 if found, else -1
 */
int ts_getAdr(SymbolTab * tab, char * symstr);
