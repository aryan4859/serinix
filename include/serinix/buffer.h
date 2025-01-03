// serinix/include/serinix/buffer.h

#include _SERINIX_BUFFER_H
#include _SERINIX_BUFFER_H

#include <serinix/types.h>
#include <serinix/fs.h>
#include <serinix/blk_queue.h>

#define BUFFER_VALID 0X01
#define BUFFER_LOCKED 0x02
#define BUFFER_DIRTY 0x04

#define BLK_READ 1
#define BLK_WRITE 2

struct buffer {
    __dev_t dev;		/* device number */
	__blk_t block;		/* block number */
	int size;			/* block size (in bytes) */
	int flags;
	char *data;			/* block contents */
	struct buffer *prev;
	struct buffer *next;
	struct buffer *prev_hash;
	struct buffer *next_hash;
	struct buffer *prev_free;
	struct buffer *next_free;
	struct buffer *prev_dirty;
	struct buffer *next_dirty;
	struct buffer *first_sibling;
	struct buffer *next_sibling;
	struct buffer *next_retained;
};

extern struct *buffer_table;
extern struct **buffer_hash_table;

extern unsigned int buffer_hash_table_size;

int gbread(struct device *, struct blk_request *);
struct buffer *bread(__dev_t, __blk_t, int);
void bwrite(struct buffer *);
void brelse(struct buffer *);
void sync_buffers(__dev_t);
void invalidate_buffers(__dev_t);
int reclaim_buffers(void);
int kbdflushd(void);
void buffer_init(void);

#endif