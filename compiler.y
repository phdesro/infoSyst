%union { char str[80]; int nb; }

%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(char*);
%}

%token tID tFCT_MAIN tFCT_PRINTF
%token tCONSTANTE tENTIER
%token tFIN_L tTAB tSPACE
%token tAO tAF tVIRGULE tPO tPF tFIN_I tQUOTEDOUBLE tQUOTESIMPLE
%token tOPADD tOPSUB tOPDIV tOPMUL tOPEQU

%type <str> tID

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
Body_line:	Call_function Body_line;
Body_line:	;

Main: tFCT_MAIN tPO Params tPF Function_body { printf("main reconnu\n");};
Main: tFCT_MAIN tPO MiseEnPage tPF Function_body { printf("main reconnu\n");};

/* 
	[les fonctions] ;
*/
Call_function:
	Printf tFIN_I;

Printf:
	tFCT_PRINTF tPO tQUOTEDOUBLE tID tQUOTEDOUBLE tPF  
			{ printf("printf -> %s\n", $4); };

/* 
	""|Param | (Param,)* 
*/
Params:	Param tVIRGULE Params;
Params:	Param;

Param:	MiseEnPage tID MiseEnPage;

/* (Carac MiseEnPage)* */
MiseEnPage:	Caractere_MiseEnPage MiseEnPage |;
Caractere_MiseEnPage:	tFIN_L | tTAB | tSPACE;

%%

int main(void) {
	yyparse();
}
