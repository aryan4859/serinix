// serinix/include/serinix/ata.h 
#ifndef _SERINIX_ATA_H
#define _SERINIX_ATA_H

#include <serinix/fs.h>
#include <serinix/part.h>
#include <serinix/sigcontext.h>
#include <serinix/blk_queue.h>
#include <serinix/timer.h>

#define IDE0_IRQ		14	/* primary controller interrupt */
#define IDE1_IRQ		15	/* secondary controller interrupt */

#define IDE0_MAJOR		3	/* 1st controller major number */
#define IDE1_MAJOR		22	/* 2nd controller major number */
#define IDE_MINORS		4	/* max. minors/partitions per unit */
#define IDE_MASTER_MSF		0	/* IDE master minor shift factor */
#define IDE_SLAVE_MSF		6	/* IDE slave minor shift factor */

#define IDE_PRIMARY		0
#define IDE_SECONDARY		1
#define IDE_MASTER		0
#define IDE_SLAVE		1
#define GET_DRIVE_NUM(_dev_)	((MINOR(_dev_) & (1 <<IDE_SLAVE_MSF)) ? IDE_SLAVE : IDE_MASTER)

#define NR_IDE_CTRLS		2	/* IDE controllers */
#define NR_ATA_DRVS		2	/* max. drives per IDE controller */

/* controller addresses */
#define IDE0_BASE		0x1F0	/* primary controller base addr */
#define IDE0_CTRL		0x3F4	/* primary controller control port */
#define IDE1_BASE		0x170	/* secondary controller base addr */
#define IDE1_CTRL		0x374	/* secondary controller control port */

#define IDE_BASE_LEN		7	/* controller address length */

#define ATA_RDY_RETR_LONG	50000	/* long delay for fast CPUs */
#define ATA_RDY_RETR_SHORT	500	/* short delay for slow CPUs */
#define MAX_IDE_ERR		10	/* number of retries */
#define MAX_CD_ERR		5	/* number of retries in CDROMs */

#define SET_ATA_RDY_RETR(retries)					\
	if((cpu_table.hz / 1000000) <= 100) {				\
		retries = ATA_RDY_RETR_SHORT;				\
	} else {							\
		retries = ATA_RDY_RETR_LONG;				\
	}

#define WAIT_FOR_DISK	(1 * HZ)	/* timeout for hard disk */
#define WAIT_FOR_CD 	(3 * HZ)	/* timeout for cdrom */

/* controller registers */
#define ATA_DATA		0x0	/* Data Port Register (R/W) */
#define ATA_ERROR		0x1	/* Error Register (R) */
#define ATA_FEATURES		0x1	/* Features Register (W) */
#define ATA_SECCNT		0x2	/* Sector Count Register (R/W) */
#define ATA_SECTOR		0x3	/* Sector Number Register (R/W) */
#define ATA_LOWLBA		0x3	/* Low Byte of LBA Register (R/W) */
#define ATA_LCYL		0x4	/* Cylinder Low Register (R/W) */
#define ATA_MIDLBA		0x4	/* Mid Byte of LBA Register (R/W) */
#define ATA_HCYL		0x5	/* Cylinder High Register (R/W) */
#define ATA_HIGHLBA		0x5	/* High Byte of LBA Register (R/W) */
#define ATA_DRVHD		0x6	/* Drive/Head Register (R/W) */
#define ATA_STATUS		0x7	/* Status Register (R) */
#define ATA_COMMAND		0x7	/* Command Register (W) */

#define ATA_ALT_STATUS		0x2	/* Alternate Register (R) */
#define ATA_DEV_CTRL		0x2	/* Device Control Register (W) */

/* error register bits */
#define ATA_ERR_AMNF		0x01	/* Address Mark Not Found */
#define ATA_ERR_TK0NF		0x02	/* Track 0 Not Found */
#define ATA_ERR_ABRT		0x04	/* Aborted Command */
#define ATA_ERR_MCR		0x08	/* Media Change Registered */
#define ATA_ERR_IDNF		0x10	/* Sector ID Field Not Found */
#define ATA_ERR_MC		0x20	/* Media Changed */
#define ATA_ERR_UNC		0x40	/* Uncorrectable Data Error */
#define ATA_ERR_BBK		0x80	/* Bad Block */

/* status register bits */
#define ATA_STAT_ERR		0x01	/* an error ocurred */
#define ATA_STAT_SENS		0x02	/* sense data available */
#define ATA_STAT_CORR		0x04	/* a correctable error ocurred */
#define ATA_STAT_DRQ		0x08	/* device is ready to transfer */
#define ATA_STAT_DSC		0x10	/* device requests service o intr. */
#define ATA_STAT_DWF		0x20	/* drive write fault */
#define ATA_STAT_RDY		0x40	/* drive is ready */
#define ATA_STAT_BSY		0x80	/* drive is busy */

#define ATA_CHS_MODE		0xA0	/* select CHS mode */
#define ATA_LBA_MODE		0xE0	/* select LBA mode */

/* alternate & device control register bits */
#define ATA_DEVCTR_DRQ		0x08	/* Data Request */
#define ATA_DEVCTR_NIEN		0x02	/* Disable Interrupt */
#define ATA_DEVCTR_SRST		0x04	/* Software Reset */

