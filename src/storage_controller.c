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



bool initialise_memory(size_t setRegSize, size_t setRamSize) { 

    REGSize = setRegSize;
    RAMSize = setRamSize;

    //Important - bytes are zeroed - this is how compiler knows free space is available
    REGArray = (Token*)calloc(setRegSize, sizeof(Token));
    REGCallArray = (Token*)calloc(setRegSize, sizeof(Token));

    RAMArray = (Token*)calloc(setRamSize, sizeof(size_t));

    if(REGArray == NULL || REGCallArray == NULL || RAMArray == NULL) return false;

    return true;
}




bool reserve_ram(Token input, size_t size) { //Reserve some space in RAM - basic malloc
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



//Check RAM if a variable/immediate is stored there, return address
size_t check_ram(Token input) {

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
 * ----------------------
 *
 * 
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

    if(check_RAM(lastToken) == (size_t)(-1)) {
        reserve_RAM(lastToken, 0); //Save last token
    }

    return true;
}


//Check register if a variable/immediate is stored there
size_t check_register(Token input) {

    for(int i = 0; i < REGSize; i++) {

        //Registers/RAM should only contain variables - therefore this is ok
        if(input.TokenContent.variableID == REGArray[i].TokenContent.variableID) {
            
            REGCallArray[i]++; //Increment times called for this register
            return i; //Return register number
            
        }
    }

    return -1; //Return max size_t
}













