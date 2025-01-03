// serinix/include/serinix/utime.h

#ifndef _SERINIX_UTIME_H
#define _SERINIX_UTIME_H

#include <serinix/types.h>  // Include type definitions from serinix/types.h

// Structure that holds the access and modification times of a file
struct utimbuf {
    __time_t actime;  // Time when the file was last accessed
    __time_t modtime; // Time when the file was last modified
};

#endif