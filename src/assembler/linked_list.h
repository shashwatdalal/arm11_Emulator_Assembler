#ifndef ARM11_38_LINKED_LIST_H
#define ARM11_38_LINKED_LIST_H

// Imported Files
#include "definitions.h"

// Methods
llist_t *initLinkedList(void);
void freeLinkedList(llist_t *list);
void llistEnqueue(llist_t *list, void *value);
void *llistPop(llist_t *list);

#endif //ARM11_38_LINKED_LIST_H
