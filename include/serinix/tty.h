 // serinix/include/serinix/tty.h 
#ifndef _SERINIX_TTY_H
#define _SERINIX_TTY_H

#include <serinix/termios.h>
#include <serinix/fs.h>
#include <serinix/fd.h>
#include <serinix/charq.h>
#include <serinix/console.h>
#include <serinix/serial.h>

#define NR_TTYS		NR_VCONSOLES + NR_SERIAL  // Total number of TTYs (virtual consoles + serial devices)

#define TAB_SIZE	8
#define MAX_TAB_COLS	132  // Maximum number of columns for tab stops

#define LAST_CHAR(q)	((q)->tail ? (q)->tail->data[(q)->tail->end_off - 1] : '\0')  // Get last character in the queue

/* TTY flags */
#define TTY_HAS_LNEXT		0x01  // Indicates presence of the LNEXT flag

// Structure to hold keyboard state
struct kbd_state {
	char mode;  // Mode of the keyboard input
};

// Structure representing a TTY (teletypewriter) device
struct tty {
	__dev_t dev;  // Device identifier
	struct clist read_q;  // Queue for reading data
	struct clist cooked_q;  // Queue for processed data
	struct clist write_q;  // Queue for writing data
	short int count;  // Number of active references
	struct termios termios;  // Terminal settings (e.g., input/output control)
	struct winsize winsize;  // Terminal window size
	struct kbd_state kbd;  // Keyboard state
	__pid_t pid, pgid, sid;  // Process IDs (PID, PGID, SID)
	void *driver_data;  // Driver-specific data
	int canon_data;  // Canonical input data
	char tab_stop[132];  // Tab stop positions
	int column;  // Current column for display
	int flags;  // Flags to manage TTY behavior

	/* TTY driver operations */
	void (*stop)(struct tty *);  // Function to stop TTY operations
	void (*start)(struct tty *);  // Function to start TTY operations
	void (*deltab)(struct tty *);  // Function to delete tab stop
	void (*reset)(struct tty *);  // Function to reset TTY
	void (*input)(struct tty *);  // Function to handle input
	void (*output)(struct tty *);  // Function to handle output
	int (*open)(struct tty *);  // Function to open TTY
	int (*close)(struct tty *);  // Function to close TTY
	void (*set_termios)(struct tty *);  // Function to set terminal settings
};

extern struct tty tty_table[];  // Array holding all TTYs

// Function declarations
int register_tty(__dev_t);  // Register a new TTY
struct tty *get_tty(__dev_t);  // Get a TTY by its device number
void disassociate_ctty(struct tty *);  // Disconnect the controlling terminal
void termios_reset(struct tty *);  // Reset terminal settings to defaults
void do_cook(struct tty *);  // Process cooked input data
int tty_open(struct inode *, struct fd *);  // Open a TTY device
int tty_close(struct inode *, struct fd *);  // Close a TTY device
int tty_read(struct inode *, struct fd *, char *, __size_t);  // Read data from a TTY
int tty_write(struct inode *, struct fd *, const char *, __size_t);  // Write data to a TTY
int tty_ioctl(struct inode *, int cmd, unsigned int);  // Handle TTY-specific IOCTL commands
__loff_t tty_llseek(struct inode *, __loff_t);  // Seek within a TTY
int tty_select(struct inode *, int);  // Select a TTY for I/O operations
void tty_init(void);  // Initialize TTY subsystem

int vt_ioctl(struct tty *, int, unsigned int);  // Handle virtual terminal IOCTL commands

#endif /* _SERINIX_TTY_H */
