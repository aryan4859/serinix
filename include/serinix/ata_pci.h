// serinix/include/serinix/ata_pci.h 

#ifndef _SERINIX_ATA_PCI_H
#define _SERINIX_ATA_PCI_H

#ifdef CONFIG_PCI
#include <serinix/ata.h>

void ata_setup_dma(struct ide *, struct ata_drv *, char *, int);
void ata_start_dma(struct ide *, struct ata_drv *, int);
void ata_stop_dma(struct ide *, struct ata_drv *);
int ata_pci(struct ide *);
#endif /* CONFIG_PCI */

#endif  