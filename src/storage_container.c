#include "storage_controller.h"




// Global arrays for RAM and register storage
size_t *valueRAM = NULL;
char *valueTypeRAM = NULL;

size_t *valueREG = NULL;
char *valueTypeREG = NULL;


/*
 * Function: set_RAM
 * -----------------
 * Initializes the storage arrays for RAM with the specified size. This function allocates memory for keys, values,
 * and their types. It is intended to be called once during the initialization phase of your application.
 *
 * RAMSize: The size of the RAM storage arrays to be allocated.
 *
 * Returns: true if the allocation was successful, false otherwise.
 */
bool set_RAM(size_t RAMSize) {
    
    valueRAM = calloc(RAMSize, sizeof(size_t));
    valueTypeRAM = calloc(RAMSize, sizeof(char));

    if(valueRAM == NULL || valueTypeRAM == NULL) {
        return false;
    }

    return true;
}

/*
 * Function: set_registers
 * -----------------------
 * Initializes the storage arrays for registers with the specified size. This function allocates memory for keys, values,
 * and their types, similar to set_RAM but for register storage.
 *
 * RegisterSize: The size of the register storage arrays to be allocated.
 *
 * Returns: true if the allocation was successful, false otherwise.
 */
bool set_registers(size_t RegisterSize) {
    
    valueREG = calloc(RegisterSize, sizeof(size_t));
    valueTypeREG = calloc(RegisterSize, sizeof(char));

    if(valueREG == NULL || valueTypeREG == NULL) {
        return false;
    }

    return true;
}




/*
 * Function: store_RAM
 * -------------------
 * Stores a variable or immediate value in RAM based on the provided type ('v' for variable, 'i' for immediate).
 * The function assigns the value and type to the storage arrays at the index specified by the ID.
 *
 * ID: The index at which the value and type should be stored.
 * value: The value to store (could be an integer, float, etc., depending on RegisterTypes definition).
 * type: The type of the value to store ('v' for variable, 'i' for immediate).
 *
 * Returns: true if the operation is successful, false otherwise.
 */
bool store_RAM(size_t ID, RegisterTypes value, char type) {

    if(type == 'v') {

    } else if(type == 'i') {

    } else {
        return false;
    }
    return true;
}





/*
 * Function: store_register
 * ------------------------
 * Stores a variable or immediate value in a register based on the provided type.
 * Similar to store_RAM but targets the register storage arrays.
 *
 * ID: The register index at which to store the value.
 * value: The value to store.
 * type: The type of the value to store ('v' for variable, 'i' for immediate).
 *
 * Returns: true if the operation is successful, false otherwise.
 */
bool store_register(size_t ID, RegisterTypes value, char type) {



}



/*
 * Function: check_RAM
 * -------------------
 * Checks for a variable's presence in RAM and returns its index.
 *
 * ID: The variable ID to check.
 *
 * Returns: The index of the variable if found, 0 if not found.
 */
size_t check_RAM(size_t ID) {


    return 0;
} 





/*
 * Function: check_register
 * ------------------------
 * Checks for a variable's presence in a register and returns the register number.
 *
 * ID: The variable ID to check.
 *
 * Returns: The register number if the variable is found, 0 if not found.
 */
size_t check_register(size_t ID) {

    return 0;
}
