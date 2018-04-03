#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {s_int, s_float} TypeSymbol;

typedef struct {
	char * 	symbol;
	int		depth;
	TypeSymbol	type;
} Symbol;

// Init un nouveau symbol à partir de son id 
Symbol * new_Symbol(char * symstr, TypeSymbol type);

// Get size
int sizeSymbol(Symbol* symbol);

// Delete contenu du symbol
int deleteSymbol(Symbol* symbol);

// Afficher le symbol
void printSymbol(Symbol * symbol);

// Traduire le type enum en chaine de charactere
char * typeToString(TypeSymbol type);

// Check if equals return 1, else return 0
int equalsSymbol(Symbol * symbol, char * new_symbol);
