#include "storage_controller.h"




// Global arrays for RAM and register storage
size_t *valueRAM = NULL;
char *valueTypeRAM = NULL;
size_t sizeRam = 0;

size_t *valueREG = NULL;
char *valueTypeREG = NULL;
size_t sizeReg = 0;


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
    sizeRam = RAMSize;
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
    sizeReg = RegisterSize;
    valueREG = calloc(RegisterSize, sizeof(size_t));
    valueTypeREG = calloc(RegisterSize, sizeof(char));

    if(valueREG == NULL || valueTypeREG == NULL) {
        return false;
    }

    return true;
}









/*
 * Function: store_variable
 * ------------------------
 * Stores a variable in the specified location (either RAM or registers). The function finds the first empty
 * position in the designated storage and stores the variable ID there, marking it as a variable.
 *
 * ID: The unique identifier of the variable to store.
 * location: The storage location character ('r' for register, 'R' for RAM).
 *
 * Returns: true if the variable is successfully stored, false if the specified location is invalid or storage fails.
 */
bool store_variable(size_t ID, char location) { //Store reg/ram

    if(location == 'r') { //Store in register

        for(int i = 0; i < sizeReg; i++) {
            if(valueTypeREG[i] == '\0') { //Empty position
                valueREG[i] = ID;
                valueTypeREG[i] = 'v';
                return true;
            }
        }

    } else if(location == 'R') { //Store in RAM
        for(int i = 0; i < sizeRam; i++) {

            if(valueTypeRAM[i] == '\0') { //Empty position
                valueRAM[i] = ID;
                valueTypeRAM[i] = 'v';
                return true;
            }
        }

    } else {
        return false;
    }

    return false;
}



/*
 * Function: clear_variable
 * ------------------------
 * Clears a variable from the specified storage location by resetting the type and value at the variable's stored index.
 *
 * ID: The unique identifier of the variable to clear.
 * location: The storage location character ('r' for register, 'R' for RAM).
 *
 * Returns: true if the variable is successfully cleared, false if the variable is not found or the location is invalid.
 */
bool clear_variable(size_t ID, char location) {  //Free reg/ram
  
    if(location == 'r') { //Store in register

        for(int i = 0; i < sizeReg; i++) {
            if(valueTypeREG[i] == 'v' && valueREG[i] == ID) { //Found index
                valueTypeREG[i] = '\0';
                valueREG[i] = 0;
                return true;
            }
        }

    } else if(location == 'R') { //Store in RAM
        for(int i = 0; i < sizeRam; i++) {

            if(valueTypeRAM[i] == 'v' && valueRAM[i] == ID) { //Empty position
                valueTypeRAM[i] = '\0';
                valueRAM[i] = 0;
                return true;
            }
        }

    } else {
        return false;
    }

    return false;
}



/*
 * Function: store_immediate
 * -------------------------
 * Stores an immediate value in the specified location (either RAM or registers). The function finds the first empty
 * position in the designated storage and stores the value there, marking it as an immediate.
 *
 * value: The value to store, which can be of type char, float, or int.
 * location: The storage location character ('r' for register, 'R' for RAM).
 * type: The type of the immediate ('c' for char, 'f' for float, 'i' for int).
 *
 * Returns: true if the immediate is successfully stored, false if the location or type is invalid or storage fails.
 */
bool store_immediate(RegisterTypes value, char location, char type) { //store reg/RAM

    if(type == 'c') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == '\0') { //Empty position
                    valueREG[i] = value.c;
                    valueTypeREG[i] = 'i';
                    return true;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == '\0') { //Empty position
                    valueRAM[i] = value.c;
                    valueTypeRAM[i] = 'i';
                    return true;
                }
            }

        } else {
            return false;
        }
    } else if(type == 'f') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == '\0') { //Empty position
                    valueREG[i] = value.f;
                    valueTypeREG[i] = 'i';
                    return true;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == '\0') { //Empty position
                    valueRAM[i] = value.f;
                    valueTypeRAM[i] = 'i';
                    return true;
                }
            }

        } else {
            return false;
        }
    } else if(type == 'i') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == '\0') { //Empty position
                    valueREG[i] = value.i;
                    valueTypeREG[i] = 'i';
                    return true;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == '\0') { //Empty position
                    valueRAM[i] = value.i;
                    valueTypeRAM[i] = 'i';
                    return true;
                }
            }

        } else {
            return false;
        }
    } else {
        return false;
    }


    return false;
}



