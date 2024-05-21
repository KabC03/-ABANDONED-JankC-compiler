#include "intepret_IR.h"


#define BYTE 1




typedef struct {
    void *registerArray;
    size_t numRegisters;

    void *ramArray;
    size_t RAMsize;

    size_t programCounter; // Indexes BITS
} VirtualMachine;



//Only ONE VM exists - allow for better encapsulation
VirtualMachine VM;


bool initialise_virtual_machine(size_t RAMsize, size_t numRegisters) {

    VM.numRegisters = numRegisters;
    VM.RAMsize = RAMsize;
    VM.programCounter = 0;

    VM.registerArray = (void*)malloc(BYTE * numRegisters); 
    VM.ramArray = (void*)malloc(BYTE * RAMsize);

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







bool run_virtual_machine(void) {







    return true;
}





































