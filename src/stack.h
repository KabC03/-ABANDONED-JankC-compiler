/*
 * stack.h
 *
 * Description:
 * This module provides a generic stack data structure designed to manage diverse data types for a compiler's 
 * needs, particularly for nested control flow constructs (labels) and handling tokens during the shunting yard algorithm 
 * in intermediate representation (IR) processing.
 * 
 * The stack facilitates dynamic management of data, supporting operations like push, pop, and clean-up, which 
 * are crucial for correct nesting of control structures and token management in parsing expressions.
 *
 * Data Structure:
 * The stack is implemented using a linked list of StackNode structures, where each StackNode contains a void 
 * pointer to handle generic data types. This allows the stack to adapt dynamically as different types of data 
 * are pushed or popped, depending on the compilation stage or context.
 *
 * Usage:
 * - Use `stack_push_size_t` and `stack_pop_size_t` to manage labels for control blocks like 'if' and 'while'.
 * - Use `stack_push_Token` and `stack_pop_Token` for managing tokens during expression parsing with the shunting 
 *   yard algorithm.
 * - `stack_print_size_t` and `stack_print_Token` can be used to debug or verify the stack's contents.
 * - Use `stack_destroy_size_t` and `stack_destroy_Token` to properly free memory associated with stack items
 *   when the stack is no longer needed or before the compiler resets its state.
 *
 * Note:
 * The internal structure of the stack is hidden from the user. Users should only interact with the stack through 
 * the provided functions for specific data types. Generic stack functions and internal structures are not visible 
 * outside this module.
 */

#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "compiler_structs.h"


//User should never see this
typedef struct StackNode StackNode; //Opaque pointer

typedef struct Stack {

    StackNode *head; //Head of stack - user uses this

} Stack;


// Stack initialisation
void stack_initialise(Stack *stack);




// Stack operations for size_t data
bool stack_push_size_t(Stack *stack, size_t data);
size_t stack_pop_size_t(Stack *stack);
void stack_destroy_size_t(Stack *stack);
void stack_print_size_t(Stack *stack);


// Stack operations for Token data
bool stack_push_Token(Stack *stack, Token data);
Token stack_pop_Token(Stack *stack);
void stack_destroy_Token(Stack *stack);
void stack_print_Token(Stack *stack);




#endif // STACK_H
