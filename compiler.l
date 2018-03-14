%{
	#include "compiler.tab.h"
%}
%%
main 		{	return  tFCT_MAIN;	}
const 		{	return  tCONST;	}
int 		{	return  tINT;	}
"\""		{	return	tQUOTEDOUBLE;	}
"'"			{	return	tQUOTESIMPLE;	}
"{" 		{	return  tAO;	}
"}" 		{	return  tAF;	}
\n 			{	return  tFIN_L;	}
\t			{	return  tTAB;	}
" "   		{	return  tSPACE;	}
"," 		{	return  tVIRGULE;	}
"(" 		{	return  tPO;	}
")" 		{	return  tPF;	}
";" 		{	return  tFIN_I;	}
"+" 		{	return  tOPADD;	}
"-" 		{	return  tOPSUB;	}
"*" 		{	return  tOPMUL;	}
"/" 		{	return  tOPDIV;	}
"=" 		{	return  tOPEQU;	}
"printf" 	{	return  tFCT_PRINTF;	}

[A-Za-z][A-Za-z0-9]* 	{	
							strcpy(yylval.str, yytext);
							return  tID;	
						}
