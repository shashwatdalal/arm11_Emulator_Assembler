#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Imported Files
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//linked list queue
typedef struct linkedListElement {
    char *value;
    struct linkedListElement *prev;
    struct linkedListElement *next;
} llist_e;

typedef struct linkedList {
    llist_e *header;
    llist_e *footer;
    int size;
} llist_t;

//symbol table
typedef struct symbolTableElement {
    char *key;
    uint32_t value;
    struct symbolTableElement *next;
} st_e;

typedef struct symbolTable {
    st_e *head;
} st_t;

typedef struct instruction {
    char *opcode;
    char *arg1;
    char *arg2;
    char *arg3;
    char *arg4;
    int memoryLocation;
    int numOfInstructions;
    st_t *symbolTable;
    llist_t *constantValues;
} inst_t;

typedef uint32_t (*functionPtr)(inst_t*);

//function table
typedef struct functionTableElement {
    char *key;
    functionPtr value;
    struct functionTableElement *next;
} ft_e;

typedef struct functionTable {
    ft_e *head;
} ft_t;

#endif
