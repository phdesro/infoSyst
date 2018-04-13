%{
	#include "compiler.tab.h"
%}

%x comment

%%

"/*"         BEGIN(comment);
<comment>[^*\n]*        
<comment>"*"+[^*/\n]*   
<comment>\n             
<comment>"*"+"/"        BEGIN(INITIAL);

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
"=="		{	strcpy(yylval.str, "EQU"); return tEQU;		}
">"			{	strcpy(yylval.str, "SUP"); return tSUP; 		}
">="		{	strcpy(yylval.str, "SUPE"); return tSUPEQU; 	}
"<"			{	strcpy(yylval.str, "INF"); return tINF;		}
"<="		{	strcpy(yylval.str, "INFE"); return tINFEQU;		}
"!="		{	strcpy(yylval.str, "DIF"); return tDIF;		}

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
[ \n\t]		{	}
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
\/\/.+\n	{	}	



[A-Za-z][A-Za-z0-9]* 	{	
							strcpy(yylval.str, yytext);
							return  tID;	
						}

[0-9][0-9]*	{
				yylval.nb = atoi(yytext);
				return  tNB;
			}
