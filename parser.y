%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calculator.h"
#include "includes.h"

float sym[26];                    /* symbol table */
extern FILE* yyin;
int counter = 0;
%}

%union {
    int iValue; 
    float fValue;           
    char sIndex;            
    node *nPtr;             
};

%token <iValue> INTEGER
%token <fValue> FLOAT 
%token <sIndex> VARIABLE
%token WHILE IF PUTS TYPEOF
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list

%%

program:
        function                { exit(0); }
        ;

function:
          function stmt         { ex($2, &counter); freeNode($2); }
        | /* Epsilon production */
        ;

stmt:
          ';'                            { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'                       { $$ = $1; }
        | PUTS expr ';'                 { $$ = opr(PUTS, 1, $2); }
	| TYPEOF expr ';'		{ $$ = opr(TYPEOF, 1, $2); }
        | VARIABLE '=' expr ';'          { $$ = opr('=', 2, id($1), $3); }
        | WHILE '(' expr ')' stmt        { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
        | '{' stmt_list '}'              { $$ = $2; }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

expr:
          INTEGER { $$ = conInteger($1); }
		| FLOAT  { $$ = conFloat($1); }
        | VARIABLE              { $$ = id($1); }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
        | '(' expr ')'          { $$ = $2; }
        ;

%%

node *conFloat(float value) {
    node *p;

    /* allocate node */
    if ((p = malloc(sizeof(node))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->con.value = value;
    p->con.type = FLOAT_TYPE;
    return p;
}


node *conInteger(int value){
	node* p;
	
	if((p = malloc(sizeof(node))) == NULL) 
		yyerror("Out of memory");

	p->type = typeCon;
	p->con.value = value;
	p->con.type = INTEGER_TYPE;
	return p;

}


node *id(int i) {
    node *p;

    /* allocate node */
    if ((p = malloc(sizeof(node))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.i = i;

    return p;
}

node *opr(int oper, int nops, ...) {
    va_list ap;
    node *p;
    int i;

    /* allocate node, extending op array */
    if ((p = malloc(sizeof(node) + (nops-1) * sizeof(node *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, node*);
    va_end(ap);
    return p;
}

void freeNode(node *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char** argv) {
	yyin = fopen(argv[1], "r");
    yyparse();
	fclose(yyin);
    return 0;
}
