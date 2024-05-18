/*
 * compiler_structs.c
 *
 * Description:
 * This file contains an array of strings representing the valid syntax tokens that can be recognized by the compiler's lexer.
 * Each token corresponds to a syntactic element used in the language, including data types, control structures, operators, 
 * punctuation, and other special symbols necessary for the parsing process.
 *
 * Usage:
 * This array is utilized during the lexical analysis phase to match sequences of characters in the source code to known tokens,
 * facilitating the tokenization process which precedes syntax analysis and AST construction.
 */

static char* validTokens[] = {
    "void", "int", "float", "char", "long", "unsigned",  // Data types
    "if", "elif", "else",                              // Conditional statements
    "for", "while",                                    // Loop structures
    "none", "VAL_MIN", "VAL_MAX",                      // Constants
    "+", "-", "*", "/", "%%", "=>", ">", "<=", "<", "==", "!=", "=",  // Operators
    "call", "return",                                  // Function calls and returns
    "read", "output", "allocate", "free", "sleep", // Built-in functions
    "[", "]", "{", "}", "(", ")", ",", ";", "@", "$",  // Punctuation and special symbols
    "/*", "#"                                          // Comment delimiters
};

/*
 * Function Descriptions:
 * 
 * read(char type) - Read a datatype from the input byte by byte. The compiler determines the number of bytes to read for each type.
 * 
 * output(char type, value) - Output a binary value of type 'type' to the output. The compiler determines the number of bytes to output for each type.
 * 
 * allocate(int bytes, variable) - Allocate a certain number of bytes to a variable of type pointer.
 * 
 * free(variable) - Free a variable and all memory associated with it (including arrays).
 * 
 * sleep(float time) - Sleep for a number of seconds (based on clock cycles). The compiler knows how many clock cycles per second.
 */
