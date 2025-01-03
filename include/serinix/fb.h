#ifndef _SERINIX_FB_H
#define _SERINIX_FB_H

#include <serinix/fs.h>

#define FB_MAJOR	29	/* major number */
#define FB_MINORS	1	/* number of supported minors */

int fb_open(struct inode *, struct fd *);
int fb_close(struct inode *, struct fd *);
int fb_read(struct inode *, struct fd *, char *, __size_t);
int fb_write(struct inode *, struct fd *, const char *, __size_t);
int fb_mmap(struct inode *, struct vma *);
int fb_ioctl(struct inode *, int, unsigned int);
__loff_t fb_llseek(struct inode *, __loff_t);

void fb_init(void);

#endif