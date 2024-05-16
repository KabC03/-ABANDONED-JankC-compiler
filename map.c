#include "map.h"


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

    printf("| KEY | VALUE |\n---------------\n");
    for(int i = 0; i < currentMap->topIndex; i++) {
        printf("| %zu | %s |\n", (currentMap->mapPtr)[i].key, (currentMap->mapPtr)[i].value);

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
        currentMap->mapPtr = (MapNode*)
        realloc(currentMap->mapPtr, (currentMap->maxSize + currentMap->expansionParameter) * sizeof(MapNode));


        currentMap->maxSize = prevSize + currentMap->expansionParameter; 

    }

    if(currentMap->mapPtr == NULL) return false;


    //Add new values and increment top
    (currentMap->mapPtr)[currentMap->topIndex].key = newKey;

    (currentMap->mapPtr)[currentMap->topIndex].value = (char*)malloc((strlen(newValue) + 1) * sizeof(char));
    strncpy((currentMap->mapPtr)[currentMap->topIndex].value, newValue, strlen(newValue) + 1);

    currentMap->topIndex++;

    return true;
}









