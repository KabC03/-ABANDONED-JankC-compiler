/*
 * storage_controller.h
 *
 * Description:
 * This module provides core functionalities for memory management within a simulated system, handling both register and RAM storage.
 * It manages a fixed array of registers and a simulated RAM space, designed to optimize memory operations typically required by compilers
 * and other systems that need to manage variable storage efficiently. This includes initializing, reserving, checking, and removing memory,
 * as well as managing register usage based on frequency of access.
 *
 * Data Structure:
 * - REGArray: A statically sized array representing registers. Each element is of type Token and is used to store variable data.
 * - RAMArray: A statically sized array simulating RAM, used for additional storage when register space is insufficient.
 * - REGCallArray: An array tracking the number of accesses for each register to implement a least-used replacement strategy.
 *
 * Key Features and Behaviors:
 * - **Memory Initialization and Cleanup**: Functions to initialize and destroy memory resources, ensuring proper setup and cleanup.
 * - **Memory Reservation**: Dynamically manages memory allocation within the RAMArray based on requested size and data type.
 * - **Memory Access and Management**: Provides functionality to check, push, and remove tokens from memory, optimizing register usage
 *   and managing RAM storage efficiently.
 * - **Least-Used Replacement Strategy**: Implements a policy for register replacement based on the least number of accesses, ensuring
 *   efficient use of limited register resources.
 *
 * Usage:
 * - **Initialize Memory**: Use `initialise_memory` to set up REGArray and RAMArray with specified sizes.
 * - **Reserve RAM**: Use `reserve_ram` to allocate memory in RAM for a token.
 * - **Remove from RAM**: Use `remove_ram` to free memory occupied by a token in RAM.
 * - **Check RAM**: Use `check_ram` to find if and where a token is stored in RAM.
 * - **Push Register**: Use `push_register` to insert a token into the register array based on the least-used strategy.
 * - **Check Register**: Use `check_register` to find if and where a token is stored in the registers and to increment access count.
 */



#ifndef STORAGE_CONTROLLER_H
#define STORAGE_CONTROLLER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "compiler_structs.h"

// Function prototypes for memory management
bool initialise_memory(size_t setRegSize, size_t setRamSize);
bool reserve_ram(Token input, size_t size);
bool remove_ram(Token input);
size_t check_ram(Token input);
bool push_register(Token input);
size_t check_register(Token input);

#endif // STORAGE_CONTROLLER_H
