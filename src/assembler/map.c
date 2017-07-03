// Imported Files
#include "map.h"

//Function Table Methods
// Initalise new table
ft_t *initFunctionTable(void) {
  ft_t *newTable = malloc(sizeof(ft_t));
  if (newTable == NULL) {
    return NULL;
  }
  newTable->head = NULL;
  return newTable;
}

// Initalise new table element
ft_e *initFunctionTableElement(void) {
  ft_e *newElem = malloc(sizeof(ft_e));
  if (newElem == NULL) {
    return NULL;
  }
  newElem->key = NULL;
  newElem->value = NULL;
  newElem->next = NULL;
  return newElem;
}

// Free memory used by table
void freeFunctionTable(ft_t *map) {
  ft_e *current = map->head;
  while (current != NULL) {
    ft_e *temp = current->next;
    free(current);
    current = temp;
  }
  free(map);
}

// Add entry to table
void ftPut(ft_t *map, char *key, functionPtr value) {
  ft_e *newElem = initFunctionTableElement();
  newElem->key = key;
  newElem->value = value;
  if (map->head == NULL) {
    // Empty map
    map->head = newElem;
    newElem->next = NULL;
  } else {
    // (E) an element
    newElem->next = map->head;
    map->head = newElem;
  }
}

// Obtain value from given key
functionPtr ftGet(ft_t *map, char *key) {
  ft_e *current = map->head;
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->value;
    }
    current = current->next;
  }
  printf("Key '%s' not found\n", key);
  return NULL;
}

//Symbol Table
// Initalise new table
st_t *initSymbolTable(void) {
  st_t *newTable = malloc(sizeof(st_t));
  if (newTable == NULL) {
    return NULL;
  }
  newTable->head = NULL;
  return newTable;
}

// Initalise new table element
st_e *initSymbolTableElement(void) {
  st_e *newElem = malloc(sizeof(st_e));
  if (newElem == NULL) {
    return NULL;
  }
  newElem->key = NULL;
  newElem->value = 0;
  newElem->next = NULL;
  return newElem;
}

// Free memory used by table
void freeSymbolTable(st_t *map) {
  st_e *current = map->head;
  while (current != NULL) {
    st_e *temp = current->next;
    free(current->next);
    free(current);
    current = temp;
  }
  free(map);
}

// Add entry to table
void stPut(st_t *map, char *key, uint32_t value) {
  st_e *newElem = initSymbolTableElement();
  newElem->key = key;
  newElem->value = value;
  if (map->head == NULL) {
    // Empty map
    map->head = newElem;
    newElem->next = NULL;
  } else {
    // (E) an element
    newElem->next = map->head;
    map->head = newElem;
  }
}

// Obtain value from given key
uint32_t stGet(st_t *map, char *key) {
  st_e *current = map->head;
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->value;
    }
    current = current->next;
  }
  printf("Key '%s' not found\n", key);
  return 0;
}
