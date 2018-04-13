#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {s_int, s_float, s_char, s_void} TypeSymbol;

typedef struct {
	char * 	symbol;
	int		depth;
	int		adr;
	TypeSymbol	type;
} Symbol;

/**
 * Create a new symbol by associating his name with his address
 * @param symstr : 	variable name ("tmp" for temporary name)
 * @param type : 	see TypeSymbol
 * @param adr :		address assigment from symtab
 * @return new symbol
 */
Symbol * new_Symbol(char * symstr, TypeSymbol type, int adr);

/**
 * Return size defined by its type. This function provides an abstract approach
 * @param symbol
 * @return its size in octets
 */
int s_size(Symbol* symbol);

/**
 * Free and clean the given symbol, associate NULL to the pointer
 * @param symbol
 */
void s_delete(Symbol* symbol);

/**
 * Print the symbol in json format
 * @param symbol
 */
void s_print(Symbol * symbol);

/**
 * Convert variable type in string
 * @param type
 * @return string
 */
char * typeToString(TypeSymbol type);

/**
 * Check if symbol has the identified name and depth
 * @param symbol
 * @param new_symbol
 * @param depth
 * @return 1 if true, else 0
 */
int s_equals(Symbol * symbol, char * new_symbol, int depth);
