#ifndef _SERINIX_ATAPI_CD_H
#define _SERINIX_ATAPI_CD_H

#include <serinix/fs.h>

#define ATAPI_CD_SECTSIZE	BLKSIZE_2K	/* sector size (in bytes) */

int atapi_cd_open(struct inode *, struct fd *);
int atapi_cd_close(struct inode *, struct fd *);
int atapi_cd_read(__dev_t, __blk_t, char *, int);
int atapi_cd_ioctl(struct inode *, int, unsigned int);
__loff_t atapi_cd_llseek(struct inode *, __loff_t);
int atapi_cd_init(struct ide *, struct ata_drv *);

#endif /* _SERINIX_ATAPI_CD_H */