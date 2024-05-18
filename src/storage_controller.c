#include "storage_controller.h"

//Note - only expect variables in registers since addi/subi instructions can be implemented in hardware
//Not pseudonstructions - therefore no point in storing immediates in register or RAM




//Array used for registers since it is small, faster than LL
static size_t REGSize = 0;
static Token *REGArray = NULL;

static size_t *REGCallArray = NULL; 
//Counts how many times a variable has been loaded from a register
//Registers with low counts are replaced in push function
//Reset when a variable is removed

static size_t RAMSize = 0;
static Token *RAMArray = NULL;









/*
 * Function: print_ram
 * -------------------
 * Prints the variable/array IDs and sizes stored in RAM.
 * The output includes the memory address (index) in hexadecimal format, the variable ID, and the size of the array.
 * This function helps in debugging by displaying the current state of the RAM array.
 *
 * Prints:
 *   Address - The index in RAM, printed as a hexadecimal number.
 *   ID      - The variable ID stored at that address.
 *   Size    - The size of the array if the token is an array type.
 */
void print_ram(void) {
    //Prints variable/array IDs in RAM

    if(RAMArray == NULL) {
        printf("RAM not initialised\n");
    } else {
        printf("Address         | ID     | Size    |\n");
        printf("----------------|--------|---------\n");
        for (int i = 0; i < RAMSize; i++) {
            printf("%-16x | %-6zu | %-7zu |\n", i, RAMArray[i].TokenContent.variableID, RAMArray[i].arraySize);
        }
    }
}

/*
 * Function: print_registers
 * -------------------------
 * Prints the variable IDs stored in the registers.
 * The output includes the register index (printed in hexadecimal format) and the variable ID.
 * This function is useful for debugging by showing the current state of the register array.
 *
 * Prints:
 *   Register - The index of the register, printed as a hexadecimal number.
 *   ID       - The variable ID stored in the register.
 */
void print_reg(void) {
    //Prints variable IDs in registers

    if(REGArray == NULL || REGCallArray == NULL) {
        printf("Registers not initialised\n");
    } else {
        printf("Register        | ID     |\n");
        printf("----------------|--------|\n");
        for (int i = 0; i < REGSize; i++) {
            printf("%-16x | %-6zu |\n", i, REGArray[i].TokenContent.variableID);
        }
    }
}





/*
 * Function: initialise_memory
 * ---------------------------
 * Initialises memory arrays for registers (REGArray) and RAM (RAMArray) based on the specified sizes.
 * Both arrays are zero-initialized to indicate free spaces, a crucial step for managing memory availability.
 *
 * Parameters:
 *   setRegSize - the size to set for the register array
 *   setRamSize - the size to set for the RAM array
 *
 * Returns:
 *   true if both memory arrays are successfully allocated and initialized,
 *   false if any allocation fails.
 */
bool initialise_memory(size_t setRegSize, size_t setRamSize) { 
    //Initialise registers/ram
    REGSize = setRegSize;
    RAMSize = setRamSize;

    //Important - bytes are zeroed - this is how compiler knows free space is available
    REGArray = (Token*)calloc(setRegSize, sizeof(Token));
    REGCallArray = (size_t*)calloc(setRegSize, sizeof(Token));

    RAMArray = (Token*)calloc(setRamSize, sizeof(size_t));

    if(REGArray == NULL || REGCallArray == NULL || RAMArray == NULL) return false;

    return true;
}


/*
 * Function: destroy_memory
 * ------------------------
 * Frees all allocated memory for REGArray, REGCallArray, and RAMArray. This function should be called
 * at the end of program execution to clean up all allocated resources and prevent memory leaks.
 *
 * Returns:
 *   true if all memory was successfully freed,
 *   false if any of the memory arrays were not initialized prior to this call.
 */
bool destroy_memory(void) {
    //Call this at the end of main to clean up
    if(REGArray == NULL || REGCallArray == NULL || RAMArray == NULL) return false;
    else {
        free(REGArray);
        free(REGCallArray);
        free(RAMArray);
    }
    return true;
}


/*
 * Function: reserve_ram
 * ---------------------
 * Attempts to allocate a specified size in RAM for a given token. If the size is zero, it allocates
 * the minimum space required by the datatype of the token. This function searches for a contiguous block
 * of free memory in RAMArray large enough to accommodate the request.
 *
 * Parameters:
 *   input - the token to store in RAM
 *   size - the size of memory to reserve (can be zero to auto-determine based on datatype)
 *
 * Returns:
 *   true if the memory was successfully reserved,
 *   false otherwise (e.g., not enough space).
 */
