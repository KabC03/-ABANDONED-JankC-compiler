#include "intepret_IR.h"


typedef struct VirtualMachine {

    //Note void pointers used - this is because memory can hold any datatype
    void *registerArray;
    void *ramArray;



    size_t programCounter;

} VirtualMachine;










































