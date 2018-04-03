#include "symbol.h"

Symbol * new_Symbol(char * symstr, TypeSymbol type)	{
	Symbol * sym = malloc(sizeof(Symbol));
	sym->symbol = malloc(strlen(symstr));

	strcpy(sym->symbol, symstr);

	sym->depth = 0;
	sym->type = type;
	return sym;
}

int sizeSymbol(Symbol* symbol)	{
	switch(symbol->type)	{
		case s_int: 	return 16;
		case s_float: 	return 32;
		case s_char: 	return 8;
		default : 		return -1;	
	}
}

int deleteSymbol(Symbol* symbol)	{
	free(symbol->symbol);
	free(symbol);
	symbol = NULL;
}

void printSymbol(Symbol * symbol)	{
	printf("{ symbol = %s, depth = %d, type = %s}", symbol->symbol, symbol->depth, typeToString(symbol->type));
}

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

int equalsSymbol(Symbol * symbol, char * new_symbol) {
	if (strcmp(symbol->symbol, new_symbol) == 0)
		return 1;
	return 0;
}