/* ATA I/O commands (28 bit LBA) */
#define ATA_READ_PIO		0x20	/* read sector(s) with retries */
#define ATA_READ_MULTIPLE_PIO	0xC4	/* read multiple sectors */
#define ATA_WRITE_PIO		0x30	/* write sector(s) with retries */
#define ATA_WRITE_MULTIPLE_PIO	0xC5	/* write multiple sectors */
#define ATA_READ_DMA		0xC8	/* read data using DMA */
#define ATA_WRITE_DMA		0xCA	/* write data using DMA */

/* ATA config commands */
#define ATA_SET_MULTIPLE_MODE	0xC6
#define ATA_PACKET		0xA0
#define ATA_IDENTIFY		0xEC	/* identify ATA device */
#define ATA_SET_FEATURES	0xEF

/* ATA_SET_FEATURES subcommands */
#define ATA_SET_XFERMODE	0x03	/* set transfer mode */

/* ATAPI commands */
#define ATAPI_IDENTIFY_PACKET	0xA1	/* identify ATAPI device */
#define ATAPI_TEST_UNIT		0x00
#define ATAPI_REQUEST_SENSE	0x03
#define ATAPI_START_STOP	0x1B
#define ATAPI_MEDIUM_REMOVAL	0x1E
#define ATAPI_GET_CAPACITY	0x25
#define ATAPI_READ10		0x28

#define CD_UNLOCK_MEDIUM	0x00	/* allow medium removal */
#define CD_LOCK_MEDIUM		0x01	/* prevent medium removal */
#define CD_EJECT		0x02	/* eject the CD if possible */
#define CD_LOAD			0x03	/* load the CD (closes tray) */

/* ATAPI CD additional sense code */
#define ASC_NOT_READY		0x04
#define ASC_NO_MEDIUM		0x3A

/* capabilities */
#define ATA_SUPPORTS_CFA	0x848A
#define ATA_HAS_DMA		0x100	/* device supports Multi-word DMA */
#define ATA_HAS_LBA		0x200
#define ATA_MIN_LBA		16514064/* sectors limit for using CHS */

/* general configuration bits */
#define ATA_HAS_CURR_VALUES	0x01	/* current logical values are valid */
#define ATA_HAS_ADVANCED_PIO	0x02	/* device supports PIO 3 or 4 */
#define ATA_HAS_UDMA		0x04	/* device supports UDMA */
#define ATA_REMOVABLE		0x80	/* removable media device */

/* ATAPI types */
#define ATAPI_IS_SEQ_ACCESS	0x01	/* sequential-access device */
#define ATAPI_IS_PRINTER	0x02
#define ATAPI_IS_PROCESSOR	0x03
#define ATAPI_IS_WRITE_ONCE	0x04
#define ATAPI_IS_CDROM		0x05	/* Command Packet Set is MMC-5 */
#define ATAPI_IS_SCANNER	0x06

/* ATA drive flags */
#define DRIVE_IS_ATAPI		0x01
#define DRIVE_IS_CFA		0x02
#define DRIVE_IS_DISK		0x04
#define DRIVE_IS_CDROM		0x08
#define DRIVE_REQUIRES_LBA	0x10
#define DRIVE_HAS_RW_MULTIPLE	0x20
#define DRIVE_HAS_DMA		0x40
#define DRIVE_HAS_DATA32	0x80

#define PRDT_MARK_END		0x8000
#define WAKEUP_AND_RETURN	1

/* ATA/ATAPI-4 based */
struct ata_drv_ident {
	unsigned short int gen_config;		/* general configuration bits */
	unsigned short int logic_cyls;		/* logical cylinders */
	unsigned short int reserved2;
	unsigned short int logic_heads;		/* logical heads */
	unsigned short int retired4;
	unsigned short int retired5;
	unsigned short int logic_spt;		/* logical sectors/track */
	unsigned short int retired7;
	unsigned short int retired8;
	unsigned short int retired9;
	char serial_number[20];			    /* serial number */
	unsigned short int vendor_spec20;
	unsigned short int buffer_cache;
	unsigned short int vendor_spec22;	/* reserved */
	char firmware_rev[8];			    /* firmware version */
	char model_number[40];			    /* model number */
	unsigned short int rw_multiple;
	unsigned short int reserved48;
	unsigned short int capabilities;	/* capabilities */
	unsigned short int reserved50;
	unsigned short int pio_mode;		/* PIO data transfer mode*/
	unsigned short int dma_mode;
	unsigned short int fields_validity;	/* fields validity */
	unsigned short int cur_log_cyls;	/* current logical cylinders */
	unsigned short int cur_log_heads;	/* current logical heads */
	unsigned short int cur_log_spt;		/* current logical sectors/track */
	unsigned short int cur_capacity;	/* current capacity in sectors */
	unsigned short int cur_capacity2;	/* 32bit number */
	unsigned short int mult_sect_set;	/* multiple sector set */
	unsigned short int mult_sect_mode;	/* multiple sectors mode */
	unsigned short int dma_mword_sect_mode;	/* multi-word DMA mode */
	unsigned short int lba_mode_set;	/* LBA mode set */
	unsigned short int dma_set;		    /* DMA mode set */
	unsigned short int current_cache;	/* current cache size */
	unsigned short int adv_pio_set;	    /* advanced PIO mode support */
	unsigned short int max_capacity;	/* max capacity */
	unsigned short int max_capacity2;	/* max capacity 2 */
};

#endif
