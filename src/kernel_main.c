


#include "fat.h"
#include <stdio.h>  // For printf

void kernel_main() {
    // Clear the BSS segment
    clear_bss();

    // Initialize the FAT filesystem
    if (fatInit() != 0) {
        printf("Failed to initialize FAT filesystem.\n");
        return;
    }
    printf("FAT filesystem initialized.\n");

    // Define a root directory entry structure to store file information
    struct root_directory_entry rde;

    // Open a file (replace "TEST    TXT" with your actual file name)
    if (fatOpen("TEST    TXT", &rde) != 0) {
        printf("Failed to open file.\n");
        return;
    }
    printf("File opened. Start cluster: %d, Size: %d\n", rde.cluster, rde.file_size);

    // Create a buffer to hold the file data
    char buffer[rde.file_size];

    // Read the file contents into the buffer
    if (fatRead(&rde, buffer, rde.file_size) != rde.file_size) {
        printf("Failed to read file.\n");
        return;
    }
    printf("File read successfully:\n%s\n", buffer);

    // Rest of your kernel loop or other main functionality
    while (1) {
        delay();
    }

    if (mmu_on() != 0) {
        while (1);
    }
}




