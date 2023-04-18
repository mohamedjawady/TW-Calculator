#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include "y.tab.h"

void yyerror(char *s);

float ex(node *p)
{
    if (!p)
        return 0;
    switch (p->type)
    {
    case typeCon:
        return p->con.value;
    case typeId:
        return sym[p->id.i];
    case typeOpr:
        switch (p->opr.oper)
        {
        case WHILE:
            while (ex(p->opr.op[0]))
                ex(p->opr.op[1]);
            return 0;
        case IF:
            if (ex(p->opr.op[0]))
                ex(p->opr.op[1]);
            else if (p->opr.nops > 2)
                ex(p->opr.op[2]);
            return 0;
        case PUTS:
            if(ex(p->opr.op[0]) == (int)ex(p->opr.op[0])){
                printf("%d\n", (int)ex(p->opr.op[0]));
            }else{
                printf("%f\n", ex(p->opr.op[0]));
            }
            return 0;
        case ';':
            ex(p->opr.op[0]);
            return ex(p->opr.op[1]);
        case '=':
            return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
        case UMINUS:
            return -ex(p->opr.op[0]);
        case '+':
            return ex(p->opr.op[0]) + ex(p->opr.op[1]);
        case '-':
            return ex(p->opr.op[0]) - ex(p->opr.op[1]);
        case '*':
            return ex(p->opr.op[0]) * ex(p->opr.op[1]);
        case '/':
            if (ex(p->opr.op[1]))
            {
                return ex(p->opr.op[0]) / ex(p->opr.op[1]);
            }
            else
            {
                yyerror("Division By Zero");
                exit(-1);
            };
        case '<':
            return ex(p->opr.op[0]) < ex(p->opr.op[1]);
        case '>':
            return ex(p->opr.op[0]) > ex(p->opr.op[1]);
        case GE:
            return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
        case LE:
            return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
        case NE:
            return ex(p->opr.op[0]) != ex(p->opr.op[1]);
        case EQ:
            return ex(p->opr.op[0]) == ex(p->opr.op[1]);
        }
    }
    return 0;
}
