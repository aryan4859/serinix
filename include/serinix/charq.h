// serinix/include/serinix/charq.h

#ifdef _SERINIX_CHARQ_H
#define _SERINIX_CHARQ_H

#define CBSIZE 32
#define NR_CB_QUEUE 8

#define LAST_CHAR(q)	((q)->tail ? (q)->tail->data[(q)->tail->end_off - 1] : '\0')

struct clist {
	unsigned short int count;
	unsigned short int cb_num;
	struct cblock *head;
	struct cblock *tail;
};

struct cblock {
	unsigned short int start_off;
	unsigned short int end_off;
	unsigned char data[CBSIZE];
	struct cblock *prev;
	struct cblock *next;
};

int charq_putchar(struct clist *, unsigned char);
int charq_unputchar(struct clist *);
unsigned char charq_getchar(struct clist *);
void charq_flush(struct clist *);
int charq_room(struct clist *q);
void charq_init(void);

#endif