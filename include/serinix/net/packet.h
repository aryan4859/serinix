// serinix/include/serinix/net/packet.h

#ifdef CONFIG_NET

#ifndef _SERINIX_NET_PACKET_H
#define _SERINIX_NET_PACKET_H

#include <serinix/types.h>

#include <serinix/types.h>

struct packet {
    char *data;
    int len;
    __off_t offset;
	struct socket *socket;
	struct packet *prev;
	struct packet *next;
};

struct packet *peek_packet(struct packet *);
struct packet *remove_packet_from_queue(struct packet **);
void append_packet_to_queue(struct packet *, struct packet **);

#endif
#endif