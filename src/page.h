#ifndef PAGE_H
#define PAGE_H

// Structure representing a physical page
struct ppage {
    struct ppage *next;          // Pointer to the next page in list
    struct ppage *prev;          // Pointer to the previous page in list
    void *physical_addr;         // Physical address of the page
};

// Funct prototypes
void init_pfa_list(void);
struct ppage *allocate_physical_pages(unsigned int npages);
void free_physical_pages(struct ppage *ppage_list);

#endif // PAGE_H
