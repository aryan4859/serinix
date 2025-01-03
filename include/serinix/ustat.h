//serinix/include/serinix/ustat.h

#ifndef _SERINIX_USTAT_H
#define _SERINIX_USTAT_H

#include <serinix/types.h>  // Include type definitions from serinix/types.h

// Structure to hold file system status information
struct ustat {
    __daddr_t f_tfree;   // Total number of free blocks in the file system
    __ino_t f_tinode;    // Total number of free inodes in the file system
    char f_fname;        // Name of the file system
    char f_fpack;        // Name of the file system pack
};

#endif /* _SERINIX_USTAT_H */