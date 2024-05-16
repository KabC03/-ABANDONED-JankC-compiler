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

    
    if(currentMap == NULL) return false;

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

/*
 * Function: return_value
 * -----------------------
 * Retrieve the value associated with a given key in the map.
 *
 * currentMap: Pointer to the map from which the value is retrieved.
 * currentKey: The key for which the value is to be retrieved.
 *
 * Returns: Pointer to the value associated with the key if found, otherwise NULL.
 */
char *return_value(Map *currentMap, size_t currentKey) {

    char *result = NULL;
    if(currentMap == NULL) return NULL;
    else if(currentMap->mapPtr == NULL) return NULL;

    for(int i = 0; i < currentMap->topIndex; i++) {
        if((currentMap->mapPtr)[i].key == currentKey) {
            result = (currentMap->mapPtr)[i].value; //Return pointer to the item IN THE MAP ITSELF
            break;
        }
    }

    return result;
}


/*
 * Function: remove_item
 * ----------------------
 * Remove an item from the map by its key.
 *
 * currentMap: Pointer to the map from which the item is to be removed.
 * currentKey: The key of the item to be removed.
 *
 * Returns: true if the item was successfully removed, false otherwise.
 */
bool remove_item(Map *currentMap, size_t currentKey) {

    if(currentMap == NULL) return false;
    else if(currentMap->mapPtr == NULL) return false;

    for(int i = 0; i < currentMap->topIndex; i++) {
        if((currentMap->mapPtr)[i].key == currentKey) {
            //Found item, deallocate            

            free((currentMap->mapPtr)[i].value); //Free string value
            (currentMap->mapPtr)[i].key = 0; 
            //Set to 0 to indicate empty spot, keep in mind that in types.h "size_t variableID == 0" indicates for, if, while, etc
            //However, 0 here means empty place
        }
    }
    return true;
}

/*
 * Function: destroy_map
 * ----------------------
 * Frees all resources associated with the map, including all values stored in map nodes.
 *
 * currentMap: Pointer to the map to be destroyed.
 *
 * Returns: true if the map was successfully destroyed, false if the input was NULL.
 */
bool destroy_map(Map *currentMap) {

    if(currentMap == NULL) return false;
    else if(currentMap->mapPtr == NULL) {
        free(currentMap);
        return true;
    }

    for(int i = 0; i < currentMap->topIndex; i++) {

        free((currentMap->mapPtr)[i].value); //Free string value

    }
    free(currentMap->mapPtr);
    free(currentMap);
    return true;

}



