// Imported Files
#include "linked_list.h"
#include <stdio.h>
#include <inttypes.h>

// Methods
// Initialise an element of the list
llist_e *initListItem(void) {
  llist_e *newElement = malloc(sizeof(llist_e));
  memset(newElement,0,sizeof(llist_e));
  if (newElement == NULL) {
    return NULL;
  }
  // Initialise all fields to NULL (or 0 respectively)
  newElement->value = NULL;
  newElement->prev = NULL;
  newElement->next = NULL;
  return newElement;
}

// Initialise the list
llist_t *initLinkedList(void) {
  llist_t *newList = malloc(sizeof(llist_t));
  memset(newList,0,sizeof(llist_t));
  if (newList == NULL) {
    return NULL;
  }
  // Initialise fields to NULL (or 0 respectively)
  llist_e *header = initListItem();
  llist_e *footer = initListItem();
  header->prev = NULL;
  footer->next = NULL;
  header->next = newList->footer;
  footer->prev = newList->footer;
  newList->header = header;
  newList->footer = footer;
  newList->size = 0;
  return newList;
}

// Free the memory used by the list
void freeLinkedList(llist_t *list) {
  free(list->header);
  free(list->footer);
  free(list);
}

// Add an item to the queue
void llistEnqueue(llist_t *list, void *value) {
  llist_e *newElement = initListItem();
  newElement->value = value;
  if (list->size == 0) {
    // The list is currently empty
    list->header = newElement;
    newElement->next = list->footer;
    list->footer->prev = newElement;
  } else if (list->size == 1) {
    list->footer = newElement;
    newElement->prev = list->header;
    list->header->next = newElement;
  } else {
    // There is at least one element in the list
    newElement->next = NULL;
    newElement->prev = list->footer;
    list->footer->next = newElement;
    list->footer = newElement;
  }
  list->size++;
}

// Get the next element in the queue
void *llistPop(llist_t *list) {
  llist_e *returnElement = NULL;
  if (list->size == 0) {
    perror("list->size = 0 (list is empty) @ \"linked_list.c\".llistPop\n");
    return NULL;
  } else if (list->size == 2) {
    // Remove from header
    returnElement = list->header;
    list->footer->prev = NULL;
    list->header = list->footer;
    list->footer = NULL;
  } else if (list->size == 1) {
    // Remove from header
    returnElement = list->header;
    list->header = NULL;
  } else {
    returnElement = list->header;
    list->header = returnElement->next;
    list->header->prev = NULL;
  }
  list->size--;
  void *returnValue = returnElement->value;
  free(returnElement);
  return returnValue;
}
