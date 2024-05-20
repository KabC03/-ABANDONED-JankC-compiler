/*
 * shunting_yard.h
 *
 * Description:
 * This module implements the Shunting Yard algorithm, originally developed by Edsger Dijkstra, to convert infix expressions
 * to postfix notation. The conversion simplifies the evaluation and manipulation of mathematical and logical expressions during
 * the compilation process. It is particularly crucial when the compiler needs to handle operator precedence and manage parentheses
 * effectively to maintain the correct order of operations.
 *
 * The algorithm treats function calls syntactically similar to operators, incorporating them into the output expression
 * with the same precedence handling mechanisms. This allows for seamless integration of function calls into complex expressions,
 * ensuring that they are evaluated at the correct times relative to other operators.
 *
 * Data Structure:
 * The 'shunting_yard' function utilizes the 'Stack' data structure defined in 'stack.h'. This stack is used to temporarily hold
 * operators, parentheses, and function names as the algorithm processes tokens from the input array. These tokens are then
 * systematically pushed to the output stack based on their precedence, ensuring that the resulting postfix expression is correctly
 * formatted for subsequent evaluation or further compilation stages.
 *
 * Functionality:
 * - Operators and functions are handled with predefined precedence levels to dictate their order in the output expression.
 * - Parentheses are used to override these precedence rules when necessary, ensuring expressions within them are evaluated first.
 * - The algorithm supports error handling by returning a 'failureStack' when it encounters invalid tokens, memory allocation failures,
 *   or syntactically incorrect expressions.
 *
 * Usage:
 * - Initialize an array of Token structures representing an infix expression. This array should end with a TOK_END_ARRAY type token.
 * - Call `shunting_yard(Token *tokenArray)` with this array. The function processes the tokens and returns a Stack in postfix order.
 * - The returned Stack can be used directly for expression evaluation or further syntactic analysis in later stages of the compiler.
 *
 * Example:
 * Token tokens[] = {{TOK_INT, TOK_VARIABLE, .TokenContent.intImmediate=3}, {TOK_ADD, TOK_OPERATOR}, {TOK_INT, TOK_VARIABLE, .TokenContent.intImmediate=5}, {TOK_END_ARRAY}};
 * Stack postfix = shunting_yard(tokens);
 * // The 'postfix' Stack now contains the postfix notation of the tokens, ready for evaluation or further processing.
 *
 * Note:
 * The input tokens must be well-formed and complete, including an end marker (TOK_END_ARRAY). The function assumes that the input is syntactically valid
 * and will handle errors by returning a special 'failureStack'. Memory management, especially the handling of dynamic allocations in 'stack.h', is critical
 * to ensure the robustness of this module.
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

