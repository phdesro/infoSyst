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

/* 
	(MiseEnPage)* Main (MiseEnPage)*
*/
S:	MiseEnPage Main MiseEnPage;
	
/*
	{ (Body_line)* }
*/
Function_body: MiseEnPage tAO Body_line tAF;

Body_line:	MiseEnPage Body_line
			| Instruction Body_line
			| MiseEnPage;

Instruction: Call_function 
			| Declaration 
			| Affectation
			| If;

Main: 		tFCT_MAIN tPO Params { printf("\n");} tPF Function_body { printf("main_fin\n");}
			| tFCT_MAIN tPO MiseEnPage tPF Function_body { printf("main_fin\n");};

/*-------------- Syntaxes conditionnelles --------------*/

If:	tIF tPO Condition tPF MiseEnPage Instruction { printf("if_fin\n");};

Condition:	Condition tCOND Condition
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
Declaration: Type { type_tmp = $1; } MiseEnPage Params tFIN_I {	printf("Declaration_fin\n");	};

Affectation: tID MiseEnPage tOPEQU MiseEnPage Expression MiseEnPage tFIN_I;

Expression:	Expression tOp Expression
			| tPO Expression tPF
			| tID
			| tNB;

tOp: 		tOPADD 
			| tOPSUB 
			| tOPDIV 
			| tOPMUL ;

/* 
	[les fonctions] ;
*/
Call_function:
	Printf tFIN_I; 

Printf:		tFCT_PRINTF tPO tID tPF 							{ printf("printf -> %s\n", $3);	}
			| tFCT_PRINTF tPO tQUOTEDOUBLE tID tQUOTEDOUBLE tPF { printf("printf -> %s\n", $4); };


/* 
	""|Param | (Param,)* 
*/
Params:		Param tVIRGULE Params
			| Param;

Param:	MiseEnPage tID MiseEnPage	{
										printf("Param %s ",$2);
										ErrorSymbolTab err = pushSymbol(symbolTable, $2, type_tmp); 
										switch(err)	{
											case st_success: break; 
											case st_full: printf(">> symtab full << "); break;
											case st_existed: printf(">> existed symbol << "); break;
											default: printf(">> cas not handled <<");
										}
									};

/* (Carac MiseEnPage)* */
MiseEnPage:	Caractere_MiseEnPage MiseEnPage |;
Caractere_MiseEnPage: tTAB 
			| tSPACE 
			| tFIN_L;

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
