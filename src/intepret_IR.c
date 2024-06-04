#include "intepret_IR.h"


#define EXPANSIONSIZE 5
#define INT_TYPE int
#define FLOAT_TYPE float

typedef union DataTypes {

    INT_TYPE intVal;
    FLOAT_TYPE floatVal;

} DataTypes;
typedef struct VirtualMachine{
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








