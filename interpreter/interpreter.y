%code requires {
	#include <stdio.h>
	#include <string.h>

	#include "memins/opcode.h"
}

%union {
	char* str;
	int nb; 
	TypeSymbol lxType;
	OpCode lxOp;
}

%{
	int yylex(void);
	void yyerror(char*);

	Machine * machine = new_Machine();
%}

%token tID tNB tFCT_MAIN tFCT_PRINTF

%nonassoc tIFX
%nonassoc tELSE

%%

//	starting point
S: Body_line ;

Body_line:	Instruction Body_line
			| Instruction;

%%

void init() {

}

int main(void) {
	init();
	yyparse();
}
