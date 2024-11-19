#include "fat.h"
#include "sd.h"
#include <string.h>

struct boot_sector *bs;
char bootSector[512];
char fat_table[8 * 512];
unsigned int root_sector;

int fatInit() {
    // Read boot sector (sector 0) into bootSector buffer
    sd_readblock(0, (unsigned char *)bootSector, 1);  // Cast added
    bs = (struct boot_sector*)bootSector;

    // Validate boot signature and FAT type
    if (bs->boot_signature != 0xAA55) {
        return -1;  // Invalid boot signature
    }
    if (strncmp(bs->fs_type, "FAT12", 5) != 0 && strncmp(bs->fs_type, "FAT16", 5) != 0) {
        return -1;  // Unsupported filesystem
    }

    // Load FAT table
    sd_readblock(bs->num_reserved_sectors, (unsigned char *)fat_table, bs->num_fat_tables * bs->num_sectors_per_fat);  // Cast added

    // Calculate root directory sector start
    root_sector = bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_hidden_sectors;

    return 0;  // Successful initialization
}

