%code requires {
	#include <stdio.h>
	#include <string.h>

	#include "memins/opcode.h"
	#include "util/util.h"

    /* --------------------- Modifiez le MODE en 1 pour afficher  -------------------------- */
    #define SYMBOL_TABLE 1
    #define INSTRUCTION_MEMORY 1
    /* ------------------------------------------------------------------------------------- */
}

%union {
	char* str;
	int nb; 
	TypeSymbol lxType;
	OpCode lxOp;
}



%left tOPADD tOPSUB
%left tOPMUL tOPDIV

%left tEQU tDIF
%left tSUPEQU tSUP tINF tINFEQU

%left tQUESTION tDOUBLEDOTS

%{
	int yylex(void);
	void yyerror(char*);

    // global variable
	TypeSymbol type_tmp;
	int depth;

    // structures
	SymbolTab * symbolTable;
	MemoireInstr * memInst;
%}

%token tID tNB tFCT_MAIN tFCT_PRINTF tFCT_ECHO
%token tCONST tINT tFLOAT tCHAR tVOID
%token tAO tAF tVIRGULE tPO tPF tFIN_I tQUOTEDOUBLE tQUOTESIMPLE
%token tOPAFC tOPADD tOPSUB tOPDIV tOPMUL
%token tEQU tSUP tSUPEQU tINF tINFEQU tDIF
%token tIF tELSE tWHILE
%token tQUESTION tDOUBLEDOTS
%token tSTRING

%type <str> tID tSTRING
%type <nb> tNB tWHILE
%type <lxType> Type tINT tFLOAT tCHAR tVOID
%type <lxOp> tEQU tSUP tSUPEQU tINF tINFEQU tDIF
%type <lxOp> tOPADD tOPSUB tOPDIV tOPMUL

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

Main: 		tINT tFCT_MAIN tPO Params { printf("\n");} tPF Function_body { printf("main_fin\n");}
			| tINT tFCT_MAIN tPO tPF Function_body { printf("main_fin\n");};

/*-------------- Syntaxes conditionnelles --------------*/

If:			tIF Condition_stmt  {
                                    mi_push(memInst, new_Instruction(op_load, 0, ts_pop(symbolTable)));
                                    mi_push(memInst, new_Instruction(op_jmpc, I_ADR_UNFILLED, 0)); // wait @ of Else
                                    depth ++;
                                } If_Block Else;

If_Block: 	Instruction
			| tAO Body_line tAF;
											

Else:		tELSE 	{
                        mi_push(memInst, new_Instruction(op_jmp, I_ADR_UNFILLED, 0));
						mi_fill_jump(memInst, 1);
					} Else_Block {
								 	mi_fill_jump(memInst, 0);
								 	mi_push(memInst, new_Instruction(op_nop));
								 	ts_clean_depth(symbolTable, depth);
								 	depth --;
								 }

			| %prec tIFX	{
							 	mi_fill_jump(memInst, 0);
							 	mi_push(memInst, new_Instruction(op_nop));
							 	ts_clean_depth(symbolTable, depth);
							 	depth --;

							};

Else_Block:	Instruction
			| tAO Body_line tAF;

While: tWHILE   {
                    $1 = memInst->last_address + I_PADDING; // address of first instruction in condition
                } Condition_stmt    {
                                    mi_push(memInst, new_Instruction(op_load, 0, ts_pop(symbolTable)));
                                    mi_push(memInst, new_Instruction(op_jmpc, I_ADR_UNFILLED, 0));
                                    depth ++;

                                }   While_Block {
                                                    mi_push(memInst, new_Instruction(op_jmp, $1, 0));
                                                    mi_fill_jump(memInst, 0);
                                                    mi_push(memInst, new_Instruction(op_nop));
                                                    ts_clean_depth(symbolTable, depth);
                                                    depth--;
                                                };

While_Block: Instruction
            | tAO Body_line tAF
            | tFIN_I;

Condition_stmt: tPO Expression tPF;


/*-------------- Instructions --------------*/

// { type_tmp = $1 } permet de mémoriser le type temporairement en variable global avant de descendre plus bas
Declaration: Type { type_tmp = $1; } Variables tFIN_I;

Variables : Variable tVIRGULE Variables
            | Variable;

Variable : tID {
                    ts_push(symbolTable, $1, type_tmp, depth);
                    mi_push(memInst, new_Instruction(op_afc, 0, 0));
                    mi_push(memInst, new_Instruction(op_store, ts_peek(symbolTable), 0));
               }
            | tID {
                    ts_push(symbolTable, $1, type_tmp, depth);
                } tOPAFC Expression {
                                        mi_push(memInst, new_Instruction(op_load, 0, ts_pop(symbolTable)));
                                        mi_push(memInst, new_Instruction(op_store, ts_getAdr(symbolTable, $1), 0));
                                    };

