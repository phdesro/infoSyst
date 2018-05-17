%{
	#include "interpreter.tab.h"

%}

%x comment

%%

%{
/* Commentaires complexes */
%}
"/*"         			{	BEGIN(comment);	}
<comment>[^*\n]*        
<comment>"*"+[^*/\n]*   
<comment>\n             
<comment>"*"+"/"        {	BEGIN(INITIAL);	}

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
"+" 		{	yylval.lxOp = op_add; 	return tOPADD;		}
"-" 		{	yylval.lxOp = op_sub; 	return tOPSUB;		}
"*" 		{	yylval.lxOp = op_equ; 	return tOPMUL;		}
"/" 		{	yylval.lxOp = op_equ; 	return tOPDIV;		}
"=" 		{	yylval.lxOp = op_equ; 	return tOPEQU;		}

%{
/* basic functions */
%}
"printf" 	{	return  tFCT_PRINTF;	}

%{
/* comments */
%}
\/\/.+\n	{	}	

"?"           {   return tQUESTION;   }
":"           {   return tDOUBLEDOTS; }

[A-Za-z][A-Za-z0-9]* 	{
                            yylval.str = malloc(sizeof(char) * strlen(yytext));
							strcpy(yylval.str, yytext);
							return  tID;	
						}

[0-9][0-9]*	{
				yylval.nb = atoi(yytext);
				return  tNB;
			}
