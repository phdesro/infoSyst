%code requires {
	#include <stdio.h>
	#include <string.h>

	#include "../memins/meminstr.h"
	#include "machine/machine.h"

    /* --------------------- Modifiez le MODE en 1 pour afficher le mémoire d'instruction -------------------------- */
    #define MODE 0
    /* ------------------------------------------------------------------------------------------------------------- */
}

%union {
	char* str;
	int nb;
	OpCode lxOp;
}

%{
	int yylex(void);
	void yyerror(char*);

	Machine * machine;
%}

%token tID tINT tOP

%type <lxOp> tOP
%type <nb> tINT

%nonassoc tIFX
%nonassoc tELSE

%%

//	starting point
S:      	Instruction S
			| Instruction;

Instruction: tOP tINT tINT tINT { m_load_instruction(machine , new_Instruction($1, $2, $3, $4));  }
            | tOP tINT tINT     { m_load_instruction(machine , new_Instruction($1, $2, $3));  }
            | tOP tINT          { m_load_instruction(machine , new_Instruction($1, $2));  }
            | tOP               { m_load_instruction(machine , new_Instruction($1)); }

%%

void init() {
    machine = new_Machine();
}

int main(void) {
	init();
	yyparse();

    m_launch(machine);

    if(MODE) {
        m_print(machine);
    }


}