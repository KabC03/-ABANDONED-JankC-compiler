#include "tokeniser.h"
#define BUFFER_EXPANSION 10 //Used for expansion of buffer in tokenise function



bool is_symbol(char character) {
    //Check for symbols
    //If symbol - check if next character is symbol also
    //If its not then stop tokenising current block

    //If variable/immediate - also check if next character is symbol
    //If it is then stop tokenising current block

    switch (character) {
        
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '(':
    case ')':

    case '@':
    case '$':
    case '[':
    case ']':
    case ',':

    case '=':
    case '>':
    case '<':
    case '!':

    case '{':
    case '}':

    case '#':
    case ';':

        return true;
        break;
    
    default:
        return false;
    }

    return false;
}









Token assign_properties(char *buffer) {

    Token result;
    result.tokenType = TOK_INVALID;
    
    if(buffer == NULL) {
        result.tokenType = TOK_END_ARRAY;
    } else if (strcmp(validTokens[0], buffer) == 0) { // Check 'void'
        // Handle 'void'
    } else if (strcmp(validTokens[1], buffer) == 0) { // Check 'int'
        // Handle 'int'
    } else if (strcmp(validTokens[2], buffer) == 0) { // Check 'float'
        // Handle 'float'
    } else if (strcmp(validTokens[3], buffer) == 0) { // Check 'char'
        // Handle 'char'
    } else if (strcmp(validTokens[4], buffer) == 0) { // Check 'long'
        // Handle 'long'
    } else if (strcmp(validTokens[5], buffer) == 0) { // Check 'unsigned'
        // Handle 'unsigned'
    } else if (strcmp(validTokens[6], buffer) == 0) { // Check 'if'
        // Handle 'if'
    } else if (strcmp(validTokens[7], buffer) == 0) { // Check 'elif'
        // Handle 'elif'
    } else if (strcmp(validTokens[8], buffer) == 0) { // Check 'else'
        // Handle 'else'
    } else if (strcmp(validTokens[9], buffer) == 0) { // Check 'for'
        // Handle 'for'
    } else if (strcmp(validTokens[10], buffer) == 0) { // Check 'while'
        // Handle 'while'
    } else if (strcmp(validTokens[11], buffer) == 0) { // Check 'none'
        // Handle 'none'
    } else if (strcmp(validTokens[12], buffer) == 0) { // Check 'VAL_MIN'
        // Handle 'VAL_MIN'
    } else if (strcmp(validTokens[13], buffer) == 0) { // Check 'VAL_MAX'
        // Handle 'VAL_MAX'
    } else if (strcmp(validTokens[14], buffer) == 0) { // Check '+'
        // Handle '+'
    } else if (strcmp(validTokens[15], buffer) == 0) { // Check '-'
        // Handle '-'
    } else if (strcmp(validTokens[16], buffer) == 0) { // Check '*'
        // Handle '*'
    } else if (strcmp(validTokens[17], buffer) == 0) { // Check '/'
        // Handle '/'
    } else if (strcmp(validTokens[18], buffer) == 0) { // Check '%%'
        // Handle '%%'
    } else if (strcmp(validTokens[19], buffer) == 0) { // Check '=>'
        // Handle '=>'
    } else if (strcmp(validTokens[20], buffer) == 0) { // Check '>'
        // Handle '>'
    } else if (strcmp(validTokens[21], buffer) == 0) { // Check '<='
        // Handle '<='
    } else if (strcmp(validTokens[22], buffer) == 0) { // Check '<'
        // Handle '<'
    } else if (strcmp(validTokens[23], buffer) == 0) { // Check '=='
        // Handle '=='
    } else if (strcmp(validTokens[24], buffer) == 0) { // Check '!='
        // Handle '!='
    } else if (strcmp(validTokens[25], buffer) == 0) { // Check '='
        // Handle '='
    } else if (strcmp(validTokens[26], buffer) == 0) { // Check 'call'
        // Handle 'call'
    } else if (strcmp(validTokens[27], buffer) == 0) { // Check 'return'
        // Handle 'return'
    } else if (strcmp(validTokens[28], buffer) == 0) { // Check 'read'
        // Handle 'read'
    } else if (strcmp(validTokens[29], buffer) == 0) { // Check 'output'
        // Handle 'output'
    } else if (strcmp(validTokens[30], buffer) == 0) { // Check 'allocate'
        // Handle 'allocate'
    } else if (strcmp(validTokens[31], buffer) == 0) { // Check 'free'
        // Handle 'free'
    } else if (strcmp(validTokens[32], buffer) == 0) { // Check 'sleep'
        // Handle 'sleep'
    } else if (strcmp(validTokens[33], buffer) == 0) { // Check '['
        // Handle '['
    } else if (strcmp(validTokens[34], buffer) == 0) { // Check ']'
        // Handle ']'
    } else if (strcmp(validTokens[35], buffer) == 0) { // Check '{'
        // Handle '{'
    } else if (strcmp(validTokens[36], buffer) == 0) { // Check '}'
        // Handle '}'
    } else if (strcmp(validTokens[37], buffer) == 0) { // Check '('
        // Handle '('
    } else if (strcmp(validTokens[38], buffer) == 0) { // Check ')'
        // Handle ')'
    } else if (strcmp(validTokens[39], buffer) == 0) { // Check ','
        // Handle ','
    } else if (strcmp(validTokens[40], buffer) == 0) { // Check ';'
        // Handle ';'
    } else if (strcmp(validTokens[41], buffer) == 0) { // Check '@'
        // Handle '@'
    } else if (strcmp(validTokens[42], buffer) == 0) { // Check '$'
        // Handle '$'
    } else if (strcmp(validTokens[43], buffer) == 0) { // Check '/*'
        // Handle '/*'
    } else if (strcmp(validTokens[44], buffer) == 0) { // Check '#'
        // Handle '#'
    } else {
        // Handle unknown input
        result.tokenType = TOK_INVALID;
    }

    return result;
}





