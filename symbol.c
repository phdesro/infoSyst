enum TypeSymbol {s_int};

typedef struct {
	char* 	symbol;
	int		depth;
	TypeSymbol	type;
} Symbol;

Symbol * new_Symbol(char * symbol)	{
	Symbol * sym = malloc(sizeof(Symbol));
	strcpy(sym->symbol, symbol);
	sym->depth = 0;
	sym->type = s_int;
	return sym;
}

int sizeSymbol(Typebol* symbol)	{
	switch(symbol->type)	{
		case s_int: return 16;
		default : return -1;	
	}
}

void printSymbol(Symbol * symbol)	{
	printf("{ symbol = %s, depth = %d}", symbol->symbol, symbol->depth);
}
