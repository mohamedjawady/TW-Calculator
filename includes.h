#ifndef INCLUDES_H
#define INCLUDES_H


// AST node constructor for operation	
node *opr(int oper, int nops, ...);

// AST node constructor for identifier
node *id(int i);

// AST node constructor for float literals
node *conFloat(float value);

// AST node constructor for Integer literals
node *conInteger(int value);

// AST node destructor: generalized
void freeNode(node *p);

// AST executor: Tree-walking interpreter 
int ex(node *p, int* counter);

// flex lexer routine
int yylex(void);

// flex error routine
void yyerror(char *s);

#endif
