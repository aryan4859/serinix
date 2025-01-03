#ifndef _SERINIX_TYPES_H
#define _SERINIX_TYPES_H

/* Signed and unsigned type definitions for various sizes */
typedef __signed__ char __s8;
typedef unsigned char __u8;
typedef __signed__ short int __s16;
typedef unsigned short int __u16;
typedef __signed__ int __s32;
typedef unsigned int __u32;
typedef __signed__ long long int __s64;
typedef unsigned long long int __u64;

/* Type definitions for system-related identifiers */
typedef __u16 __uid_t;     /* User ID */
typedef __u16 __gid_t;     /* Group ID */
typedef __u32 __ino_t;     /* Inode number */
typedef __u64 __ino64_t;   /* 64-bit inode number */
typedef __u16 __mode_t;    /* File mode */
typedef __u16 __nlink_t;   /* Number of links */
typedef __u32 __off_t;     /* File offset */
typedef __s32 __pid_t;     /* Process ID */
typedef __s32 __ssize_t;   /* Signed size type */
typedef __u32 __size_t;    /* Unsigned size type */
typedef __u32 __clock_t;   /* Clock ticks */
typedef __u32 __time_t;    /* Time type */
typedef __u16 __dev_t;     /* Device ID */
typedef __u16 __key_t;     /* IPC key */
typedef __s32 __blk_t;     /* Block number, signed for error codes */
typedef __s32 __daddr_t;   /* Disk address */
typedef __s64 __loff_t;    /* Large file offset, signed for error codes */

/* Maximum number of file descriptors supported in an fd_set */
#define __FD_SETSIZE  64

/* Bit manipulation macros for fd_set */
#define __NFDBITS     (sizeof(unsigned int) * 8)
#define __FDELT(d)    ((d) / __NFDBITS)
#define __FDMASK(d)   (1 << ((d) % __NFDBITS))

/* fd_set structure for managing file descriptors in select() */
typedef struct {
    unsigned int fds_bits[__FD_SETSIZE / __NFDBITS];
} fd_set;

/* Structure for scatter-gather I/O operations */
struct iovec {
    void *iov_base;   /* Base address of the buffer */
    __size_t iov_len; /* Length of the buffer */
};

/* Macros for manipulating fd_set */
#define __FD_ZERO(set)       (memset_b((void *)(set), 0, sizeof(fd_set)))
#define __FD_SET(d, set)     ((set)->fds_bits[__FDELT(d)] |= __FDMASK(d))
#define __FD_CLR(d, set)     ((set)->fds_bits[__FDELT(d)] &= ~__FDMASK(d))
#define __FD_ISSET(d, set)   ((set)->fds_bits[__FDELT(d)] & __FDMASK(d))

/* Macro for byte-swapping a 32-bit integer */
#define __bswap32(x) \
    ((unsigned int)(              \
        ((x & 0xFF) << 24) |      \
        (((x >> 8) & 0xFF) << 16) | \
        (((x >> 16) & 0xFF) << 8) | \
        ((x >> 24) & 0xFF)        \
    ))

#endif 