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

If:			tIF _ Condition_stmt _ Instruction _ Else { printf("if_fin\n");}
			| tIF _ Condition_stmt _ tAO Body_line tAF _ Else { printf("if_fin\n");};

Else:		tELSE _ Instruction 		{ printf("else_fin\n");}
			| tELSE _ tAO Body_line tAF	{ printf("else_fin\n");}
			| ;

Condition_stmt: tPO _ Condition _ tPF;

Condition:	Condition _ tCOND _ Condition
			| Expression;

tCOND: 		tEQU
			| tSUP
			| tSUPEQU
			| tINF
			| tINFEQU
			| tDIF;

/*-------------- Instructions --------------*/

// { type_tmp = $1 } permet de mémoriser le type temporairement en variable global avant de descendre plus bas
Declaration: Type { type_tmp = $1; } _ Params tFIN_I {  };

Affectation: tID _ tOPEQU _ Expression _ tFIN_I { 
												
												};

Expression:	Expression _ tOPMUL _ Expression 	{ 	
													printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
													printf("LOAD 1 %d \n", ts_peek(symbolTable)); 
													printf("MUL 0 1 0 \n");
													printf("STORE %d 0 \n", ts_peek(symbolTable));
												}
			| Expression _ tOPDIV _ Expression	{ 	
													printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
													printf("LOAD 1 %d \n", ts_peek(symbolTable)); 
													printf("DIV 0 1 0 \n");
													printf("STORE %d 0 \n", ts_peek(symbolTable));
												}
			| Expression _ tOPADD _ Expression	{ 	
													printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
													printf("LOAD 1 %d \n", ts_peek(symbolTable)); 
													printf("ADD 0 1 0 \n");
													printf("STORE %d 0 \n", ts_peek(symbolTable));
												}
			| Expression _ tOPSUB _ Expression	{ 	
													printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
													printf("LOAD 1 %d \n", ts_peek(symbolTable)); 
													printf("SUB 0 1 0 \n");
													printf("STORE %d 0 \n", ts_peek(symbolTable));
												}
			| tPO _ Expression _ tPF
			| tID								{	
													ts_push(symbolTable, "tmp", s_int);
													int existed_adr = ts_getAdr(symbolTable, $1);
													if(existed_adr < 0) { printf("%s non declare\n", $1); exit(0); }
													printf("LOAD 0 %d \n", existed_adr);
													printf("STORE %d 0 \n", ts_peek(symbolTable)); 
												}
			| tNB								{ 
													ts_push(symbolTable, "tmp", s_int); 
													printf("AFC 0 %d\n",$1); 
													printf("STORE %d 0\n", ts_peek(symbolTable)); 
												};

/*
tOp: 		tOPMUL
			| tOPDIV
			| tOPADD
			| tOPSUB;
*/

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
					ErrorSymbolTab err = ts_push(symbolTable, $2, type_tmp); 

					// handlle error after pushed
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
	ts_print(symbolTable);
}
