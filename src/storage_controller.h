/*
 * storage_controller.h
 *
 * Description:
 * This header file defines the interfaces for managing storage of variables and immediate values in both RAM and registers
 * within a compiler. It provides functionality to initialize, store, and clear data, as well as to search for data in
 * RAM and registers.
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
 *                             | storing a variable ('v') or an immediate ('i'). ('\0') is used to denote an empty space
 *
 *
 * Data Structures:
 * The module uses two global arrays for RAM and register storage, one for storing values and another for storing types.
 * These arrays are indexed where the index acts as a key and the corresponding entry in the arrays represents the stored
 * value and its type (either variable 'v' or immediate 'i').
 *
 * Functions:
 * - set_RAM: Initializes the RAM storage with specified size.
 * - set_registers: Initializes the register storage with specified size.
 * - store_variable: Stores a variable in either RAM or registers.
 * - clear_variable: Clears a variable from RAM or registers.
 * - store_immediate: Stores an immediate value in either RAM or registers.
 * - clear_immediate: Clears an immediate value from RAM or registers.
 * - search: Searches for a variable's ID and returns its location.
 * - search_immediate: Searches for an immediate value and returns its location.
 *
 * The types of data that can be stored are defined in a union, accommodating character, float, and integer types.
 */

#ifndef STORAGE_CONTROLLER_H
#define STORAGE_CONTROLLER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define the union type for handling different data types uniformly.
typedef union RegisterTypes {
    char c;
    float f;
    int i;
} RegisterTypes;

// Function prototypes
void print_RAM(void);
void print_registers(void);
bool set_RAM(size_t RAMSize);
bool set_registers(size_t RegisterSize);
bool store_variable(size_t ID, char location);
bool clear_variable(size_t ID, char location);
bool store_immediate(RegisterTypes value, char location, char type);
bool clear_immediate(RegisterTypes value, char location, char type);
size_t search_variable(size_t ID, char location);
size_t search_immediate(RegisterTypes value, char location, char type);

#endif // STORAGE_CONTROLLER_H
