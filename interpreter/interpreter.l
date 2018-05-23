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
"ADD" 		{	yylval.lxOp = op_add; 	return tOPADD;		}
"SUB" 		{	yylval.lxOp = op_sub; 	return tOPSUB;		}

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
