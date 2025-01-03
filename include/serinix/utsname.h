// serinix/include/utsname.h

#ifndef _SERINIX_UTSNAME_H
#define _SERINIX_UTSNAME_H


#define _OLD_UTSNAME_LENGTH	8
#define _UTSNAME_LENGTH		64

#ifndef _UTSNAME_NODENAME_LENGTH
#define _UTSNAME_NODENAME_LENGTH _UTSNAME_LENGTH
#endif

/*
 * Structures describing the system and machine information.
 * These structures have evolved over time to accommodate new requirements.
 */

struct oldold_utsname {
    char sysname[_OLD_UTSNAME_LENGTH + 1];  /* Name of the operating system */
    char nodename[_OLD_UTSNAME_LENGTH + 1]; /* Name of the node in the network */
    char release[_OLD_UTSNAME_LENGTH + 1];  /* Release level */
    char version[_OLD_UTSNAME_LENGTH + 1];  /* Version level */
    char machine[_OLD_UTSNAME_LENGTH + 1];  /* Machine hardware name */
};

/* Old structure describing the system and machine */
struct old_utsname {
    char sysname[_UTSNAME_LENGTH + 1];               /* Name of the operating system */
    char nodename[_UTSNAME_NODENAME_LENGTH + 1];    /* Name of the node in the network */
    char release[_UTSNAME_LENGTH + 1];              /* Release level */
    char version[_UTSNAME_LENGTH + 1];              /* Version level */
    char machine[_UTSNAME_LENGTH + 1];              /* Machine hardware name */
};

/* New structure describing the system and machine */
struct new_utsname {
    char sysname[_UTSNAME_LENGTH + 1];               /* Name of the operating system implementation */
    char nodename[_UTSNAME_NODENAME_LENGTH + 1];    /* Name of the node in the network */
    char release[_UTSNAME_LENGTH + 1];              /* Current release level */
    char version[_UTSNAME_LENGTH + 1];              /* Current version level */
    char machine[_UTSNAME_LENGTH + 1];              /* Hardware type name */
    char domainname[_UTSNAME_LENGTH + 1];           /* Domain name of the system */
};

/* Global instance of the new structure representing the current system */
extern struct new_utsname sys_utsname;

/* Machine type constant */
extern char UTS_MACHINE[_UTSNAME_LENGTH + 1];

#endif