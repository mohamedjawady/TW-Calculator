typedef enum { typeCon, typeId, typeOpr } nodeEnum;

typedef enum { INTEGER_TYPE, FLOAT_TYPE } langType;

typedef struct {
    float value;
    langType type;
} conNode;


typedef struct {
    int i;                      
} idNode;

typedef struct {
    int oper;                   
    int nops;                   
    struct nodeTag *op[1];	
} oprNode;

typedef struct nodeTag {
    nodeEnum type;             

    union {
        conNode con;       
        idNode id;         
        oprNode opr;        
    };
} node;

extern float sym[26];
