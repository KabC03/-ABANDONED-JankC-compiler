/*
 * Map
 * 
 * Description:
 * This module provides functionality for a dynamic map data structure, which is used to store variables as key-value pairs.
 * The map dynamically adjusts its size as needed to accommodate new elements and manages memory efficiently during its operations.
 * 
 * Data Structure:
 * The map is implemented as an array of MapNode structures, where each MapNode contains a key-value pair. The array can grow dynamically
 * as new items are added. When items are removed, their slots are marked as empty by setting their keys to 0, but the memory is not 
 * immediately reclaimed; these slots are not reused.
 * 
 * Example:
 * | KEY | VALUE |
 * ---------------
 * |  1  | 'var1'| 
 * |  2  | 'var2'|  
 * |  3  | 'var3'| 
 * 
 * Key Features and Behaviors:
 * - **Dynamic Size Adjustment**: The initial size of the map and its expansion behavior are configurable. When the map reaches its 
 *   capacity, it expands by a predefined amount to accommodate additional items.
 * - **Non-reusing of Deleted Entries**: When items are removed, their keys are set to 0, which marks the slot as empty. These 'empty' 
 *   slots are not reused, and the item's memory (specifically the value) is freed, but the slot remains part of the array until the map 
 *   itself is destroyed.
 * - **Memory Management**: Memory for values is dynamically allocated and should be freed when no longer needed. The entire map and 
 *   its contents are only completely freed when the `destroy_map` function is called, which cleans up all allocated memory associated 
 *   with the map.
 * 
 * Usage:
 * - **Creating a Map**: Use `create_map(size_t initialSize, size_t expansionParameter)` to initialize a map with a set initial capacity 
 *   and expansion behavior.
 * - **Adding Items**: Use `append_map(Map* map, size_t key, char* value)` to add new key-value pairs to the map. If the map reaches its 
 *   capacity, it will expand according to the specified expansion parameter.
 * - **Removing Items**: Use `remove_item_map(Map* map, size_t key)` to remove an item by key. The key is set to 0 to indicate the slot is 
 *   now empty, but the slot itself is not removed from the array.
 * - **Accessing Items**: Use `return_value_map(Map* map, size_t key)` to retrieve the value for a given key. If the key has been set to 0, 
 *   the function returns NULL, indicating that the variable was previously removed.
 * - **Destroying the Map**: Use `destroy_map(Map* map)` to free all memory associated with the map, including all keys and values stored 
 *   within. This should be called to prevent memory leaks when the map is no longer needed.
 * - **Printing Map Contents**: Use `print_map(Map* map)` to display all current key-value pairs in the map.
 */



#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct MapNode {

    size_t key;   //'1'
    char *value;  //'var1'
} MapNode;

typedef struct Map {

    size_t maxSize;                //Max size of map
    size_t topIndex;               //Index of last element in map
    size_t expansionParameter;     //How much map grows every time it is expanded

    MapNode *mapPtr;               //Points to array of map nodes

} Map;


void print_map(Map *currentMap);
Map *create_map(size_t mapSize, size_t expansionParameter);
bool append_map(Map *currentMap, size_t newKey, char* newValue);
char *return_value_map(Map *currentMap, size_t currentKey);
bool remove_item_map(Map *currentMap, size_t currentKey);
bool destroy_map(Map *currentMap);


#endif
