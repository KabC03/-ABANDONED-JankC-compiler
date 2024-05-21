/*
 * compiler_structs.h
 *
 * Description:
 * Defines data structures and enumerations for tokens, expressions, and high-level syntactic constructs used
 * throughout the compilation process. This header is integral for lexical analysis, parsing, and constructing 
 * the abstract syntax tree (AST).
 *
 * Key Components:
 * - TOKEN_TYPE: Enumerates all recognizable syntax elements including operators, data types, and control structures.
 * - Token: Represents syntactic elements with associated data, supporting both variables and immediate values.
 * - ExpressionTree: Represents hierarchical expressions ensuring correct evaluation order.
 * - High-level structures (DeclarationStatement, IfStatement, etc.): Define the constructs for an AST to facilitate
 *   code generation and optimization.
 */
#ifndef COMPILER_STRUCTS_H 
#define COMPILER_STRUCTS_H 
#include <stddef.h>
#include <stdbool.h>
extern const char* const validTokens[];


typedef enum OPERATOR_PRECEDENCE {
    //Lower values indicate lower presedence
    //Used in shunting yard algorithm

    FUNCTION_PRECEDENCE = 0,

    ADDITION_PRECEDENCE = 1,
    SUBTRACTION_PRECEDENCE = 1,

    MULTIPLICATION_PRECEDENCE = 2,
    DIVISION_PRECEDENCE = 2,
    MOD_PRECEDENCE = 2,

} OPERATOR_PRECEDENCE;


typedef enum TOKEN_TYPE {

    //Tokenisation
    TOK_INVALID,
    TOK_END_ARRAY, //End of array - equivelant to '\0'


    //Token types
    TOK_DEC_MODIFIER, //char, float, void, long, ptr, etc
    TOK_IMMEDIATE,
    TOK_FUNCTION_NAME,
    TOK_VARIABLE,
    TOK_OPERATOR, // '+', '-', etc (INCLUDES FUNCTIONS)
    TOK_CURVED_BRACE, // '(' and ')' ONLY
    TOK_COMPARATOR, //'!=', '==', '>=', etc



    //Datatypes
    TOK_NOT_DATATYPE,
    TOK_VOID,
    TOK_INT,
    TOK_FLOAT,
    TOK_CHAR,
    TOK_LONG,
    TOK_UNSIGNED,
    TOK_ARRAY,
    TOK_POINTER,

    //Conditional statements
    TOK_IF,
    TOK_ELIF,
    TOK_ELSE,
    TOK_FOR,
    TOK_WHILE,
    
    //Function call
    TOK_CALL,
    TOK_RETURN,

    //Inbuilt functions
    TOK_SLEEP,       //Wait
    TOK_OUTPUT,      //Print
    TOK_READ,        //Read from input
    TOK_ALLOCATE,    //Allocate memory
    TOK_FREE,        //Free memory

    //Constants
    TOK_NONE,        //NULL
    TOK_VAL_MAX,     //Max int value
    TOK_VAL_MIN,     //Smallest int value
    // Operators
    TOK_ADD,            // '+'
    TOK_SUBTRACT,       // '-'
    TOK_MULTIPLY,       // '*'
    TOK_DIVIDE,         // '/'
    TOK_MODULUS,        // '%'
    TOK_GREATER_EQUAL,  // '=>'
    TOK_GREATER,        // '>'
    TOK_LESS_EQUAL,     // '<='
    TOK_LESS,           // '<'
    TOK_EQUAL,          // '=='
    TOK_NOT_EQUAL,      // '!='
    // Symbols
    TOK_OPEN_SQUARE,
    TOK_CLOSE_SQUARE,
    TOK_OPEN_CURLY,
    TOK_CLOSE_CURLY,
    TOK_OPEN_PAREN,
    TOK_CLOSE_PAREN,
    TOK_COMMA,
    TOK_SEMICOLON,
    TOK_EQUALS, // Equals for assignments (=)
    TOK_AT,     // Dereference operator   (@)
    TOK_DOLLAR, // Address of operator    ($)
    // Comments
    TOK_MULTILINE_COMMENT,  // '/*  */'
    TOK_SINGLELINE_COMMENT, // '#'


} TOKEN_TYPE;



//Tokeniser structs: 
//Output an array of these for each line

typedef struct Token {

    enum TOKEN_TYPE tokenType; //Actual token itself (for, while, variable, immediate, etc)
    enum TOKEN_TYPE dataType; //float/char/symbol/operator/comparator/etc. TOK_NOT_DATATYPE for for,while,etc

    size_t arraySize; //If this is an array - specify its size - if not set to 0

    union TokenContent {
        size_t variableID; 
        //Each variable has a 'variable ID' that is stored in a map (map.c/h)
        //Variable ID of 0 is set to indicate non-variable/immediate (e.g symbol, 'for', 'if', 'while', etc)


        //Immediates have their values directly stored
        float floatImmediate;
        int intImmediate;
        char charImmediate;
    } TokenContent;

} Token;




//AST
//Relevent information is extracted from line of tokens (array of them), and are put into a struct
//Can then be converted into IR
//Should only need one of these structs per line of source code
//Check for syntax (e.g, '=') in parser, dont need to put them into struct


typedef struct ExpressionTree {

    //To do
    //Basically have a tree of stuff - allows for bodmas
    //Should be able to handle function calls (just call a jump too it)







} ExpressionTree;




typedef struct DeclarationModifiers {
    bool isArray;
    size_t isPointer; //0 if not pointer, >0 to indicate pointer level (e.g isPointer == 2 is equivelant to **)
} DeclarationModifiers;
typedef struct DeclarationStatement {

    /*
    int, x, @, [5] = y;
    Above declares x - an int pointer to an array of 5 elements

    float, x, [5] = y;
    Above declares x - a float array of 5 elements

    char, x = y;
    Above declares x - a char
    */

    //Variable stored information
    Token dataType;

    DeclarationModifiers declarationModifiers; //Declaration modifiers from above struct



    //Variable set equal to this expression
    ExpressionTree *expressionTree;

} DeclarationStatement;



typedef struct IfStatement {

    /*
    Cannot combine statements - must nest (e.g no && or || operator)
    if(x >= 0)
    */


    Token ifType; 
    /*
    if, elif or else - One of these expected:
    TOK_IF,
    TOK_ELIF,
    TOK_ELSE,
    */

    ExpressionTree *expression1;
    Token comparator;
    ExpressionTree *expression2;

} IfStatement;



typedef struct WhileStatement { //Essentially the same structure as IfStatement, not combined to maintain clarity

    /*
    Cannot combine statements - must nest (e.g no && or || operator)
    while(x >= 0)
    */

    ExpressionTree *expression1;
    Token comparator;
    ExpressionTree *expression2;

} WhileStatement;

typedef struct ForStatement {

    /*
    For loop should follow this structure (can only use ints)

    for(x, 0, 10, 1) -> for(int x = 0; x < 10; x++)    

    x should go out of scope after loop ends
    */

    Token variableName;
    Token start;
    Token stop;
    Token increment;


} ForStatement;


typedef struct FunctionStatement {

    Token functionName; //Remember this somewhere

    DeclarationStatement *inputParameterArray;
    //Compiler can essentially just declare these variables in the function the same way its done normally
    //Array of input parameters

} FunctionStatement;






#endif 
