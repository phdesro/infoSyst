#include "symbol.h"

/**
 * Create a new symbol by associating his name with his address
 * @param symstr : 	variable name ("tmp" for temporary name)
 * @param type : 	see TypeSymbol
 * @param adr :		address assigment from symtab
 * @param depth:	depth
 * @return new symbol
 */
Symbol * new_Symbol(char * symstr, TypeSymbol type, int adr, int depth)	{
	Symbol * sym = malloc(sizeof(Symbol));
	sym->symbol = malloc(strlen(symstr));

	strcpy(sym->symbol, symstr);

	sym->depth = depth;
	sym->type = type;

	sym->adr = adr;

	return sym;
}

/**
 * Return size defined by its type. This function provides an abstract approach
 * @param symbol
 * @return its size in octets
 */
int s_size(Symbol* symbol)	{
	switch(symbol->type)	{
		case s_int: 	return 16;
		case s_float: 	return 32;
		case s_char: 	return 8;
		default : 		return -1;	
	}
}

/**
 * Free and clean the given symbol, associate NULL to the pointer
 * @param symbol
 */
void s_delete(Symbol* symbol)	{
	free(symbol->symbol);
	free(symbol);
	symbol = NULL;
}

/**
 * Print the symbol in json format
 * @param symbol
 */
void s_print(Symbol * symbol)	{
	printf("{ symbol = %s, depth = %d, type = %s, adr = %d}", symbol->symbol, symbol->depth, typeToString(symbol->type), symbol->adr);
}

/**
 * Convert variable type in string
 * @param type
 * @return string
 */
char * typeToString(TypeSymbol type)	{
	switch(type)	{
		case s_int:
			return "int";
		case s_float:
			return "float";
		case s_char:
			return "char";
		case s_void:
			return "void";
		default:
			return "unknown";
	}
}

/**
 * Check if symbol has the identified name and depth
 * @param symbol
 * @param new_symbol
 * @param depth
 * @return 1 if true, else 0
 */
int s_equals(Symbol * symbol, char * new_symbol, int depth) {
	return strcmp(symbol->symbol, new_symbol) == 0;

}