//User calls this
Token *tokenise(char *inputLine) {

    Token *tokensOut = NULL; //Array of tokens
    size_t tokensOutSize = 0;

    //Dynamic array
    char *buffer = NULL;
    size_t bufferSize = 0;



    int i = 0; //Iterate through inputLine
    int j = 0; //Assign to buffer
    int k = 0; //Assign to tokensOut
    Token tokenOut;
    tokenOut.tokenType = TOK_INVALID;

    while(inputLine[i] != '\0') {

        //Check if buffer needs to be expanded
        if((bufferSize - 1) % j == 0) { //Allocate memory when 1 byte away from reaching end - allows space of '\0'
            buffer = realloc(buffer, bufferSize + BUFFER_EXPANSION);
            if(buffer == NULL) return NULL;

            bufferSize += BUFFER_EXPANSION;
        }


        if((tokensOutSize) % k == 0) { 
            tokensOut = realloc(tokensOut, tokensOutSize + BUFFER_EXPANSION);
            if(tokensOut == NULL) return NULL;

            tokensOutSize += BUFFER_EXPANSION;
        }
        


        buffer[j] = inputLine[i];

        if(is_symbol(inputLine[i]) == true) { //Symbol detected - if next character isnt symbol or space then stop tokenising this block

            if(is_symbol(inputLine[i + 1]) == true || inputLine[i + 1] == ' ') {

                j++;
                i++;
                continue;
                //Continue tokenising this block
            } else {
                bufferSize = 0;
                j = 0;
                buffer[i + 1] = '\0';
                //Check if token is valid by comparing buffer to validTokens
                //Then assign propertiess
                tokenOut = assign_properties(buffer);

                if(tokenOut.dataType == TOK_INVALID) {
                    //Unrecognised token
                    break;
                } 
                tokensOut[k] = tokenOut;
                k++;

            }

        } else { //Var/immediate detected - if next character is symbol or space stop tokenising this block

            if(is_symbol(inputLine[i + 1]) == false || inputLine[i + 1] == ' ') {

                j++;
                i++;
                continue;
                //Continue tokenising this block

            } else {
                bufferSize = 0;
                j = 0;
                buffer[i + 1] = '\0';
                //Stop tokenising this block
                //Check if token is valid by comparing buffer to validTokens
                //Then assign properties

                tokenOut = assign_properties(buffer);

                if(tokenOut.dataType == TOK_INVALID) {
                    //Unrecognised token
                    break;
                } 
                tokensOut[k] = tokenOut;
                k++;
                
            }

        }


    }



    if(buffer != NULL) free(buffer);

    return tokensOut;
}








































