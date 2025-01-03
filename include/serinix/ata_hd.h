#ifndef _SERINIX_ATA_HD_H
#define _SERINIX_ATA_HD_H

#include <serinix/types.h>

#define ATA_HD_SECTSIZE		512	 
int ata_hd_open(struct inode *, struct fd *);
int ata_hd_close(struct inode *, struct fd *);
int ata_hd_read(__dev_t, __blk_t, char *, int);
int ata_hd_write(__dev_t, __blk_t, char *, int);
int ata_hd_ioctl(struct inode *, int, unsigned int);
__loff_t ata_hd_llseek(struct inode *, __loff_t);
int ata_hd_init(struct ide *, struct ata_drv *);

#endif  