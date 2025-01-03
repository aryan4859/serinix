// serinix/include/vgacon.h

#ifndef _SERINIX_VGACON_H
#define _SERINIX_VGACON_H

#include <serinix/console.h>

#define MONO_ADDR		0xB0000L
#define COLOR_ADDR		0xB8000L

#define MONO_6845_ADDR		0x3B4	/* i/o address (+1 for data register) */
#define COLOR_6845_ADDR		0x3D4	/* i/o address (+1 for data register) */

#define ATTR_CONTROLLER		0x3C0	/* attribute controller registrer */
#define ATTR_CONTROLLER_PAS	0x20	/* palette address source */
#define INPUT_STAT1		0x3DA	/* input status #1 register */

#define CRT_INDEX		0
#define CRT_DATA		1
#define CRT_CURSOR_STR		0xA
#define CRT_CURSOR_END		0xB
#define CRT_START_ADDR_HI	0xC
#define CRT_START_ADDR_LO	0xD
#define CRT_CURSOR_POS_HI	0xE
#define CRT_CURSOR_POS_LO	0xF

#define CURSOR_MASK		0x1F
#define CURSOR_DISABLE		0x20

void vgacon_put_char(struct vconsole *, unsigned char);
void vgacon_insert_char(struct vconsole *);
void vgacon_delete_char(struct vconsole *);
void vgacon_update_curpos(struct vconsole *);
void vgacon_show_cursor(struct vconsole *, int);
void vgacon_get_curpos(struct vconsole *);
void vgacon_write_screen(struct vconsole *, int, int, short int);
void vgacon_blank_screen(struct vconsole *);
void vgacon_scroll_screen(struct vconsole *, int, int);
void vgacon_restore_screen(struct vconsole *);
void vgacon_screen_on(struct vconsole *);
void vgacon_screen_off(unsigned int);
void vgacon_buf_scroll(struct vconsole *, int);
void vgacon_cursor_blink(unsigned int);
void vgacon_init(void);

#endif