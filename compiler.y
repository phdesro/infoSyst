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
%token tCONST tINT tFLOAT
%token tFIN_L tTAB tSPACE
%token tAO tAF tVIRGULE tPO tPF tFIN_I tQUOTEDOUBLE tQUOTESIMPLE
%token tOPADD tOPSUB tOPDIV tOPMUL tOPEQU

%type <str> tID
%type <nb> tNB
%type <lxType> tINT tFLOAT Type

%%

/* 
	(MiseEnPage)* Main (MiseEnPage)*
*/
S:	MiseEnPage Main MiseEnPage;
	
/*
	{ (Body_line)* }
*/
Function_body: MiseEnPage tAO Body_line tAF;

/*
	MiseEnPage | 
*/
Body_line:	MiseEnPage Body_line;
Body_line:	Instruction Body_line;
Body_line: 	MiseEnPage;

Instruction: Call_function | Declaration | Affectation;

Main: tFCT_MAIN tPO Params tPF Function_body { printf("main reconnu\n");};
Main: tFCT_MAIN tPO MiseEnPage tPF Function_body { printf("main reconnu\n");};

/*-------------- Instruction --------------*/

// { type_tmp = $1 } permet de mémoriser le type temporairement en variable global avant de descendre plus bas
Declaration: Type { type_tmp = $1; } MiseEnPage Params tFIN_I {	printf("declaration de var\n");	};

Affectation: tID MiseEnPage tOPEQU MiseEnPage Expression MiseEnPage tFIN_I;

Expression: Expression tOp Expression;
Expression: tPO Expression tPF;
Expression: tID;
Expression: tNB;

tOp	: tOPADD 
	| tOPSUB 
	| tOPDIV 
	| tOPMUL ;

/* 
	[les fonctions] ;
*/
Call_function:
	Printf tFIN_I; 

Printf:
	tFCT_PRINTF tPO tID tPF 
			{ printf("printf -> %s\n", $3);	};
Printf:
	tFCT_PRINTF tPO tQUOTEDOUBLE tID tQUOTEDOUBLE tPF  
			{ printf("printf -> %s\n", $4); };

/* 
	""|Param | (Param,)* 
*/
Params:	Param tVIRGULE Params;
Params:	Param;

Param:	MiseEnPage tID MiseEnPage {printf("Param %s ",$2);
									pushSymbol(symbolTable, $2, type_tmp); };

/* (Carac MiseEnPage)* */
MiseEnPage:	Caractere_MiseEnPage MiseEnPage |;
Caractere_MiseEnPage:	 tTAB 
					| tSPACE 
					| tFIN_L;

Type:	tINT 
		| tFLOAT { $$ = $1; };
%%
	
int main(void) {
	symbolTable = new_SymbolTab();
	//init();
	
	yyparse();
	printSymbolTab(symbolTable);
}
