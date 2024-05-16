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


/*
 * Function: print_map
 * --------------------
 * Print the contents of the given map.
 *
 * currentMap: Pointer to the map to be printed.
 */
void print_map(Map *currentMap) {

    if(currentMap == NULL) {
        printf("Empty map\n");
        return;
    }






    return;
}


/*
 * Function: create_map
 * ---------------------
 * Create a new map with the specified initial size and expansion parameter.
 *
 * mapSize: Initial size of the map.
 * expansionParameter: Amount by which the map should grow when expanded.
 *
 * Returns: Pointer to the newly created map.
 */
Map *create_map(size_t mapSize, size_t expansionParameter) {

    Map* result = (Map*)malloc(sizeof(Map));
    result->mapPtr = (MapNode*)malloc(mapSize * sizeof(MapNode));


    result->maxSize = mapSize;
    result->topIndex = 0;
    result->expansionParameter = expansionParameter;

    return result;
}


/*
 * Function: append_map
 * ---------------------
 * Append a new key-value pair to the given map.
 *
 * currentMap: Pointer to the map to which the pair should be appended.
 * newKey: Key of the new element to be added.
 * newValue: Value associated with the new key.
 *
 * Returns: true if the operation is successful, false otherwise.
 */
bool append_map(Map *currentMap, size_t newKey, char*newValue) {

    
    if(currentMap == NULL) return true;

    if(currentMap->maxSize == currentMap->topIndex) {
        //Map at max capacity, must expand

        size_t prevSize = currentMap->maxSize;
        currentMap->mapPtr = (MapNode*)realloc(currentMap->mapPtr, currentMap->maxSize + currentMap->expansionParameter);
        currentMap->maxSize = prevSize + currentMap->expansionParameter; 

    }

    if(currentMap->mapPtr == NULL) return false;


    //Add new values and increment top
    (currentMap->mapPtr)[currentMap->topIndex].key = newKey;
    (currentMap->mapPtr)[currentMap->topIndex].value = newValue; 

    currentMap->topIndex++;

    return true;
}





#endif
