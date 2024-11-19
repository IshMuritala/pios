

#include "fat.h"
#include "sd.h"
#include <string.h>
#include <ctype.h>

int fatOpen(const char *filename, struct root_directory_entry *rde) {
    char upper_filename[12];
    int i;
    for (i = 0; i < 8; i++) upper_filename[i] = toupper(filename[i]);
    for (; i < 11; i++) upper_filename[i] = ' ';  // Pad with spaces
    upper_filename[11] = '\0';

    char rde_buffer[512];
    int root_dir_sectors = ((bs->num_root_dir_entries * 32) + (bs->bytes_per_sector - 1)) / bs->bytes_per_sector;

    // Loop through root directory entries
    for (int i = 0; i < root_dir_sectors; i++) {
        sd_readblock(root_sector + i, (unsigned char *)rde_buffer, 1);  // Cast added
        for (int j = 0; j < bs->bytes_per_sector / sizeof(struct root_directory_entry); j++) {
            struct root_directory_entry *entry = (struct root_directory_entry *)&rde_buffer[j * sizeof(struct root_directory_entry)];
            if (strncmp(entry->file_name, upper_filename, 11) == 0) {
                memcpy(rde, entry, sizeof(struct root_directory_entry));  // Copy RDE data to output structure
                return 0;  // File found
            }
        }
    }
    return -1;  // File not found
}

