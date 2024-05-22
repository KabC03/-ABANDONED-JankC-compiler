#include "intepret_IR.h"


#define EXPANSIONSIZE 5
#define INT_TYPE int
#define FLOAT_TYPE float

typedef union DataTypes {

    INT_TYPE intVal;
    FLOAT_TYPE floatVal;

} DataTypes;
typedef struct {
    size_t instructionsPerSecond;  ///< The number of instructions the VM can execute per second.
    DataTypes *registerArray;      ///< Pointer to the array of registers.
    size_t numRegisters;           ///< Number of registers in the register array.

    DataTypes *ramArray;                ///< Pointer to the array representing the VM's RAM.
    size_t RAMsize;                ///< Size of the RAM array (NUMBER OF BYTES).
    
    size_t programCounter;         ///< Index of the current instruction in the instruction set (COUNT BITS NOT BYTES).
} VirtualMachine;







typedef enum VALID_INSTRUCTIONS {
    INVALID,  ///< Interpreter use only - not part of instruction set
    ADD,      ///< Add instruction
    SUB,      ///< Subtract instruction
    MUL,      ///< Multiply instruction
    DIV,      ///< Divide instruction
    STR,      ///< Store instruction
    LOD,      ///< Load instruction
    GRT,      ///< Greater than instruction
    GRE,      ///< Greater than or equal instruction
    LTE,      ///< Less than or equal instruction
    LES,      ///< Less than instruction
    EQU,      ///< Equal instruction
    NEQ,      ///< Not equal instruction
    JMP,      ///< Jump instruction
    JAL,      ///< Jump and link instruction
    JRT,      ///< Jump return instruction
    NOP       ///< No operation instruction
} VALID_INSTRUCTIONS;



// Only ONE VM exists - allow for better encapsulation
VirtualMachine VM;



/**
 * @brief Initialize the virtual machine with the specified RAM size, number of registers, and instructions per second.
 *
 * This function allocates memory for the register array and RAM array, and sets the program counter to 0.
 *
 * @param RAMsize Size of the RAM array to allocate.
 * @param numRegisters Number of registers to allocate in the register array.
 * @param instructionsPerSecond Number of instructions the VM can execute per second.
 * @return true if initialization is successful, false otherwise.
 */
bool initialise_virtual_machine(size_t RAMsize, size_t numRegisters, size_t instructionsPerSecond) {

    VM.numRegisters = numRegisters;
    VM.RAMsize = RAMsize;
    VM.programCounter = 0;


    if(instructionsPerSecond == 0) {
        return false;
    }
    VM.instructionsPerSecond = instructionsPerSecond; //Clockspeed basically

    VM.registerArray = (DataTypes*)malloc(numRegisters * sizeof(DataTypes)); //Store space for a full word
    VM.ramArray = (DataTypes*)malloc(RAMsize * sizeof(DataTypes)); //Store space for a full word - yes this wastes space

    if(VM.registerArray == NULL || VM.ramArray == NULL) {
        if(VM.ramArray == NULL) {
            free(VM.registerArray);
        } else if(VM.registerArray == NULL){
            free(VM.ramArray);
        } else {
            //Should never happen but left here for readability
        }
    }


    return true;
}


/**
 * Store data in a register or RAM.
 *
 * @param index The index at which to store data.
 * @param newData The data to store.
 * @param datatype 'i' for int and 'f' for float.
 * @param destination 'R' for register and 'r' for RAM.
 * @return The original data on success, or zero-initialized data on failure.
 */
DataTypes store_data(size_t index, DataTypes newData, char datatype, char destination) {

    DataTypes result;
    result.intVal = 0;

    DataTypes failureReturn;
    failureReturn.intVal = -1;

    if(VM.registerArray == NULL || VM.ramArray == NULL) return failureReturn;



    else if(destination == 'R') { //Register
        if(index >= VM.numRegisters) {
            return failureReturn; //Register does not exist
        } else {

            if(datatype == 'i') {
                (VM.registerArray[index]).intVal = newData.intVal;
            } else if(datatype == 'f') {
                (VM.registerArray[index]).floatVal = newData.floatVal;
            } else {
                return failureReturn;
            }

        }
    } else if(destination == 'r') { //RAM

        if(index >= VM.RAMsize) {
            return failureReturn; //Segfault - invalid memory
        } else {

            if(datatype == 'i') {
                (VM.ramArray[index]).intVal = newData.intVal;
            } else if(datatype == 'f') {
                (VM.ramArray[index]).floatVal = newData.floatVal;
            } else {
                return failureReturn;
            }

        }
    } else return failureReturn;


    return result;
}




/**
 * Store data in a register or RAM.
 *
 * @param index The index at which to store data.
 * @param newData The data to store.
 * @param datatype 'i' for int and 'f' for float.
 * @param destination 'R' for register and 'r' for RAM.
 * @return The original data on success, or zero-initialized data on failure.
 */
