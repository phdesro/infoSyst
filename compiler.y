%code requires {
	#include <stdio.h>
	#include "symtab/symboltab.h"
}

%union { 
	char str[80]; 
	int nb; 
	TypeSymbol lxType;
}

%left tEQU tDIF
%left tSUPEQU tSUP tINF tINFEQU

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
%token tAO tAF tVIRGULE tPO tPF tFIN_I tQUOTEDOUBLE tQUOTESIMPLE
%token tOPADD tOPSUB tOPDIV tOPMUL tOPEQU
%token tEQU tSUP tSUPEQU tINF tINFEQU tDIF
%token tIF tELSE tWHILE 

%type <str> tID tCOND tEQU tSUP tSUPEQU tINF tINFEQU tDIF
%type <nb> tNB
%type <lxType> Type tINT tFLOAT tCHAR tVOID

%%

//	starting point
S: Main ;
	

//	{ (Body_line)* }
Function_body: tAO Body_line tAF;

Body_line:	Instruction Body_line
			| Instruction;

Instruction: Call_function 
			| Declaration 
			| Affectation
			| If
			| While;

Main: 		tFCT_MAIN tPO Params { printf("\n");} tPF Function_body { printf("main_fin\n");}
			| tFCT_MAIN tPO tPF Function_body { printf("main_fin\n");};

/*-------------- Syntaxes conditionnelles --------------*/

If:			tIF Condition_stmt Instruction Else { printf("if_fin\n");}
			| tIF Condition_stmt tAO Body_line tAF Else { printf("if_fin\n");};
											

Else:		tELSE Instruction 		{ printf("else_fin\n");}
			| tELSE tAO Body_line tAF	{ printf("else_fin\n");}
			| ;

While:		tWHILE Condition_stmt Instruction { printf("while_fin\n");}
			| tWHILE Condition_stmt tAO Body_line tAF { printf("while_fin\n");}
			| tWHILE Condition_stmt tFIN_I { printf("[warning] empty while\n");};
											

Condition_stmt: tPO Condition tPF;

Condition:	Condition tCOND Condition 	{ 
											printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
											printf("LOAD 1 %d \n", ts_pop(symbolTable)); 
											printf("%s 0 0 1\n", $2); 
										}
			| Expression ;

tCOND: 		tEQU { strcpy($$,$1); }
			| tSUP
			| tSUPEQU
			| tINF
			| tINFEQU
			| tDIF;

/*-------------- Instructions --------------*/

// { type_tmp = $1 } permet de mémoriser le type temporairement en variable global avant de descendre plus bas
Declaration: Type { type_tmp = $1; } Params tFIN_I {  };

Affectation: tID tOPEQU Expression tFIN_I	{	
												int existing_adr = ts_getAdr(symbolTable, $1);
												if(existing_adr < 0) { 
													printf("\n\n[error] %s undeclared\n\n", $1); 
												}
												else {
													printf("LOAD 0 %d\n", ts_pop(symbolTable));
													printf("STORE %d 0\n", existing_adr);
												}
											};

Expression:	tID								{	
												ts_push(symbolTable, "tmp", s_int);
												int existing_adr = ts_getAdr(symbolTable, $1);
												if(existing_adr < 0) { 
													printf("\n\n[error] %s undeclared\n\n", $1);
												} else {
													printf("LOAD 0 %d \n", existing_adr);
													printf("STORE %d 0 \n", ts_peek(symbolTable)); 
												}
											}
			| tNB							{ 
												ts_push(symbolTable, "tmp", s_int); 
												printf("AFC 0 %d\n",$1); 
												printf("STORE %d 0\n", ts_peek(symbolTable)); 
											}
			| Expression tOPMUL Expression 	{ 	
												printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
												printf("LOAD 1 %d \n", ts_peek(symbolTable)); 
												printf("MUL 0 1 0 \n");
												printf("STORE %d 0 \n", ts_peek(symbolTable));
											}
			| Expression tOPDIV Expression	{ 	
												printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
												printf("LOAD 1 %d \n", ts_peek(symbolTable)); 
												printf("DIV 0 1 0 \n");
												printf("STORE %d 0 \n", ts_peek(symbolTable));
											}
			| Expression tOPADD Expression	{ 	
												printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
												printf("LOAD 1 %d \n", ts_peek(symbolTable)); 
												printf("ADD 0 1 0 \n");
												printf("STORE %d 0 \n", ts_peek(symbolTable));
											}
			| Expression tOPSUB Expression	{ 	
												printf("LOAD 0 %d \n", ts_pop(symbolTable)); 
												printf("LOAD 1 %d \n", ts_peek(symbolTable)); 
												printf("SUB 0 1 0 \n");
												printf("STORE %d 0 \n", ts_peek(symbolTable));
											}
			| tPO Expression tPF ;

/*-------------- Functions specifiques --------------*/
Call_function:
	Printf tFIN_I; 

Printf:		tFCT_PRINTF tPO tID tPF 							{ printf("printf -> %s\n", $3);	}
			| tFCT_PRINTF tPO tQUOTEDOUBLE tID tQUOTEDOUBLE tPF { printf("printf -> %s\n", $4); };

Params:		Param tVIRGULE Params
			| Param;

Param: tID 	{
				printf("Param %s ",$1);
				ErrorSymbolTab err = ts_push(symbolTable, $1, type_tmp); 

				// handlle error after pushed
				switch(err)	{
					case st_success: break; 
					case st_full: printf(">> symtab full << "); break;
					case st_existed: printf(">> existed symbol << "); break;
					default: printf(">> cas not handled <<");
				}
			};

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
