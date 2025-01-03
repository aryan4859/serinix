// serinix/include/serinix/devices.h
#ifndef _SERINIX_DEVICES_H
#define _SERINIX_DEVICES_H

#include <serinix/types.h>
#include <serinix/fs.h>

#define NP_BLKDEV 128 // mas no. of block dev
#define NR_CHRDEV 128 // max no. of char dev

#define BLK_DEV 1
#define CHR_DEV 2

#define SET_MINOR(minors, bit)   ((minors[(bit) / 32]) |= (1 << ((bit) % 32)))
#define CLEAR_MINOR(minors, bit) ((minors[(bit) / 32]) &= ~(1 << ((bit) % 32)))
#define TEST_MINOR(minors, bit)	 ((minors[(bit) / 32]) & (1 << ((bit) % 32)))

struct device {
	char *name;
	unsigned char major;
	unsigned int minors[8];		/* bitmap of 256 bits */
	unsigned int *blksize;		/* default minor blocksizes, in KB */
	void *device_data;		/* mostly used for minor sizes, in KB */
	struct fs_operations *fsop;
	void *requests_queue;
	void *xfer_data;
	struct device *next;
};

extern struct device *chr_device_table[NR_CHRDEV];
extern struct device *blk_device_table[NR_BLKDEV];

int register_device(int, struct device *);
struct device *get_device(int, __dev_t);
int chr_dev_open(struct inode *, struct fd *);
int blk_dev_open(struct inode *, struct fd *);
int blk_dev_close(struct inode *, struct fd *);
int blk_dev_read(struct inode *, struct fd *, char *, __size_t);
int blk_dev_write(struct inode *, struct fd *, const char *, __size_t);
int blk_dev_ioctl(struct inode *, int, unsigned int);
__loff_t blk_dev_llseek(struct inode *, __loff_t);

void dev_init(void);

#endif