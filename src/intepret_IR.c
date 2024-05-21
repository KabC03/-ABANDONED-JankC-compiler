#include "intepret_IR.h"


#define EXPANSIONSIZE 5



typedef struct {

    size_t instructionsPerSecond;
    void *registerArray;
    size_t numRegisters;

    void *ramArray;
    size_t RAMsize;

    size_t programCounter; // Indexes BITS
} VirtualMachine;







typedef enum VALID_INSTRUCTIONS {

    INVALID, //Intepreter use only - not part of instruction set

    ADD,
    SUB,
    MUL,
    DIV,

    STR,
    LOD,

    GRT,
    GRE,
    LTE,
    LES,
    EQU,
    NEQ,
    JMP,
    
    JAL,
    JRT,

    NOP,

} VALID_INSTRUCTIONS;



//Only ONE VM exists - allow for better encapsulation
VirtualMachine VM;


bool initialise_virtual_machine(size_t RAMsize, size_t numRegisters, size_t instructionsPerSecond) {

    VM.numRegisters = numRegisters;
    VM.RAMsize = RAMsize;
    VM.programCounter = 0;


    if(instructionsPerSecond == 0) {
        return false;
    }
    VM.instructionsPerSecond = instructionsPerSecond; //Clockspeed basically

    VM.registerArray = (void*)malloc(numRegisters); 
    VM.ramArray = (void*)malloc(RAMsize);

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





