DataTypes read_data(size_t index, char datatype, char destination) {

    DataTypes result;
    result.intVal = 0;

    DataTypes failureReturn;
    failureReturn.intVal = -1;

    if(VM.registerArray == NULL || VM.ramArray == NULL) return failureReturn;



    else if(destination == 'R') { //Register
        if(index >= VM.numRegisters) {
            return failureReturn; //Register does not exist
        } else {

            if(datatype == 'i') {
                result.intVal = (VM.registerArray[index]).intVal; 
            } else if(datatype == 'f') {
                result.floatVal = (VM.registerArray[index]).floatVal; 
            } else {
                return failureReturn;
            }
        }
    } else if(destination == 'r') { //RAM

        if(index >= VM.RAMsize) {
            return failureReturn; //RAM does not exist - segfault
        } else {

            if(datatype == 'i') {
                result.intVal = (VM.ramArray[index]).intVal; 
            } else if(datatype == 'f') {
                result.floatVal = (VM.ramArray[index]).floatVal; 
            } else {
                return failureReturn;
            }
        }

    } else return failureReturn;


    return result;
}









/**
 * @brief Run the virtual machine using the instructions from the specified IR code file.
 *
 * This function opens the specified IR code file, reads and tokenizes instructions, and executes them accordingly.
 * If an error occurs during file opening, tokenization, or execution, it prints an error message and returns false.
 *
 * @param IRCodePath Path to the IR code file.
 * @return true if the VM runs successfully, false otherwise.
 */
bool run_virtual_machine(char *IRCodePath) { //NOTE - MAKE ERROR CODES BETTER - USE AN ENUM AS PLANNED IN OTHER FILES TO INDICATE ERROR CODE

    FILE *inputFile = fopen(IRCodePath, "r");
    if(inputFile == NULL) {
        printf("[Virtual Machine] Failed to open '%s'\n",inputFile);
        return false;
    }

    char *buffer[100]; //TEMPORARY - USE DYNAMIC MEMORY LATER
    bool justWhitespace = true;

    while(fgets(buffer, sizeof(buffer), inputFile) != EOF) {

        for(int i = 0; i < strlen(buffer) + 1; i++) {
            if(buffer[i] != '\n' || buffer[i] != ' '){
                justWhitespace = false;
            }
        }
        justWhitespace = true;




        if(justWhitespace == false) {
            char *instructionPtr = strtok(buffer, "|||");
            char *arg1Ptr = strtok(NULL, "|||");
            char *arg2Ptr = strtok(NULL, "|||");
            char *argc3Ptr = strtok(NULL, "|||");

            if(instructionPtr == NULL || arg1Ptr == NULL || arg2Ptr == NULL || argc3Ptr == NULL) {
                printf("[Virtual Machine] Failed to tokenise '%s'\n",buffer);
                return false;
            }



            
            if (strcmp(instructionPtr, "ADD") == 0) {
                
                //Convert all args to long long ints, do calculation then place in register
                //Check arg1, 2 and 3 are both numbers
                //reg[arg1Ptr] = reg[arg2Ptr] + reg[arg13Ptr]
                //CHECK REGISTER BOUNDS BEFORE INDEXING - THROW ERROR (INVALID REGISTER) IF MUST


            } else if (strcmp(instructionPtr, "SUB") == 0) {
                // Body
            } else if (strcmp(instructionPtr, "MUL") == 0) {
                // Body
            } else if (strcmp(instructionPtr, "DIV") == 0) {
                // Body


            } else if (strcmp(instructionPtr, "STR") == 0) { // Takes address and register to store, no label

                //Check arg3 is just '[]'
                //Convert all args to long long ints, do calculation then place in register
                //Check arg1, 2 and 3 are both numbers
                //RAM[arg1] = regarray[arg2]
                //CHECK REGISTER BOUNDS BEFORE INDEXING - THROW ERROR (SIGSEV) IF MUST
            } else if (strcmp(instructionPtr, "LOD") == 0) {
                // Body
            } else if (strcmp(instructionPtr, "GRT") == 0) {
                //Basically do the same, but check arg3 has no symbols (just letters/numbers - also first character shouldnt ne a number)
                //If label is not known (not in list of known labels - throw syntax error)
                //If known do comparison then jump
            } else if (strcmp(instructionPtr, "GRE") == 0) {
                // Body
            } else if (strcmp(instructionPtr, "LTE") == 0) {
                // Body
            } else if (strcmp(instructionPtr, "LES") == 0) {
                // Body
            } else if (strcmp(instructionPtr, "EQU") == 0) {
                // Body
            } else if (strcmp(instructionPtr, "NEQ") == 0) {
                // Body


            } else if (strcmp(instructionPtr, "JMP") == 0) {
                //Same as comparison statements above with the jump process
            } else if (strcmp(instructionPtr, "JAL") == 0) {
                //Push the program counter on the stack (current address) then jump to procedure
                //Should already know function labels because they should be declared before they are called
                //Check bounds to avoid stack overflow
            } else if (strcmp(instructionPtr, "JRT") == 0) {
                //Jump to whatever is on the stack. Check RAM bounds to avoid underflow
            } else if (strcmp(instructionPtr, "NOP") == 0) {
                //Do nothing but increase program counter
            } else {
                printf("[Virtual Machine] Unexpected '%s'\n",instructionPtr);
                return false;
            }









            sleep(1/(VM.instructionsPerSecond)); //Clockspeed simulation
        }
    }






    if(buffer != NULL) free(buffer);
    if(fclose(inputFile) != 0) return false;
    return true;
}
