#include "intepret_IR.h"


#define EXPANSIONSIZE 5
#define INT_TYPE int
#define FLOAT_TYPE float


#define OPCODE_SIZE 7

typedef union DataTypes {

    INT_TYPE intVal;
    FLOAT_TYPE floatVal;

} DataTypes;
typedef struct VirtualMachine {
    size_t instructionsPerSecond;  ///< The number of instructions the VM can execute per second.
    DataTypes *registerArray;      ///< Pointer to the array of registers.
    size_t numRegisters;           ///< Number of registers in the register array.

    DataTypes *ramArray;                ///< Pointer to the array representing the VM's RAM.
    size_t RAMsize;                ///< Size of the RAM array (NUMBER OF BYTES).
    
    size_t programCounter;         ///< Index of the current instruction in the instruction set (COUNT BITS NOT BYTES).

} VirtualMachine;


typedef struct Instruction {

    char opcode[OPCODE_SIZE];
    size_t ARG1; //Register
    size_t ARG2; //Register

    union ARG3{
        size_t reg; //Register, Label or Immediate
        size_t label;
        double immediate;
    } ARG3;


} Instruction;





typedef enum VALID_INSTRUCTIONS {
    INVALID,  ///< Interpreter use only - not part of instruction set
    ADD,      ///< Add instruction
    SUB,      ///< Subtract instruction
    MUL,      ///< Multiply instruction
    DIV,      ///< Divide instruction
    MOD,      ///< Mod instruction
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
 * @brief Print the properties of the virtual machine.
 *
 * This function prints the current properties of the virtual machine, including instructions per second,
 * number of registers, and RAM size.
 */
void print_VM_properties(void) {
    //Print the VM info

    printf("=======Virtual machine properties=======\n");
    printf("Instructions per second:    %zu\n", VM.instructionsPerSecond);
    printf("Number of registers:        %zu\n", VM.numRegisters);
    printf("Ram size:                   %zu\n",VM.RAMsize);
    printf("========================================\n");

    return;
}


/**
 * @brief Run the virtual machine with the given intermediate representation (IR) file.
 *
 * This function reads the IR output file line by line and interprets each line on the VM.
 * It performs a pass on the file first to put it into a token array, where each index in the token array
 * acts as an index into the instruction memory. This approach allows labels to be defined in a map
 * (Label name -> jump address). The debug flag can be used to print what the VM is doing.
 * If an error occurs, such as an out-of-bounds access in the VM memory, the corresponding interrupt flag
 * is set and the function returns false. If debug mode is enabled, error messages are printed.
 *
 * @param fileName The name of the IR file to execute.
 * @param debug If true, prints debugging information.
 * @return true if the file was successfully opened and processed, false otherwise.
 */
bool run_VM(char *fileName, bool debug) {


    //Basically reads the IR output file line by line and inteprets (line by line) on the VM
    //Does a PASS on the file FIRST - put it into a token array
    //Each index in the token array is like an index into the instruction memory
    //This approach also allows lables to be defined in a map (Label name -> jump Address)

    //Returns false if file cant be opened
    //If something goes wrong in the VM itself (e.g OOB access in the VM memory) set the corrosponding interupt flag
    //Continue execution then return false - if debug mode on then also print that a error happened
    
    //In instruction IR file all have the form OPERATION|||argument1|||argument2|||argument3|||
    //Irregardless of r i or j instruction
    //Use strtok to break it up



    //Debug is used to print what the VM is doing
    //input filename for source file
    if(fileName == NULL) {
        return false;
    }
    FILE *fptr = fopen(fileName, "r");
    if(fptr == NULL) {

        if(debug == true) {
            printf("[VM - DEBUG] FAILED to open: %s\n",fileName);
        }

        return false;
    }

    if(debug == true) {
        printf("[VM - DEBUG] Opened: %s\n",fileName);
    }
    




    //Tokenisation
    //Each line goes into the instruction memory array (which is a dynamic array)











    return true;
}


















