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
 *    Array for Storage:       | Index:  0   1   2   3
 *                             | Value: [10, 20, 30, 40]
 *                             | This array stores values directly at each index, which can represent either a 
 *                             | variable's value or an immediate value.
 *
 *    Type Array (Variable ID or Immediate):
 *                             | Index:  0   1   2   3
 *                             | Type : ['v', 'i', 'v', 'i']
 *                             | This array indicates whether the corresponding index in the storage array is 
 *                             | storing a variable ('v') or an immediate ('i'). ('e') is used to denote an empty space
 *
 * Functions:
 * - set_RAM and set_registers: Initialize memory for RAM and registers respectively.
 * - store_RAM and store_register: Stores data in RAM or registers, handling either a variable or an immediate 
 *   based on the type parameter.
 * - check_RAM and check_register: Check for a data's presence in RAM or registers and return its location.
 */

#ifndef STORAGE_CONTROLLER_H
#define STORAGE_CONTROLLER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define the union type for handling different data types in a uniform way
typedef union RegisterTypes {
    char c;
    float f;
    int i;
} RegisterTypes;

// Function to initialize RAM storage
bool set_RAM(size_t RAMSize);

// Function to initialize register storage
bool set_registers(size_t RegisterSize);

// Storage management functions for RAM
bool store_RAM(size_t ID, RegisterTypes value, char type); // 'v' for variable, 'i' for immediate

// Storage management functions for registers
bool store_register(size_t ID, RegisterTypes value, char type); // 'v' for variable, 'i' for immediate

// Check functions for RAM and registers
size_t check_RAM(size_t ID); // Return index of item (0 if not found)
size_t check_register(size_t ID); // Return index of item (0 if not found)

#endif // STORAGE_CONTROLLER_H
