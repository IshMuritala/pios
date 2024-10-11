
#include "page.h"

// array of 128 physical pages, each 2MB
struct ppage physical_page_array[128];

// Free list of physical pages
struct ppage *free_physical_pages = NULL;

// Initialize the page frame allocator list
void init_pfa_list(void) {
    for (int i = 0; i < 128; i++) {
        physical_page_array[i].next = NULL;
        physical_page_array[i].prev = NULL;
        physical_page_array[i].physical_addr = (void *)(i * 2 * 1024 * 1024);  // 2MB per page

        // Insert the page into the free list
        if (free_physical_pages == NULL) {
            free_physical_pages = &physical_page_array[i];
        } else {
            // Insert the page at the head of free list
            physical_page_array[i].next = free_physical_pages;
            free_physical_pages->prev = &physical_page_array[i];
            free_physical_pages = &physical_page_array[i];
        }
    }
}


struct ppage *allocate_physical_pages(unsigned int npages) {
    if (npages == 0 || free_physical_pages == NULL) {
        return NULL;  // Invalid number of pages or no pages left to allocate
    }

    struct ppage *allocd_list = NULL;
    struct ppage *last_allocd_page = NULL;

    for (unsigned int i = 0; i < npages; i++) {
        if (free_physical_pages == NULL) {
            return NULL;
        }

        // Remove the first page from the free list
        struct ppage *page_to_allocate = free_physical_pages;
        free_physical_pages = free_physical_pages->next;

        if (free_physical_pages != NULL) {
            free_physical_pages->prev = NULL;
        }

        // Add the page to the allocated list
        page_to_allocate->next = NULL;
        page_to_allocate->prev = last_allocd_page;
        if (last_allocd_page != NULL) {
            last_allocd_page->next = page_to_allocate;
        } else {
            allocd_list = page_to_allocate;
        }

        last_allocd_page = page_to_allocate;
    }

    return allocd_list;  // Return allocated pages
}

void free_physical_pages(struct ppage *ppage_list) {
    if (ppage_list == NULL) {
        return;  // Nothing to free
    }

    struct ppage *current_page = ppage_list;

    while (current_page != NULL) {
        struct ppage *next_page = current_page->next;

        current_page->next = free_physical_pages;
        if (free_physical_pages != NULL) {
            free_physical_pages->prev = current_page;
        }
        free_physical_pages = current_page;
        current_page->prev = NULL;

        // Move to the next page in list
        current_page = next_page;
    }
}
