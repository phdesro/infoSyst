#include "symbol.h"

Symbol * new_Symbol(char * symstr, TypeSymbol type, int adr)	{
	Symbol * sym = malloc(sizeof(Symbol));
	sym->symbol = malloc(strlen(symstr));

	strcpy(sym->symbol, symstr);

	sym->depth = 0;
	sym->type = type;

	sym->adr = adr;

	return sym;
}

int s_size(Symbol* symbol)	{
	switch(symbol->type)	{
		case s_int: 	return 16;
		case s_float: 	return 32;
		case s_char: 	return 8;
		default : 		return -1;	
	}
}

int s_delete(Symbol* symbol)	{
	free(symbol->symbol);
	free(symbol);
	symbol = NULL;
}

void s_print(Symbol * symbol)	{
	printf("{ symbol = %s, depth = %d, type = %s, adr = %d}", symbol->symbol, symbol->depth, typeToString(symbol->type), symbol->adr);
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

int s_equals(Symbol * symbol, char * new_symbol, int depth) {
	if (strcmp(symbol->symbol, new_symbol) == 0 && (depth < 0 || symbol->depth == depth))
		return 1;
	return 0;
}
