// serinix/include/serinix/fbcon.h

#ifndef _SERINIX_FBCON_H
#define _SERINIX_FBCON_H

void fbcon_put_char(struct vconsole *, unsigned char);

void fbcon_put_char(struct vconsole *, unsigned char);
void fbcon_insert_char(struct vconsole *);
void fbcon_delete_char(struct vconsole *);
void fbcon_update_curpos(struct vconsole *);
void fbcon_show_cursor(struct vconsole *, int);
void fbcon_get_curpos(struct vconsole *);
void fbcon_write_screen(struct vconsole *, int, int, short int);
void fbcon_blank_screen(struct vconsole *);
void fbcon_scroll_screen(struct vconsole *, int, int);
void fbcon_restore_screen(struct vconsole *);
void fbcon_screen_on(struct vconsole *);
void fbcon_screen_off(unsigned int);
void fbcon_buf_scroll(struct vconsole *, int);
void fbcon_cursor_blink(unsigned int);
void fbcon_init(void);

#endif