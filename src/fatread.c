

#include "fat.h"
#include "sd.h"
#include <string.h>

int fatRead(const struct root_directory_entry *rde, char *buffer, unsigned int buffer_size) {
    unsigned int cluster = rde->cluster;
    unsigned int bytes_read = 0;
    char cluster_buffer[CLUSTER_SIZE];

    while (cluster < 0xFFF8 && bytes_read < rde->file_size) {
        unsigned int sector = root_sector + (cluster - 2) * SECTORS_PER_CLUSTER;
        sd_readblock(sector, (unsigned char *)cluster_buffer, SECTORS_PER_CLUSTER);  // Cast added

        unsigned int to_copy = (bytes_read + CLUSTER_SIZE > rde->file_size) ? rde->file_size - bytes_read : CLUSTER_SIZE;
        memcpy(buffer + bytes_read, cluster_buffer, to_copy);
        bytes_read += to_copy;

        // Get next cluster from FAT table (assuming FAT12 here)
        unsigned int fat_index = (cluster * 3) / 2;
        if (cluster & 1) {
            cluster = (fat_table[fat_index] >> 4) | (fat_table[fat_index + 1] << 4);
        } else {
            cluster = (fat_table[fat_index] | ((fat_table[fat_index + 1] & 0x0F) << 8));
        }
    }
    return bytes_read;  // Return number of bytes read
}

