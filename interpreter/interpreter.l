%{
	#include "interpreter.tab.h"
%}

%x comment

%%

%{
/* multi line comment */
%}
"/*"         			{	BEGIN(comment);	}
<comment>[^*\n]*        
<comment>"*"+[^*/\n]*   
<comment>\n             
<comment>"*"+"/"        {	BEGIN(INITIAL);	}

%{
/* simple line comment */
%}
#.+\n	{	}

%{
/* operations */
%}
"ADD" 		{	yylval.lxOp = op_add; 	    return tOP;		}
"SUB" 		{	yylval.lxOp = op_sub; 	    return tOP;		}
"MUL" 		{	yylval.lxOp = op_mul; 	    return tOP;		}
"DIV" 		{	yylval.lxOp = op_div; 	    return tOP;		}
"EQU" 		{	yylval.lxOp = op_equ; 	    return tOP;		}
"INF" 		{	yylval.lxOp = op_inf; 	    return tOP;		}
"INFE" 		{	yylval.lxOp = op_infe; 	    return tOP;		}
"SUP" 		{	yylval.lxOp = op_sup; 	    return tOP;		}
"SUPE" 		{	yylval.lxOp = op_supe; 	    return tOP;		}
"DIF" 		{	yylval.lxOp = op_dif; 	    return tOP;		}
"COP" 		{	yylval.lxOp = op_cop; 	    return tOP;		}
"AFC" 		{	yylval.lxOp = op_afc; 	    return tOP;		}
"LOAD" 		{	yylval.lxOp = op_load; 	    return tOP;		}
"STORE" 	{	yylval.lxOp = op_store; 	return tOP;		}
"JMPC" 		{	yylval.lxOp = op_jmpc; 	    return tOP;		}
"JMP" 		{	yylval.lxOp = op_jmp; 	    return tOP;		}
"ECHO" 		{	yylval.lxOp = op_echo; 	    return tOP;		}
"NOP" 		{	yylval.lxOp = op_nop; 	    return tOP;		}

%{
/* skip layout characters */
%}
[ \n\t]		{}

%{
/* number */
%}
-?[0-9]+	{
				yylval.nb = atoi(yytext);
				return  tINT;
			}
