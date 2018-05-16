%{
	#include "compiler.tab.h"
    #include "util/util_string.h"

    String * str;
%}

%x comment
%x string

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
/* Chaine de caracteres */
%}
"\""			{
                    str = new_String();
	                BEGIN(string);
	            }
<string>[^\n\"]	{   us_append(str, yytext[0]);  }
<string>"\\".   {   us_append(str, yytext[1]);  }
<string>"\n" 	{   printf("Multiline not allowed strings\n"); }
<string>"\""	{
                    BEGIN(INITIAL);
                    yylval.str = us_content(str);
                    return tSTRING;
                }

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
"=="		{	yylval.lxOp = op_equ; 	return tEQU;		}
">"			{	yylval.lxOp = op_sup; 	return tSUP; 		}
">="		{	yylval.lxOp = op_supe; 	return tSUPEQU; 	}
"<"			{	yylval.lxOp = op_inf; 	return tINF;		}
"<="		{	yylval.lxOp = op_infe; 	return tINFEQU;		}
"!="		{	yylval.lxOp = op_dif; 	return tDIF;		}

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
