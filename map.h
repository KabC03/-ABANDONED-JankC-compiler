/*
 * Map
 * 
 * Description:
 * This module provides functionality for a dynamic map data structure, which is used to store variables as key-value pairs.
 * It dynamically adjusts its size as needed to accommodate new elements.
 * 
 * Data Structure:
 * The map is implemented as an array of MapNode structures, where each MapNode contains a key-value pair.
 * 
 * Example:
 * | KEY | VALUE |
 * ---------------
 * |  1  | 'var1'| 
 * |  2  | 'var2'|  
 * |  3  | 'var3'| 
 * 
 * Usage:
 * - To create a map, use create_map() function, specifying the initial size and expansion parameter.
 * - To append a new key-value pair to the map, use append_map() function.
 * - To print the contents of the map, use print_map() function.
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




#endif