/*
 * Function: clear_immediate
 * -------------------------
 * Clears an immediate value from the specified location by resetting the type and value at the immediate's stored index.
 *
 * value: The immediate value to clear.
 * location: The storage location character ('r' for register, 'R' for RAM).
 * type: The type of the immediate ('c' for char, 'f' for float, 'i' for int).
 *
 * Returns: true if the immediate is successfully cleared, false if it is not found or the location is invalid.
 */
bool clear_immediate(RegisterTypes value, char location, char type) { //Free reg/RAM

    if(type == 'c') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == 'v' && valueREG[i] == value.c) { //Found index
                    valueTypeREG[i] = '\0';
                    valueREG[i] = 0;
                    return true;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == 'v' && valueRAM[i] == value.c) { //Empty position
                    valueTypeRAM[i] = '\0';
                    valueRAM[i] = 0;
                    return true;
                }
            }

        } else {
            return false;
        }
    } else if(type == 'f') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == 'v' && valueREG[i] == value.f) { //Found index
                    valueTypeREG[i] = '\0';
                    valueREG[i] = 0;
                    return true;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == 'v' && valueRAM[i] == value.f) { //Empty position
                    valueTypeRAM[i] = '\0';
                    valueRAM[i] = 0;
                    return true;
                }
            }

        } else {
            return false;
        }
    } else if(type == 'i') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == 'v' && valueREG[i] == value.i) { //Found index
                    valueTypeREG[i] = '\0';
                    valueREG[i] = 0;
                    return true;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == 'v' && valueRAM[i] == value.i) { //Empty position
                    valueTypeRAM[i] = '\0';
                    valueRAM[i] = 0;
                    return true;
                }
            }

        } else {
            return false;
        }


    return false;
    }
}





/*
 * Function: search_variable
 * ----------------
 * Searches for a variable's ID in the specified storage location and returns the index where it is stored.
 *
 * ID: The unique identifier of the variable to find.
 * location: The storage location character ('r' for register, 'R' for RAM).
 *
 * Returns: The index of the variable if found, 0 if the variable is not found or the location is invalid.
 */
size_t search_variable(size_t ID, char location) {//Return register number containing item
  
    if(location == 'r') { //Store in register

        for(int i = 0; i < sizeReg; i++) {
            if(valueTypeREG[i] == 'v' && valueREG[i] == ID) { //Found index
                return i;
            }
        }

    } else if(location == 'R') { //Store in RAM
        for(int i = 0; i < sizeRam; i++) {

            if(valueTypeRAM[i] == 'v' && valueRAM[i] == ID) { //Empty position
                return i;
            }
        }

    } else {
        return 0;
    }

    return 0;
}



/*
 * Function: search_immediate
 * --------------------------
 * Searches for an immediate value in the specified location and returns the index where it is stored.
 *
 * value: The immediate value to find.
 * location: The storage location character ('r' for register, 'R' for RAM).
 * type: The type of the immediate ('c' for char, 'f' for float, 'i' for int).
 *
 * Returns: The index of the immediate if found, 0 if the immediate is not found or the location/type is invalid.
 */
size_t search_immediate(RegisterTypes value, char location, char type) { //Return register/RAM number containing item

    if(type == 'c') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == 'v' && valueREG[i] == value.c) { //Found index
                    return i;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == 'v' && valueRAM[i] == value.c) { //Empty position
                    return i;
                }
            }

        } else {
            return 0;
        }
    } else if(type == 'f') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == 'v' && valueREG[i] == value.f) { //Found index
                    return i;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == 'v' && valueRAM[i] == value.f) { //Empty position
                    return i;
                }
            }

        } else {
            return 0;
        }
    } else if(type == 'i') {
        if(location == 'r') { //Store in register

            for(int i = 0; i < sizeReg; i++) {
                if(valueTypeREG[i] == 'v' && valueREG[i] == value.i) { //Found index
                    return i;
                }
            }

        } else if(location == 'R') { //Store in RAM
            for(int i = 0; i < sizeRam; i++) {

                if(valueTypeRAM[i] == 'v' && valueRAM[i] == value.i) { //Empty position
                    return i;
                }
            }

        } else {
            return 0;
        }


    return 0;
    }
}






