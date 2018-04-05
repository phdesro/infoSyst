%code requires {
	#include <stdio.h>
	#include "symboltab.h"
}

%union { 
	char str[80]; 
	int nb; 
	TypeSymbol lxType;
}
%left tOPADD tOPSUB
%left tOPMUL tOPDIV

%{
	int yylex(void);
	void yyerror(char*);

	TypeSymbol type_tmp;
	SymbolTab * symbolTable;
%}

%token tID tNB tFCT_MAIN tFCT_PRINTF
%token tCONST tINT tFLOAT tCHAR tVOID
%token tFIN_L tTAB tSPACE
%token tAO tAF tVIRGULE tPO tPF tFIN_I tQUOTEDOUBLE tQUOTESIMPLE
%token tOPADD tOPSUB tOPDIV tOPMUL tOPEQU
%token tEQU tSUP tSUPEQU tINF tINFEQU tDIF
%token tIF tELSE tWHILE 

%type <str> tID
%type <nb> tNB
%type <lxType> Type tINT tFLOAT tCHAR tVOID

%%

//	(MiseEnPage)* Main (MiseEnPage)*
S:	_ Main _;
	

//	{ (Body_line)* }
Function_body: _ tAO Body_line tAF;

Body_line:	_ Body_line
			| Instruction Body_line
			| _;

Instruction: Call_function 
			| Declaration 
			| Affectation
			| If;

Main: 		tFCT_MAIN tPO Params { printf("\n");} tPF Function_body { printf("main_fin\n");}
			| tFCT_MAIN tPO _ tPF Function_body { printf("main_fin\n");};

/*-------------- Syntaxes conditionnelles --------------*/

If:			tIF Condition_stmt _ Instruction { printf("if_fin\n");}
			| tIF Condition_stmt _ tAO Body_line tAF { printf("if_fin\n");};

Condition_stmt: tPO _ Condition _ tPF;

Condition:	Condition _ tCOND _ Condition
			| tID
			| tNB;

tCOND: 		tEQU
			| tSUP
			| tSUPEQU
			| tINF
			| tINFEQU
			| tDIF;

/*-------------- Instructions --------------*/

// { type_tmp = $1 } permet de mémoriser le type temporairement en variable global avant de descendre plus bas
Declaration: Type { type_tmp = $1; } _ Params tFIN_I {	printf("Declaration_fin\n");	};

Affectation: tID _ tOPEQU _ Expression _ tFIN_I;

Expression:	Expression tOp Expression
			| tPO Expression tPF
			| tID
			| tNB;

tOp: 		tOPADD 
			| tOPSUB 
			| tOPDIV 
			| tOPMUL ;

/*-------------- Functions specifiques --------------*/
Call_function:
	Printf tFIN_I; 

Printf:		tFCT_PRINTF tPO tID tPF 							{ printf("printf -> %s\n", $3);	}
			| tFCT_PRINTF tPO tQUOTEDOUBLE tID tQUOTEDOUBLE tPF { printf("printf -> %s\n", $4); };


//	""|Param | (Param,)* 
Params:		Param tVIRGULE Params
			| Param;

Param:	_ tID _	{
					printf("Param %s ",$2);
					ErrorSymbolTab err = pushSymbol(symbolTable, $2, type_tmp); 
					switch(err)	{
						case st_success: break; 
						case st_full: printf(">> symtab full << "); break;
						case st_existed: printf(">> existed symbol << "); break;
						default: printf(">> cas not handled <<");
					}
				};

// (Carac MiseEnPage)* 
_:	Caractere_MiseEnPage _ 
			|;

Caractere_MiseEnPage: tTAB 
			| tSPACE 
			| tFIN_L;

// Gestion de typage
Type:		tINT 
			| tVOID
			| tCHAR
			| tFLOAT { $$ = $1; };
%%

int main(void) {
	symbolTable = new_SymbolTab();
	//init();
	
	yyparse();
	printSymbolTab(symbolTable);
}
