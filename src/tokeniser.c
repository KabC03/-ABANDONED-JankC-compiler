#include "tokeniser.h"
#define BUFFER_EXPANSION 10 //Used for expansion of buffer in tokenise function


/**
 * WARNING - does not check ALL symbols - DO NOT USE FOR THIS PURPOSE. E.g doesnt check for '.', '|', etc
 * Evaluates whether a character is considered a symbol within the context of the tokenizer.
 * Symbols include special characters that could denote operators, punctuation, or other significant tokens in the language syntax.
 * 
 * The function aids in determining token boundaries based on the context:
 * - If the previous character is alphanumeric and the current character is a symbol, this signifies the start of a new token block.
 * - If the previous character is a symbol and the current character continues to be a symbol, the tokenization continues within the same block.
 * - Conversely, if the current character is not a symbol following any character, it may indicate the start of a new token block.
 *
 * @param character The character to be evaluated.
 * @return true if the character is a symbol, indicating a special token; false if it is alphanumeric or other non-symbolic character.
 */
bool is_symbol(char character) {
    //Check for symbols - SHOULD NOT check for '.'
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
    //case '.': //IGNORE DECIMALS

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







/**
 * Checks if a given string is a valid function name according to the defined naming conventions.
 * A valid function name must start with "fn_" and should not contain any symbols.
 *
 * Usage:
 * This function is used during tokenization to categorize tokens that represent function identifiers.
 *
 * @param buffer A pointer to a null-terminated string containing the token to check.
 * @return true if the string matches the function naming criteria, false otherwise.
 */
bool function_name_check(char *buffer) {

    if(buffer == NULL) return false;

    char fnSubstring[] = "fn_";


    //Check at least 3 characters are present (3 for fn_ and a function name at least 1 chracter long)
    if(strlen(buffer) < 4) return false;


    if(strncmp(fnSubstring, buffer, strlen(fnSubstring)) == 0) return true;

    return false;
}





/**
 * Verifies whether a string qualifies as a valid variable name in the programming language.
 * A valid variable name must not contain any symbols and should adhere to language-specific naming rules.
 *
 * Usage:
 * This function helps in distinguishing variable tokens during the lexical analysis phase.
 *
 * @param buffer A pointer to a null-terminated string to evaluate.
 * @return true if the string is a valid variable name, false otherwise.
 */
bool variable_name_check(char *buffer) {

    if(buffer == NULL) return false;


    for(int i = 0; i < strlen(buffer) + 1; i++) {

        if(i == 0) {
            if(isdigit(buffer[0]) != 0) return false; //First character should not be number

        } else if(isdigit(buffer) != 0 || isalpha(buffer) != 0) { //Expected a character or number

            return false;
        }

    }

    return true;
}



/**
 * Determines if a string represents an immediate value, which is a numeric literal that does not contain symbols or letters.
 *
 * Usage:
 * This function is pivotal in classifying numeric literals during tokenization, ensuring that literals like numbers are correctly identified.
 *
 * @param buffer A pointer to a null-terminated string that potentially contains an immediate value.
 * @return true if the string represents an immediate numeric value, false otherwise.
 */
bool immediate_check(char *buffer) {

    if(buffer == NULL) return false;

    bool seenDecimal = false;

    for(int i = 0; i < strlen(buffer) + 1; i++) {

        if(buffer[i] == '.' && seenDecimal == false) {

            seenDecimal = true;

        } else if(buffer[i] == '.' && seenDecimal == true) {
            
            return false; //Unexpeced '.'

        } else if(isdigit(buffer[i]) != 0) {

            return false; //Expected a digit, got something else
        }

    }


    return true;
}



/**
 * Evaluates if a string correctly represents a character literal in the language.
 * A valid character literal should consist of exactly one character enclosed within single quotes (' ').
 *
 * Usage:
 * Used during the parsing process to validate tokens as character literals, ensuring they conform to the syntax rules.
 *
 * @param buffer A pointer to a null-terminated string to check.
 * @return true if the string is a properly formatted character literal, false otherwise.
 */
bool char_check(char *buffer) {

    if(buffer == NULL) return false;

    if(strlen(buffer) == 3) {

        if(buffer[0] == '\'' && buffer[2] == '\'') return true; 
    }


    return false;

}






/**
 * Assigns token properties based on the content of the buffer.
 * This function maps a string buffer to a specific token type by comparing it against known valid tokens.
 *
 * @param buffer A pointer to a null-terminated string that contains the token to process.
 * @return A Token structure with the token type set according to the content of the buffer.
 *         If the buffer matches a known token, the corresponding token type is set.
 *         If no match is found, TOK_INVALID is set as the token type.
 */
Token assign_properties(char *buffer) {

    Token result;
    result.tokenType = TOK_INVALID;
    
    if(buffer == NULL) {
        result.tokenType = TOK_END_ARRAY;
    } else if (strcmp(validTokens[0], buffer) == 0) { // Check 'void'
        // Handle 'void'
        result.tokenType = TOK_VOID;
        result.dataType = TOK_DEC_MODIFIER;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;


    } else if (strcmp(validTokens[1], buffer) == 0) { // Check 'int'
        // Handle 'int'
        result.tokenType = TOK_INT;
        result.dataType = TOK_DEC_MODIFIER;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;

    } else if (strcmp(validTokens[2], buffer) == 0) { // Check 'float'
        // Handle 'float'
        result.tokenType = TOK_FLOAT;
        result.dataType = TOK_DEC_MODIFIER;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;


    } else if (strcmp(validTokens[3], buffer) == 0) { // Check 'char'
        // Handle 'char'
        result.tokenType = TOK_CHAR;
        result.dataType = TOK_DEC_MODIFIER;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;


    } else if (strcmp(validTokens[4], buffer) == 0) { // Check 'long'
        // Handle 'long'
        result.tokenType = TOK_LONG;
        result.dataType = TOK_DEC_MODIFIER;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;


    } else if (strcmp(validTokens[5], buffer) == 0) { // Check 'unsigned'
        // Handle 'unsigned'
        result.tokenType = TOK_UNSIGNED;
        result.dataType = TOK_DEC_MODIFIER;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;





    } else if (strcmp(validTokens[6], buffer) == 0) { // Check 'if'
        // Handle 'if'
        result.tokenType = TOK_IF;
        result.dataType = TOK_LOOP;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;

    } else if (strcmp(validTokens[7], buffer) == 0) { // Check 'elif'
        // Handle 'elif'
        result.tokenType = TOK_ELIF;
        result.dataType = TOK_LOOP;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;

    } else if (strcmp(validTokens[8], buffer) == 0) { // Check 'else'
        // Handle 'else'
        result.tokenType = TOK_ELSE;
        result.dataType = TOK_LOOP;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;


    } else if (strcmp(validTokens[9], buffer) == 0) { // Check 'for'
        // Handle 'for'
        result.tokenType = TOK_FOR;
        result.dataType = TOK_LOOP;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;

    } else if (strcmp(validTokens[10], buffer) == 0) { // Check 'while'
        // Handle 'while'
        result.tokenType = TOK_WHILE;
        result.dataType = TOK_LOOP;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;




    } else if (strcmp(validTokens[11], buffer) == 0) { // Check 'none'
        // Handle 'none'
        result.tokenType = TOK_NONE;
        result.dataType = TOK_CONSTANT;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;

    } else if (strcmp(validTokens[12], buffer) == 0) { // Check 'VAL_MIN'
        // Handle 'VAL_MIN'
        result.tokenType = TOK_VAL_MIN;
        result.dataType = TOK_CONSTANT;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[13], buffer) == 0) { // Check 'VAL_MAX'
        // Handle 'VAL_MAX'
        result.tokenType = TOK_VAL_MAX;
        result.dataType = TOK_CONSTANT;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;




    } else if (strcmp(validTokens[14], buffer) == 0) { // Check '+'
        // Handle '+'
        result.tokenType = TOK_ADD;
        result.dataType = TOK_OPERATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[15], buffer) == 0) { // Check '-'
        // Handle '-'
        result.tokenType = TOK_SUBTRACT;
        result.dataType = TOK_OPERATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[16], buffer) == 0) { // Check '*'
        // Handle '*'
        result.tokenType = TOK_MULTIPLY;
        result.dataType = TOK_OPERATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[17], buffer) == 0) { // Check '/'
        // Handle '/'
        result.tokenType = TOK_DIVIDE;
        result.dataType = TOK_OPERATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[18], buffer) == 0) { // Check '%%'
        // Handle '%%'
        result.tokenType = TOK_MODULUS;
        result.dataType = TOK_OPERATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;




    } else if (strcmp(validTokens[19], buffer) == 0) { // Check '=>'
        // Handle '=>'
        result.tokenType = TOK_GREATER_EQUAL;
        result.dataType = TOK_COMPARATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[20], buffer) == 0) { // Check '>'
        // Handle '>'
        result.tokenType = TOK_GREATER;
        result.dataType = TOK_COMPARATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[21], buffer) == 0) { // Check '<='
        // Handle '<='
        result.tokenType = TOK_LESS_EQUAL;
        result.dataType = TOK_COMPARATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[22], buffer) == 0) { // Check '<'
        // Handle '<'
        result.tokenType = TOK_LESS;
        result.dataType = TOK_COMPARATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[23], buffer) == 0) { // Check '==' (EQUALS FOR COMPARISON)
        // Handle '=='
        result.tokenType = TOK_EQUAL;
        result.dataType = TOK_COMPARATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[24], buffer) == 0) { // Check '!=' 
        // Handle '!='
        result.tokenType = TOK_NOT_EQUAL;
        result.dataType = TOK_COMPARATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[25], buffer) == 0) { // Check '=' (EQUALS FOR ASSIGNMENTS)
        // Handle '='
        result.tokenType = TOK_EQUALS;
        result.dataType = TOK_DEC;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;





    } else if (strcmp(validTokens[26], buffer) == 0) { // Check 'call'
        // Handle 'call'
        result.tokenType = TOK_CALL;
        result.dataType = TOK_USER_FUNC;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[27], buffer) == 0) { // Check 'return'
        // Handle 'return'
        result.tokenType = TOK_RETURN;
        result.dataType = TOK_USER_FUNC;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;




    } else if (strcmp(validTokens[28], buffer) == 0) { // Check 'read'
        // Handle 'read'
        result.tokenType = TOK_READ;
        result.dataType = TOK_INBUILD_FUNC;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[29], buffer) == 0) { // Check 'output'
        // Handle 'output'
        result.tokenType = TOK_OUTPUT;
        result.dataType = TOK_INBUILD_FUNC;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[30], buffer) == 0) { // Check 'allocate'
        // Handle 'allocate'
        result.tokenType = TOK_ALLOCATE;
        result.dataType = TOK_INBUILD_FUNC;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[31], buffer) == 0) { // Check 'free'
        // Handle 'free'
        result.tokenType = TOK_FREE;
        result.dataType = TOK_INBUILD_FUNC;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[32], buffer) == 0) { // Check 'sleep'
        // Handle 'sleep'
        result.tokenType = TOK_SLEEP;
        result.dataType = TOK_INBUILD_FUNC;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;




    } else if (strcmp(validTokens[33], buffer) == 0) { // Check '['
        // Handle '['
        result.tokenType = TOK_OPEN_SQUARE;
        result.dataType = TOK_OTHER_SYMBOL;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[34], buffer) == 0) { // Check ']'
        // Handle ']'
        result.tokenType = TOK_CLOSE_SQUARE;
        result.dataType = TOK_OTHER_SYMBOL;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[35], buffer) == 0) { // Check '{'
        // Handle '{'
        result.tokenType = TOK_OPEN_CURLY;
        result.dataType = TOK_OTHER_SYMBOL;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[36], buffer) == 0) { // Check '}'
        // Handle '}'
        result.tokenType = TOK_CLOSE_CURLY;
        result.dataType = TOK_OTHER_SYMBOL;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[37], buffer) == 0) { // Check '('
        // Handle '('
        result.tokenType = TOK_OPEN_PAREN;
        result.dataType = TOK_OTHER_SYMBOL;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[38], buffer) == 0) { // Check ')'
        // Handle ')'
        result.tokenType = TOK_CLOSE_PAREN;
        result.dataType = TOK_OTHER_SYMBOL;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[39], buffer) == 0) { // Check ','
        // Handle ','
        result.tokenType = TOK_COMMA;
        result.dataType = TOK_OTHER_SYMBOL;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[40], buffer) == 0) { // Check ';'
        // Handle ';'
        result.tokenType = TOK_SEMICOLON;
        result.dataType = TOK_OTHER_SYMBOL;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;






    } else if (strcmp(validTokens[41], buffer) == 0) { // Check '@'
        // Handle '@'
        result.tokenType = TOK_AT;
        result.dataType = TOK_OPERATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[42], buffer) == 0) { // Check '$'
        // Handle '$'
        result.tokenType = TOK_DOLLAR;
        result.dataType = TOK_OPERATOR;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;





    } else if (strcmp(validTokens[43], buffer) == 0) { // Check '/*'
        // Handle '/*'
        result.tokenType = TOK_MULTILINE_COMMENT;
        result.dataType = TOK_COMMENT;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;
    } else if (strcmp(validTokens[44], buffer) == 0) { // Check '#'
        result.tokenType = TOK_SINGLELINE_COMMENT;
        result.dataType = TOK_COMMENT;
        result.arraySize = 0;
        result.TokenContent.variableID = 0;




    } else if(function_name_check(buffer) == true) {  //Function starts with fn_ and has no symbols

    } else if(variable_name_check(buffer) == true) {  //Variable contains no symbols

    } else if(immediate_check(buffer) == true) { //Immediate contains no symbols or letters

    } else if(char_check(buffer) == true) { //Char should only be 1 character and surrounded in ' '

    } else {
        // Handle unknown input
        result.tokenType = TOK_INVALID;
    }




    //Else is unknown



    return result;
}





/**
 * Tokenizes a given input line into a dynamic array of tokens.
 * The function processes the input line character by character, and uses the `is_symbol`
 * function to determine when a token ends. Each token is processed and properties are assigned
 * using `assign_properties`. Memory for tokens and the buffer is dynamically managed.
 *
 * @param inputLine A pointer to a null-terminated string from which tokens will be extracted.
 * @return A pointer to an array of Token structures, each representing a token extracted
 *         from the input. If a memory allocation fails during processing, NULL is returned.
 *         The caller is responsible for freeing the returned array.
 */
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








































