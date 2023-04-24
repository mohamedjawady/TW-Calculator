
# Tree-Walk Calculator


The project aims to develop an interpreter for mathematical expressions using Flex/Bison tools. The interpreter is expected to calculate the value of an expression formed by real numbers and the usual operators (+, -, *, and /).

## Installation

Building the calculator executable
`
    bash build
`

Files cleanup
`
    bash clean
`
## Examples
Statements are comma separated, with current support for flow control statements, assignment and evaluation of expressions.  
Identifiers are single alphabetic characters, to simplify the symbols' table form, not resorting to Hashmaps (more in the notes section). 
#### Assignment statement

```
  identifier = expression;
```
Values can be either integers, or floating point numbers.
An example would be:
```
  a = 2;
  b = 2/3;
```

#### Expressions

Operations evaluating to a literal are considered as expressions. This can be the result of a number literal (Integer/Floating point number), or the result of applying an operation (**+** /**-** / **\*** / **/**) + Logical Operators.


```
  a = 2;
  b = 2/3;
  c = a + 2;
```

#### Side Effect statements
Expressions can be printed to the console using puts, or with the corresponding type, using typeof.
```
  puts 2;
  typeof 2/3;
  a = 5.2;
  puts a;
```

#### Flow Control

#### 1. Conditionals
Conditional execution of statements. (*non-zero values are evalued as truthful*)
```
  a = 2;
  b = 5.5;
  if(2>1){
      puts a;
  }else{
      puts b;
  };
```
Note that the else block is optional.

#### 2. Loops
Repeating execution of statements.
```
  a = 5;
  while(a>0){
      puts a;
      a = a - 1;
  };
```
## Requirements

- ✔ The lexical analyzer specification (Flex file) needs to be provided.  
- ✔ The Bison specification file defining the syntax analyzer needs to be developed.
- ✔ The syntax analyzer needs to be enriched by adding semantic actions to evaluate an input expression.



- ✔ The interpreter needs to be enriched by specifying the necessary specifications at the lexical (Flex file) and syntax (Bison file) levels.
- The project needs to ensure certain control functions (semantic aspects), including:
    - ✔ Evaluation of expressions
    - ✔ Detection of the error "missing end if" (not compatible with chosen syntax)
    - ✔ Detection of infinite loops (do not exceed 200 iterations).

**An input example would be**  
`If x=y Then z:=12+24 End if If x=y Then z:=3 Else x:=2 End if`
## Implementation
For the execution of this project, different candidate solutions were taken into account;
- **Tree-walking Interpreter**: A Tree-walking Interpreter is a type of interpreter that processes an abstract syntax tree (AST) and traverses the tree node-by-node to interpret and execute the program. In this interpreter, the source code is parsed into an AST using a parser like Lex and Yacc. The interpreter then walks through the AST, evaluating each node and executing the corresponding code. This approach is commonly used in scripting languages such as Python and Ruby.
- **JIT (Just-In-Time Compilation) compiler**: A JIT compiler is a type of compiler that compiles code at runtime, as it is needed. It takes the source code and compiles it into machine code, which can be executed directly by the CPU. The compiled code is then cached for future use, improving performance. JIT compilers are commonly used in dynamic languages such as Java, JavaScript, and Python to improve performance by eliminating the need for interpretation.
- **Compilation targerting a VM**: Compilation targeting a virtual machine (VM) involves compiling source code into bytecode that is designed to run on a virtual machine. The bytecode is then interpreted by the VM, which translates it into machine code that can be executed by the CPU. This approach is commonly used in languages like Java and C# to achieve platform independence. The simplest and most suitable approach for this type of problem at this scale was deemed to be a tree-walking interpreter using Lex and Yacc. In this approach, the source code is parsed into an AST, and the interpreter walks through the AST to interpret and execute the program. This approach is straightforward to implement and can be used for small-scale projects.
The simplest, and most suitable for this type of problem at this scale was deemed to be a tree-walking interpreter, using Lex and Yacc.

### Implementation Approach - Tree Walking Interpreter
In this approach, the input code is first parsed to a lexer, then to a parser in order to create an abstract syntax tree (AST) that represents the structure of the program.  
The interpreter (*calculator.c*) then traverses the AST and evaluates each node, following a specific order of traversal.

For the first part of the project, implementing an interpreter for mathematical expressions, the tree-walk interpreter would traverse the AST and evaluate each node as follows:

- When the interpreter encounters a leaf node, it returns the value of the leaf (in this case, the value of a number).
- When the interpreter encounters an operator node (such as "+", "-", "*", or "/"), it evaluates child nodes of the operator node and applies the corresponding operation to the values obtained.  
- The interpreter continues this process recursively until it reaches the root node of the AST, which represents the final value of the expression.  
Note that this tree-walk interpreter is extended to handle additional structures and statements(*print/typeof*) such as conditional (*if/else*) and iterative structures (while). It evaluates each node of the AST using specific semantic rules to perform the corresponding operation. For example, when the interpreter encounters a conditional statement, it would evaluate the condition and either execute the "then" statement or the "else" statement depending on the result of the condition.

One advantage of implementing a tree-walk interpreter is that it allows for a straightforward and efficient evaluation of the AST, making it a popular choice for interpreting programming languages.  
Additionally, the interpreter can be easily extended to support additional language features by adding the necessary semantic actions for each node of the AST.


## Notes


**Symbols' Table**

- The symbols' table for this project is chosen to be an array holding information for 26 possible identifiers. A different, more complex and yet practical would be using a Hashmap.  
- In a hashmap symbol table, the symbol names are used as keys, and the symbol attributes, such as data type, scope, and memory location, are stored as values in a hash table. 
This allows for fast and efficient lookup of symbol information during compilation or interpretation.

**Detection of infinite loops**
- In order to detect, and prevent infinite loops, we followed a counter strategy; 
`C
#define MAX_ITERATIONS 200
` in combination with 
`C
float ex(node *p, int* counter)
` to keep track of an iterations' counter at runtime.  
If the number of iterations present at `counter` exceeds the set MAX_ITERATIONS, the program errors out.  
## Authors

- [@mohamedjawady](https://www.github.com/mohamedjawady)
- [Islem Bennour]()
- [Lassad Jarray]()


