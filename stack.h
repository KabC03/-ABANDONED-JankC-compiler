/*
 * stack.h
 *
 * Description:
 * This module provides functionality for a stack data structure specifically designed to manage the scope and control
 * flow constructs in a compiler. Each block-like construct ('if', 'while', etc.) receives a unique ID when it is
 * encountered, and this ID is used to create labels in the compiler's intermediate representation (IR).
 * The stack supports operations such as push, pop, and destruction, allowing for efficient management of block scopes
 * during the compilation process.
 *
 * Data Structure:
 * The stack is implemented as a linked list of StackNode structures, where each StackNode holds an ID representing a
 * control flow construct. This allows for dynamic adjustment of the stack size as blocks are entered and exited during
 * parsing.
 *
 * Usage:
 * - To push a new control block ID onto the stack, use `push_stack`.
 * - To pop the most recent control block ID off the stack, use `pop_stack`.
 * - To print the current state of the stack for debugging, use `print_stack`.
 * - To clean up the stack at the end of its use or when resetting the compiler state, use `destroy_stack`.
 */

#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct StackNode {
    size_t ID;              // Unique identifier for a control block
    struct StackNode *nextPtr; // Pointer to the next node in the stack
} StackNode;

// Function prototypes for stack operations
void print_stack(StackNode *head);
bool push_stack(StackNode **head, size_t newValue);
size_t pop_stack(StackNode **head);
bool destroy_stack(StackNode **head);

#endif // STACK_H