Affectation: tID tOPAFC Expression tFIN_I {
												int existing_adr = ts_getAdr(symbolTable, $1);
												if(existing_adr < 0) { 
													printf("\n[error] %s undeclared\n", $1);
												}   else {
													mi_push(memInst, new_Instruction(op_load, 0, ts_pop(symbolTable)));
													mi_push(memInst, new_Instruction(op_store, existing_adr, 0));

												}
											};

Expression:	tID								{
												int existing_adr = ts_getAdr(symbolTable, $1);
												if(existing_adr < 0) { 
													printf("\n[error] %s undeclared\n", $1);
												} else {
												    ts_push(symbolTable, "tmp", s_int, depth);
													mi_push(memInst, new_Instruction(op_load, 0, existing_adr));
													mi_push(memInst, new_Instruction(op_store, ts_peek(symbolTable), 0));
												}
											}
			| tNB							{ 
												ts_push(symbolTable, "tmp", s_int, depth);
												mi_push(memInst, new_Instruction(op_afc, 0, $1));
												mi_push(memInst, new_Instruction(op_store, ts_peek(symbolTable), 0));
											}
			| Expression tOPADD Expression 	{   util_op(symbolTable, memInst, $2);  }
			| Expression tOPSUB Expression 	{   util_op(symbolTable, memInst, $2);  }
			| Expression tOPDIV Expression 	{   util_op(symbolTable, memInst, $2);  }
			| Expression tOPMUL Expression 	{   util_op(symbolTable, memInst, $2);  }
			| tOPSUB Expression 	{
			                             mi_push(memInst, new_Instruction(op_afc, 0, 0));
			                             ts_push(symbolTable, "tmp", s_int, depth);
			                             mi_push(memInst, new_Instruction(op_load, 1, ts_peek(symbolTable)));
			                             mi_push(memInst, new_Instruction(op_sub, 0, 0, 1));
			                             mi_push(memInst, new_Instruction(op_store, ts_peek(symbolTable), 0));
			                        }
			| Expression tEQU       Expression 	    {   util_op(symbolTable, memInst, $2); }
            | Expression tSUP       Expression 	    {   util_op(symbolTable, memInst, $2); }
            | Expression tSUPEQU    Expression 	    {   util_op(symbolTable, memInst, $2); }
            | Expression tINF       Expression 	    {   util_op(symbolTable, memInst, $2); }
            | Expression tINFEQU    Expression 	    {   util_op(symbolTable, memInst, $2); }
            | Expression tDIF       Expression 	    {   util_op(symbolTable, memInst, $2); }

			| tPO Expression tPF
			| Expression tQUESTION Expression tDOUBLEDOTS Expression { printf("ternary\n"); }; //TODO check if we collect correctly information

/*-------------- Functions specifiques --------------*/
Call_function:  Printf tFIN_I
            | Echo tFIN_I;

Printf:		tFCT_PRINTF tPO tID tPF 							{   printf("printf -> %s\n", $3);	}
            | tFCT_PRINTF tPO tSTRING tPF                       {   printf("printf -> %s\n", $3);    }
			| tFCT_PRINTF tPO tQUOTEDOUBLE tID tQUOTEDOUBLE tPF {   printf("printf -> %s\n", $4); };

Echo:       tFCT_ECHO tPO tID tPF
                {
                    int existing_adr = ts_getAdr(symbolTable, $3);
                    if(existing_adr < 0) {
                        printf("\n[error] %s undeclared\n", $3);
                    }
                    else {
                        mi_push(memInst, new_Instruction(op_load, 0, existing_adr));
                        mi_push(memInst, new_Instruction(op_echo, 0));
                    }
                };

Params:		Param tVIRGULE Params
			| Param;

Param: tID 	{
				ts_push(symbolTable, $1, type_tmp, depth);
			};

// Gestion de typage
Type:		tINT 
			| tVOID
			| tCHAR
			| tFLOAT { $$ = $1; };
%%

void init() {
    // init global vars
    depth = 0;

    // init structs
	symbolTable = new_SymbolTab();
	memInst = new_MemoireInstr();
}

int main(void) {
	init();
	yyparse();

    if(SYMBOL_TABLE)            ts_print(symbolTable);
	if(INSTRUCTION_MEMORY)	    mi_print(memInst);

	mi_write(memInst, "test.asm");
	util_copy_file("test.asm", "interpreter/test.asm");
}
