#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include "y.tab.h"
#define MAX_ITERATIONS 200
void yyerror(char *s);

char* typeMappings[] = {"INTEGER", "FLOAT"};


float ex(node *p, int* counter)
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
            while (ex(p->opr.op[0], counter)){
                // printf("Counter: %d", *counter);
				if (*counter > MAX_ITERATIONS) {
			        printf("Infinite loop detected!\n");
					exit(-1);
				};
				ex(p->opr.op[1], counter);
				(*counter)++;
	    };
            return 0;
        case IF:
            if (ex(p->opr.op[0], counter))
                ex(p->opr.op[1], counter);
            else if (p->opr.nops > 2)
                ex(p->opr.op[2], counter);
            return 0;
        case PUTS:
            if(ex(p->opr.op[0], counter) == (int)ex(p->opr.op[0], counter)){
                printf("%d\n", (int)ex(p->opr.op[0], counter));
            }else{
                printf("%f\n", ex(p->opr.op[0], counter));
            }
            return 0;
	case TYPEOF:
	    // TODO: remove conditional? redundant in PUTS and TYPEOF?
	    // TODO: handle proper typing of number literals 
            if(ex(p->opr.op[0], counter) == (int)ex(p->opr.op[0], counter)){
                 printf("%d (%s)\n", (int)ex(p->opr.op[0], counter), typeMappings[INTEGER_TYPE]);
            }else{
                 printf("%f (%s)\n", ex(p->opr.op[0], counter), typeMappings[FLOAT_TYPE]);
             }
	    return 0;
        case ';':
            ex(p->opr.op[0], counter);
            return ex(p->opr.op[1], counter);
        case '=':
            return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1], counter);
        case UMINUS:
            return -ex(p->opr.op[0], counter);
        case '+':
            return ex(p->opr.op[0], counter) + ex(p->opr.op[1], counter);
        case '-':
            return ex(p->opr.op[0], counter) - ex(p->opr.op[1], counter);
        case '*':
            return ex(p->opr.op[0], counter) * ex(p->opr.op[1], counter);
        case '/':
            if (ex(p->opr.op[1], counter))
            {
                return ex(p->opr.op[0], counter) / ex(p->opr.op[1], counter);
            }
            else
            {
                yyerror("Division By Zero");
                exit(-1);
            };
        case '<':
            return ex(p->opr.op[0], counter) < ex(p->opr.op[1], counter);
        case '>':
            return ex(p->opr.op[0], counter) > ex(p->opr.op[1], counter);
        case GE:
            return ex(p->opr.op[0], counter) >= ex(p->opr.op[1], counter);
        case LE:
            return ex(p->opr.op[0], counter) <= ex(p->opr.op[1], counter);
        case NE:
            return ex(p->opr.op[0], counter) != ex(p->opr.op[1], counter);
        case EQ:
            return ex(p->opr.op[0], counter) == ex(p->opr.op[1], counter);
        }
    }
    return 0;
}
