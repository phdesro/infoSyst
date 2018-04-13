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

// Init un nouveau symbol à partir de son id 
Symbol * new_Symbol(char * symstr, TypeSymbol type, int adr);

// Get size
int s_size(Symbol* symbol);

// Delete contenu du symbol
int s_delete(Symbol* symbol);

// Afficher le symbol
void s_print(Symbol * symbol);

// Traduire le type enum en chaine de charactere
char * typeToString(TypeSymbol type);

// Check if equals return 1, else return 0
int s_equals(Symbol * symbol, char * new_symbol, int depth);
