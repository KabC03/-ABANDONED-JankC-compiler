/*
 * shunting_yard.h
 *
 * Description:
 * This module implements the Shunting Yard algorithm, developed by Edsger Dijkstra, to convert infix expressions 
 * to postfix notation. The conversion facilitates easier and more efficient evaluation of mathematical expressions 
 * during compilation. This module is crucial for parsing expressions in the compiler, particularly when dealing with 
 * operator precedence and parentheses management.
 * 
 * The Shunting Yard algorithm uses a stack to handle operators and parentheses, ensuring that the output postfix 
 * expression adheres to the correct order of operations as dictated by arithmetic rules.
 *
 * Data Structure:
 * The module relies on the 'Stack' data structure defined in 'stack.h' to manage both operators and operands during 
 * the conversion process. The algorithm processes tokens (operands and operators) from an input array and arranges 
 * them into a postfix format using the stack for intermediate storage.
 *
 * Usage:
 * - Call `shunting_yard(Token *tokenArray)` with an array of tokens representing the infix expression.
 * - The function returns a Stack containing the tokens in postfix order.
 * - This stack can then be used for further processing, such as expression evaluation or code generation in the compiler.
 *
 * Note:
 * It is assumed that the input tokens are part of a well-formed expression. Error handling in the function returns a 
 * special 'failureStack' if an issue is encountered during processing, such as memory allocation failure or invalid token types.
 */


#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "compiler_structs.h"
#include "stack.h"

Stack shunting_yard(Token *tokenArray);



#endif // SHUNTING_YARD_H

