
#include "list.h"
#include <stdio.h>


void list_add(struct list_element **list_head, struct list_element *new_element) {
    new_element->next = *list_head;  // Point new element to the current head
    *list_head = new_element;        // Make new element the new head
}


void list_remove(struct list_element **list_head, struct list_element *element) {
    if (*list_head == NULL) return;


    // If the element to remove is the head
    if (*list_head == element) {
        *list_head = element->next;
        return;
    }


    struct list_element *current = *list_head;
    while (current->next != NULL) {
        if (current->next == element) {
            current->next = element->next;  // Bypass element to remove
            return;
        }
        current = current->next;
    }
}
