%code requires {
	#include <stdio.h>

	#include "memins/opcode.h"
	#include "util/util.h"
}

%union { 
	char str[80]; 
	int nb; 
	TypeSymbol lxType;
	OpCode lxOp;
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
	MemoireInstr * memInst;
%}

%token tID tNB tFCT_MAIN tFCT_PRINTF
%token tCONST tINT tFLOAT tCHAR tVOID
%token tAO tAF tVIRGULE tPO tPF tFIN_I tQUOTEDOUBLE tQUOTESIMPLE
%token tOPADD tOPSUB tOPDIV tOPMUL tOPEQU
%token tEQU tSUP tSUPEQU tINF tINFEQU tDIF
%token tIF tELSE tWHILE 

%type <str> tID
%type <nb> tNB
%type <lxType> Type tINT tFLOAT tCHAR tVOID
%type <lxOp> tEQU tSUP tSUPEQU tINF tINFEQU tDIF
%type <lxOp> tOPADD tOPSUB tOPDIV tOPMUL tOPEQU

%nonassoc tIFX
%nonassoc tELSE

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

If:			tIF Condition_stmt If_Block Else;

If_Block: 	Instruction
			| tAO Body_line tAF { 	
									mi_push(memInst, new_Instruction(op_jmpc, I_ADR_UNFILLED, 0)); 
								};
											

Else:		tELSE 	{
						mi_push(memInst, new_Instruction(op_jmpc, I_ADR_UNFILLED, 0)); 
						mi_fill_jump(memInst, memInst->last_address, 1);  
					} Else_Block {
								 	mi_fill_jump(memInst, memInst->last_address, 0);
								 }

			| %prec tIFX	{
							 	mi_fill_jump(memInst, memInst->last_address, 0);
							};

Else_Block:	Instruction
			| tAO Body_line tAF;

While:		tWHILE Condition_stmt Instruction           { printf("while_fin\n");}
			| tWHILE Condition_stmt tAO Body_line tAF   { printf("while_fin\n");}
			| tWHILE Condition_stmt tFIN_I              { printf("[warning] empty while\n");};
											

Condition_stmt: tPO Condition tPF { mi_push(memInst, new_Instruction(op_jmpc, I_ADR_UNFILLED, 0));/* wait @ of Else */ };

Condition:	Condition tEQU Condition 	    {   util_cond(symbolTable, memInst, $2); }
			| Condition tSUP Condition 	    {   util_cond(symbolTable, memInst, $2); }
			| Condition tSUPEQU Condition 	{   util_cond(symbolTable, memInst, $2); }
			| Condition tINF Condition 	    {   util_cond(symbolTable, memInst, $2); }
			| Condition tINFEQU Condition 	{   util_cond(symbolTable, memInst, $2); }
			| Condition tDIF Condition 	    {   util_cond(symbolTable, memInst, $2); }
			| Expression ;

/*-------------- Instructions --------------*/

// { type_tmp = $1 } permet de mémoriser le type temporairement en variable global avant de descendre plus bas
Declaration: Type { type_tmp = $1; } Params tFIN_I {  };

Affectation: tID tOPEQU Expression tFIN_I	{	
												int existing_adr = ts_getAdr(symbolTable, $1);
												if(existing_adr < 0) { 
													printf("\n\n[error] %s undeclared\n\n", $1); 
												}
												else {
													mi_push(memInst, new_Instruction(op_load, 0, ts_pop(symbolTable)));
													mi_push(memInst, new_Instruction(op_store, existing_adr, 0));
												}
											};

Expression:	tID								{	
												ts_push(symbolTable, "tmp", s_int);
												int existing_adr = ts_getAdr(symbolTable, $1);
												if(existing_adr < 0) { 
													printf("\n\n[error] %s undeclared\n\n", $1);
												} else {
													mi_push(memInst, new_Instruction(op_load, 0, ts_pop(symbolTable)));
													mi_push(memInst, new_Instruction(op_store, 0, ts_peek(symbolTable)));
												}
											}
			| tNB							{ 
												ts_push(symbolTable, "tmp", s_int); 
												mi_push(memInst, new_Instruction(op_afc, 0, $1));
												mi_push(memInst, new_Instruction(op_store, ts_peek(symbolTable), 0));
											}
			| Expression tOPADD Expression 	{   util_op(symbolTable, memInst, $2);  }
			| Expression tOPSUB Expression 	{   util_op(symbolTable, memInst, $2);  }
			| Expression tOPDIV Expression 	{   util_op(symbolTable, memInst, $2);  }
			| Expression tOPMUL Expression 	{   util_op(symbolTable, memInst, $2);  }
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

void init() {
	printf("init");
	symbolTable = new_SymbolTab();
	memInst = new_MemoireInstr();
}

int main(void) {
	
	init();
	
	yyparse();
	//ts_print(symbolTable);
	mi_print(memInst);
}
