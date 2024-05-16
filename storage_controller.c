/*
 * storage_controller.h
 *
 * Description:
 * Manages the storage of variables and immediate values in both RAM and registers within a compiler. This module
 * interfaces with the system's memory and registers to efficiently handle allocation, retrieval, and updates of
 * data storage.
 *
 * Data Structure:
 * Uses an array-based approach for managing storage where the array index acts as the key and the array value
 * at that index represents the stored value. A separate type array marks entries as 'v' (variable) or 'i' (immediate),
 * indicating the nature of the data stored at each index.
 *
 * Example Data Representation:
 * Array for Storage:
 *    Index:  0   1   2   3
 *    Value: [10, 20, 30, 40]
 *    This array stores values directly at each index, which can represent either a variable's value or an immediate value.
 *
 * Type Array (Variable ID or Immediate):
 *    Index:  0   1   2   3
 *    Type : ['v', 'i', 'v', 'i']
 *    This array indicates whether the corresponding index in the storage array is storing a variable ('v') or an immediate ('i').
 *
 * Functions:
 * - store_RAM: Stores data in RAM, handling either a variable or an immediate based on the type parameter.
 * - store_register: Stores data in a register, handling either a variable or an immediate based on the type parameter.
 * - check_RAM: Checks for a data's presence in RAM and returns its location.
 * - check_register: Checks for a data's presence in a register and returns the register number.
 */

#ifndef STORAGECONTROLLER_H
#define STORAGECONTROLLER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "map.h"


typedef union RegisterTypes { //Pass this to register function to allow char, float or int in (rather than having 3 function)
    char c;
    float f;
    int i;
} RegisterTypes;



// Storage management functions for RAM and registers
bool store_RAM(size_t id, RegisterTypes value, char type); // 'v' for variable, 'i' for immediate
bool store_register(size_t id, RegisterTypes value, char type); // 'v' for variable, 'i' for immediate

// Check functions for RAM and registers
size_t check_RAM(size_t id); // Return index of item (0 if not found)
size_t check_register(size_t id); // Return index of item (0 if not found) (basically the register number)

#endif // STORAGE_CONTROLLER_H
