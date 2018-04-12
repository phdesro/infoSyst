%{
	#include "compiler.tab.h"
%}
%%
main 		{	return  tFCT_MAIN;	}
const 		{	return  tCONST;	}

%{
/* types */
%}
int			{ 	yylval.lxType = s_int;		return tINT; 	}
float		{	yylval.lxType = s_float;	return tFLOAT;	}
char		{	yylval.lxType = s_char;		return tCHAR; 	}
void		{	yylval.lxType = s_void;		return tVOID; 	}

%{
/* conditions */
%}
"=="		{	return tEQU;		}
">"			{	return tSUP; 		}
">="		{	return tSUPEQU; 	}
"<"			{	return tINF;		}
"<="		{	return tINFEQU;		}
"!="		{	return tDIF;		}

%{
/* conditional loops */
%}
if			{	return 	tIF;	}
else		{	return  tELSE;	}
while		{	return 	tWHILE;	}

"\""		{	return	tQUOTEDOUBLE;	}
"'"			{	return	tQUOTESIMPLE;	}
"{" 		{	return  tAO;	}
"}" 		{	return  tAF;	}

%{
/* mise en page */
%}
\n 			{	return  tFIN_L;	}
\t			{	return  tTAB;	}
" "   		{	return  tSPACE;		}
"," 		{	return  tVIRGULE;	}
";" 		{	return  tFIN_I;		}

"(" 		{	return  tPO;	}
")" 		{	return  tPF;	}

%{
/* operations */
%}
"+" 		{	return  tOPADD;		}
"-" 		{	return  tOPSUB;		}
"*" 		{	return  tOPMUL;		}
"/" 		{	return  tOPDIV;		}
"=" 		{	return  tOPEQU;		}

%{
/* basic functions */
%}
"printf" 	{	return  tFCT_PRINTF;	}

%{
/* comments */
%}
\/\/.+\n			{	return 	tCOMMENT_S;		}
\/\*(.|\n)*\*\/	{	return	tCOMMENT_C;		}

[A-Za-z][A-Za-z0-9]* 	{	
							strcpy(yylval.str, yytext);
							return  tID;	
						}

[0-9][0-9]*	{
				yylval.nb = atoi(yytext);
				return  tNB;
			}
