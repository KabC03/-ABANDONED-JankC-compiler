/*
 * label_stack.h
 *
 * Description:
 * This module provides functionality for a stack data structure that is used to manage labels for nested control
 * flow constructs in a compiler's intermediate representation (IR). Each time a nested control statement like 'if',
 * 'while', or similar is encountered during compilation, a unique ID is pushed onto the stack. This ID is then used
 * to generate labels in the IR, ensuring the correct scope and sequence for nested statements.
 *
 * The stack supports dynamic management of these labels through push, pop, and clean-up operations, facilitating
 * correct nesting and ending of control structures during the compilation process.
 *
 * Data Structure:
 * The stack is implemented as a linked list of StackNode structures. Each StackNode contains an ID representing
 * a label for a nested statement. This linked list approach allows the stack to dynamically adjust in size as
 * more nested blocks are entered or exited.
 *
 * Usage:
 * - To manage the entry into a new nested statement, use `push_stack` to add a new label ID.
 * - To manage the exit from a nested statement, use `pop_stack` to remove the most recent label ID.
 * - To debug or verify the current nesting of statements, use `print_stack`.
 * - To clean up the stack upon completion of parsing or when resetting compiler states, use `destroy_stack`.
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
