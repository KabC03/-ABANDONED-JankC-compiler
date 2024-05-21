#include "intepret_IR.h"


#define BYTE 1


bool initialise_virtual_machine(VirtualMachine *VMout, size_t RAMsize, size_t numRegisters) {

    VMout->numRegisters = numRegisters;
    VMout->RAMsize = RAMsize;
    VMout->programCounter = 0;

    VMout->registerArray = (void*)malloc(BYTE * numRegisters); 
    VMout->ramArray = (void*)malloc(BYTE * RAMsize);

    if(VMout->registerArray == NULL || VMout->ramArray == NULL) {
        if(VMout->ramArray == NULL) {
            free(VMout->registerArray);
        } else if(VMout->registerArray == NULL){
            free(VMout->ramArray);
        } else {
            //Should never happen but left here for readability
        }
    }


    return true;
}








































