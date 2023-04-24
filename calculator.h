// Supported AST node types
// typeCon -> type for Constants (number literals)
// typeId  -> type for Identifiers 
// typeOpr -> type for Operations
typedef enum { typeCon, typeId, typeOpr } nodeEnum;


// Number types
// Internally, everything is a float for now
typedef enum { INTEGER_TYPE, FLOAT_TYPE } langType;

// AST node of type constant.
typedef struct {
    float value;
    langType type;
} conNode;

// AST node of type identifier, storage for index
// in sym array.
typedef struct {
    int i;                      
} idNode;

// AST node of type operator
// oper -> operation type
// nops -> number of operators
// op -> operands pointer array
typedef struct {
    int oper;                   
    int nops;                   
    struct nodeTag *op[1];	
} oprNode;

// AST node generalization
typedef struct nodeTag {
    nodeEnum type;             

    union {
        conNode con;       
        idNode id;         
        oprNode opr;        
    };
} node;

// globally synced symbols table
extern float sym[26];
