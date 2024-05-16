#include "stack.h"


/*
 * Function: print_stack
 * ----------------------
 * Prints the contents of the stack from the top to the bottom.
 * Each stack node's ID is printed in order. An empty stack will display "empty".
 *
 * head: Pointer to the top node of the stack.
 */
void print_stack(StackNode *head) {

    printf(" ┌───────┐\n");
    if(head == NULL) {
        printf(" │ empty │\n");
    } else {
        while(head != NULL) {
            printf(" │  %2zu   │\n", head->ID);
            head = head->nextPtr;
            printf(" ├───────┤\n");
        }

    }

    printf(" └───────┘\n");
    return;
}


/*
 * Function: push_stack
 * ---------------------
 * Pushes a new value onto the stack. This function allocates a new StackNode,
 * assigns it the given value, and adjusts the stack pointers.
 *
 * head: A pointer to the pointer of the top node of the stack.
 * newValue: The new value to be pushed onto the stack.
 *
 * Returns: true if the node was successfully pushed, false if allocation failed.
 */
bool push_stack(StackNode **head, size_t newValue) {

    if(head == NULL) return false;
    StackNode *newNode = malloc(sizeof(StackNode));
    if(newNode == NULL) return false;
    newNode->ID = newValue;
    newNode->nextPtr = *head;
    *head = newNode;

    return true;
}


/*
 * Function: pop_stack
 * --------------------
 * Pops the top value from the stack and returns it. This function removes the top node
 * of the stack, retrieves its value, frees the node, and adjusts the stack's top pointer.
 *
 * head: A pointer to the pointer of the top node of the stack.
 *
 * Returns: The ID of the popped node if successful, -1 if the stack is empty or head is NULL.
 */
size_t pop_stack(StackNode **head) {
    if(head == NULL) return -1;
    else if(*head == NULL) return -1; // Return max value on failure, interpreted as -1 for size_t

    size_t returnVal = (*head)->ID;
    StackNode *freePtr = (*head);
    *head = (*head)->nextPtr;
    free(freePtr);

    return returnVal;
}


/*
 * Function: destroy_stack
 * ------------------------
 * Frees all nodes in the stack and sets the stack's head to NULL.
 * This function iterates through the stack and frees each node.
 *
 * head: A pointer to the pointer of the top node of the stack.
 *
 * Returns: true if the stack was successfully destroyed, false if the input was NULL.
 */
bool destroy_stack(StackNode **head) {

    if(head == NULL) return false;
    if(*head == NULL) return false; //Stack empty already

    StackNode *currentPtr = (*head);
    StackNode *prevPtr = (*head);
    while(currentPtr != NULL) {

        currentPtr = currentPtr->nextPtr;
        free(prevPtr);
        prevPtr = currentPtr;
    }

    return true;
}













