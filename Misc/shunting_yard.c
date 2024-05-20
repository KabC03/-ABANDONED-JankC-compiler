#include "shunting_yard.h"




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



























