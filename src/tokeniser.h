
/*
 * tokeniser.h
 *
 * Description:
 * Provides the declaration of the tokenise function, which is a core component of the lexical analysis phase in
 * a compiler's workflow. This function is responsible for converting a line of source code into a sequence of tokens,
 * which are the basic units of syntax within the language being compiled. The function utilizes structures and
 * types defined in 'compiler_structs.h' to categorize and return these tokens, facilitating subsequent parsing stages.
 *
 * Key Functions:
 * - Token *tokenise(char *inputLine): Takes a single string (inputLine) as input and returns a dynamically allocated
 *   array of Token structures. Each Token structure represents a distinct lexical unit extracted from the input string.
 *   The function handles identification and categorization of various token types including keywords, identifiers,
 *   operators, and delimiters based on the language's syntax rules.
 *
 * Dependencies:
 * - compiler_structs.h: Includes definitions for the Token structure and possibly other related types or constants
 *   critical for the tokenisation process.
 * - Standard Libraries:
 *   - stdio.h: Used for input/output operations, primarily for debugging purposes.
 *   - stdlib.h: Required for memory management functions such as malloc and free.
 *   - stdbool.h: Provides the 'bool' type for boolean expressions and conditions.
 *   - string.h: Utilized for string manipulation functions which are essential for comparing token strings and handling them.
 *
 * Notes:
 * - The 'tokenise' function is expected to handle memory allocation for the array of tokens it returns. It is the
 *   caller's responsibility to ensure that this memory is properly freed after use to avoid memory leaks.
 * - Error handling within 'tokenise' should account for and manage issues such as memory allocation failures and
 *   invalid input scenarios gracefully, returning NULL in such cases to indicate failure.
 */
#ifndef TOKENISER_H 
#define TOKENISER_H 
#include "compiler_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

Token *tokenise(char *inputLine);

#endif 



