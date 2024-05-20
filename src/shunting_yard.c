#include "shunting_yard.h"



/*
 * Function: shunting_yard
 * -----------------------
 * Converts an array of tokens from infix notation to postfix notation using the Shunting Yard algorithm 
 * developed by Edsger Dijkstra. This function processes operands, operators, and parentheses from the 
 * input token array and organizes them into a postfix format using two stacks to handle operator precedence 
 * and parentheses grouping. The function treats functions as operators, integrating them seamlessly into 
 * the output based on their precedence.
 *
 * Parameters:
 *   tokenArray - Pointer to an array of Token structures representing the infix expression. The array 
 *                must end with a token of type TOK_END_ARRAY.
 *
 * Returns:
 *   Stack - Returns a stack containing the tokens in postfix order. If an error occurs, such as invalid 
 *           token processing or memory allocation failure, a failureStack initialized to an empty state 
 *           is returned.
 *
 * Usage:
 *   Token inputTokens[] = {
 *     {TOK_INT, TOK_VARIABLE, .TokenContent.intImmediate=3}, 
 *     {TOK_ADD, TOK_OPERATOR}, 
 *     {TOK_INT, TOK_VARIABLE, .TokenContent.intImmediate=5}, 
 *     {TOK_END_ARRAY}
 *   };
 *   Stack resultStack = shunting_yard(inputTokens);
 *   // Process the resultStack as needed for evaluation or further compilation tasks.
 *
 * Note:
 *   This function assumes that the input token array is syntactically correct and properly terminated.
 *   It handles memory internally but depends on proper initializations provided by stack_initialise and 
 *   relies on stack operations such as stack_push_Token and stack_pop_Token from 'stack.h'.
 */
Stack shunting_yard(Token *tokenArray) {

    Stack failureStack;
    stack_initialise(&failureStack);

    
    Token result;
    result.tokenType = TOK_INVALID;

    //initialise stacks
    Stack outputStack;
    Stack operatorStack;
    stack_initialise(&outputStack);
    stack_initialise(&operatorStack);

    int i = 0;
    Token topToken;
    topToken.tokenType = TOK_INVALID;

    while(tokenArray[i].tokenType != TOK_END_ARRAY) {

        if(tokenArray[i].tokenType == TOK_VARIABLE || 
        tokenArray[i].tokenType == TOK_IMMEDIATE) { //NOTE - functions are OPERATORS not operands

            if(stack_push_Token(&outputStack, tokenArray[i]) == false) return failureStack;

        } else if(tokenArray[i].tokenType == TOK_OPERATOR || tokenArray[i].tokenType == TOK_FUNCTION_NAME) {

            while(1) {
                topToken = stack_peak_Token(&operatorStack);
                if(topToken.tokenType == TOK_END_ARRAY) break;

                else if(topToken.dataType >= tokenArray[i].dataType) {

                    topToken = stack_pop_Token(&operatorStack);
                    if(stack_push_Token(&operatorStack, topToken) == false) return failureStack;

                } else {

                    break;
                }
            }

            if(stack_push_Token(&outputStack, tokenArray[i]) == false) return failureStack;



        } else if(tokenArray[i].tokenType == TOK_OPEN_PAREN) {

            if(stack_push_Token(&operatorStack, tokenArray[i]) == false) return failureStack;

        } else if(tokenArray[i].tokenType == TOK_CLOSE_PAREN) { 

            while(1) {
                topToken = stack_peak_Token(&operatorStack);
                if(topToken.tokenType == TOK_END_ARRAY) break;

                else if(topToken.dataType != TOK_OPEN_PAREN) {

                    topToken = stack_pop_Token(&operatorStack);
                    if(stack_push_Token(&operatorStack, topToken) == false) return failureStack;

                } else {

                    break;
                }
            }


        } else {

            return failureStack; //Unrecognised token - syntax error
        }

        i++;
    }

    while(1) {

        topToken = stack_pop_Token(&operatorStack);
        if(topToken.tokenType == TOK_END_ARRAY) break;
        if(stack_push_Token(&outputStack, topToken) == false) return failureStack;

    }


    return outputStack;
}



























