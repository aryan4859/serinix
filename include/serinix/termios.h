/*
 * serinix/include/serinix/termios.h
 */

#ifndef _SERINIX_TERMIOS_H
#define _SERINIX_TERMIOS_H

#include <serinix/termbits.h>  // Include termbits.h for terminal flag and control structure definitions

// Define the structure for terminal window size (rows, columns, pixel dimensions)
struct winsize {
    unsigned short int ws_row;   // Number of rows
    unsigned short int ws_col;   // Number of columns
    unsigned short int ws_xpixel; // Width in pixels
    unsigned short int ws_ypixel; // Height in pixels
};

#define NCC 8  // Number of control characters in the old terminal control structure

// Old terminal control structure for compatibility
struct termio {
    unsigned short int c_iflag;  // Input mode flags
    unsigned short int c_oflag;  // Output mode flags
    unsigned short int c_cflag;  // Control mode flags
    unsigned short int c_lflag;  // Local mode flags
    unsigned char c_line;        // Line discipline
    unsigned char c_cc[NCC];     // Control characters
};

#define NCCS 19  // Number of control characters in the new terminal control structure

// New terminal control structure with extended control characters and proper flag types
struct termios {
    tcflag_t c_iflag;    // Input mode flags
    tcflag_t c_oflag;    // Output mode flags
    tcflag_t c_cflag;    // Control mode flags
    tcflag_t c_lflag;    // Local mode flags
    cc_t c_line;         // Line discipline
    cc_t c_cc[NCCS];     // Control characters
};

#endif /* _SERINIX_TERMIOS_H */
