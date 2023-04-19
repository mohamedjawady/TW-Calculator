%{
#include <stdlib.h>
#include "calculator.h"
#include "y.tab.h"
void yyerror(char *);
%}
integer ([1-9])([0-9])*
float ([0-9])+[.]([0-9])+
%%


[a-z]       { 
                yylval.sIndex = *yytext - 'a';
                return VARIABLE;
            }

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

{float} {
    // printf("Float %f\n", atof(yytext));
		yylval.fValue = atof(yytext);
                return FLOAT;
}
{integer} {
    // printf("Integer %s\n", yytext);
                yylval.iValue = atof(yytext);
                return INTEGER;
            }

[-()<>=+*/;{}] {
                return *yytext;
             }

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"puts"          return PUTS;
"typeof"	return TYPEOF;
[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");
%%
int yywrap(void) {
    return 1;
}
