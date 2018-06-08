#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"

#ifndef SYMBOLTAB_H
#define SYMBOLTAB_H

#define TABMAX 1000

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
 * Delete symbol greater then this depth
 * @param depth
 */
void ts_clean_depth(SymbolTab * tab, int depth);

/**
 * push new symbol to tab
 * @param tab
 * @param symstr
 * @param type
 * @param depth
 * @return
 */
ErrorSymbolTab ts_push(SymbolTab * tab, char * symstr, TypeSymbol type, int depth);

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

#endif