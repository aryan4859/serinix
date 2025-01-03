//serinix/include/serinix/bios.h

#ifndef _SERINIX_BIOS_H
#define _SERINIX_BIOS_H

#include <serinix/multiboot1.h>

#define NR_BIOS_MM_ENT  50

struct bios_mem_map {
    unsigned int from;
    unsigned int from_h1;
    unsigned int to;
    unsigned int to_hi;
    int type;
}

extern struct bios_mem_map bios_mem_map[NR_BIOS_MM_ENT];
extern struct bios_mem_map kernel_mem_map[NR_BIOS_MM_ENT];

int is_addr_in_bios_map(unsigned int);
void bios_map_reserve(unsigned int, unsigned int);
void bios_map_init(struct multiboot_mmap_entry *, unsigned int);

#endif