bool reserve_ram(Token input, size_t size) { 
    //Reserve some space in RAM - basic malloc
    //Note that first element of array should contain array field in 'input' to specify it is an array
    //It also has a name - like variables so the compiler can find it

    //Zero size asks the function to reserve the minumum amount of space for the datatype
    //E.g int - 2 bytes, char - 1 byte, etc


    for(int i = 0; i < REGSize; i++) {


        if(RAMArray[i].TokenContent.variableID == '\0') { //Check for empty space (zeroed memory)


            //This part should ensure that the next few indexes (based on the size of the datatype are free before allocating)
            //E.g if trying to allocate an int, make sure the next 1 space is also zeroed, if not move on

            //Arrays are essentially the same but the space they are trying to allocate is variable
        
        }
    }

    return false;
}



/*
 * Function: check_ram
 * -------------------
 * Searches the RAMArray for a given token and returns the index if found. This function helps
 * determine whether a specific token is already stored in RAM, which is essential for managing
 * memory allocation and avoiding duplicates.
 *
 * Parameters:
 *   input - the token to check in RAM
 *
 * Returns:
 *   The index of the token in RAM if found,
 *   -1 otherwise.
 */
size_t check_ram(Token input) {
    //Check RAM if a variable is stored there, return address
    for(int i = 0; i < REGSize; i++) {


        if(RAMArray[i].arraySize != 0) { //Array detected - must skip following elements after check

            if(input.TokenContent.variableID == RAMArray[i].TokenContent.variableID) { //Same check as below
                return i; 
            }

            i+= RAMArray[i].arraySize; //Assuming that array bounds have already been checked (wont go outside of RAM)

        
        } else if(input.TokenContent.variableID == RAMArray[i].TokenContent.variableID) {
            //Registers/RAM should only contain variables - therefore this is ok
            return i; //Return RAM number
            
        }
    }

    return -1; //Return max size_t
}



/*
 * Function: remove_ram
 * --------------------
 * Frees up space in RAMArray that is occupied by a given token. This function is used to manage
 * memory by clearing space when it is no longer needed. If the token represents an array, it clears
 * the space occupied by the entire array.
 *
 * Parameters:
 *   input - the token to remove from RAM
 *
 * Returns:
 *   true if the token was successfully removed,
 *   false if the token was not found in RAM.
 */
bool remove_ram(Token input) { //Free some space in RAM
    //Frees a variable/array
    //First element in array contains array token which specifies the array size - this is how compiler knows how much to free
    //Similar to how free works

    size_t RAMIndex = check_ram(input);


    if(RAMIndex == (size_t)(-1)) { //Variable not in RAM
        return false;
    } else if(input.arraySize == 0) { //Not array
        memset(&RAMArray[RAMIndex], 0, sizeof(Token)); //Set memory index back to zero
    } else { //Array - should zero out all bytes associated with array so compiler knows its all free
        memset(&RAMArray[RAMIndex], 0, sizeof(Token) * (input.arraySize)); //Set memory index back to zero
    }

    return true;
}


/*
 * Function: push_register
 * -----------------------
 * Pushes a token into the least used register based on the usage statistics in REGCallArray.
 * This function implements a least-used replacement policy to manage the limited space in registers
 * efficiently. If the replaced register's token is not in RAM, it gets saved to RAM.
 *
 * Parameters:
 *   input - the token to push into a register
 *
 * Returns:
 *   true if the token was successfully pushed into a register,
 *   false if an error occurred (e.g., failed to save to RAM).
 */
bool push_register(Token input) { //Push this into a register, push out last used register

    size_t currentMin = 0;
    size_t currentMinIndex = 0;


    //See which register has been used the least, replace that register with a new value
    for(int i = 0; i < REGSize; i++) {

        if(currentMin > REGCallArray[i]) {
            currentMin = REGCallArray[i];
            currentMinIndex = i;
        }

    }
    Token lastToken = REGArray[currentMinIndex]; //Replace this index
    REGCallArray[currentMinIndex] = 0; //Set the index to zero


    //Check if token should be disguarded
    //Disguard if already in RAM, if not then save to RAM

    if(check_ram(lastToken) == (size_t)(-1)) {
        reserve_ram(lastToken, 0); //Save last token
    }

    return true;
}


/*
 * Function: check_register
 * ------------------------
 * Checks whether a specific token is stored in any of the registers and returns the register index.
 * Additionally, this function increments the access count for the register in which the token is found,
 * which is used for managing the replacement policy.
 *
 * Parameters:
 *   input - the token to check in the registers
 *
 * Returns:
 *   The index of the register containing the token if found,
 *   -1 otherwise.
 */
size_t check_register(Token input) {
    //Check register if a variable/immediate is stored there
    for(int i = 0; i < REGSize; i++) {

        //Registers/RAM should only contain variables - therefore this is ok
        if(input.TokenContent.variableID == REGArray[i].TokenContent.variableID) {
            
            REGCallArray[i]++; //Increment times called for this register
            return i; //Return register number
            
        }
    }

    return -1; //Return max size_t
}













