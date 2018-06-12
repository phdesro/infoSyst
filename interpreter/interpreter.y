%code requires {
	#include <stdio.h>
	#include <string.h>

	#include "../memins/meminstr.h"
	#include "machine/machine.h"

    /* --------------------- Modifiez le MODE en 1 pour afficher le mémoire d'instruction -------------------------- */
    #define VIRTUAL_MACHINE 0
    #define BINARY 1
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

    if(VIRTUAL_MACHINE) {
        m_print(machine);
    }

    if(BINARY) {
        printf("Binary mode activated\n");
        m_binary(machine, "test.hex");
        printf("Binary code has been written in 'test.hex' file\n");
    }


}
