/*
Linker script for the serinix kernel
* Configures memory layout for the kernel, including sections for code, data, and uninitialized data.
 * Defines entry point and aligns sections as required for proper execution.
*/

#inlcude <serinix/linker.ld>


OUTPUT_FORMAT("elf32-i386")   // Specifies the output file format as ELF 32-bit for the i386 architecture.
OUTPUT_ARCH("i386")           // Specifies the target architecture as i386.
ENTRY(_start)                 // Sets the entry point of the kernel to the symbol `_start`.

/* Define virtual and physical addresses */
vaddr = PAGE_OFFSET;          // Virtual address where the kernel will be loaded.
paddr = KERNEL_ADDR;          // Physical address, typically 1MB (0x100000) for protected mode kernels.

/* Define the output sections and their properties */
SECTIONS
{
    . = paddr;               // Set the location counter to the starting physical address.

    /* Kernel setup code section */
    .setup ALIGN(4096) :     // Align the `.setup` section to a 4KB boundary.
    {
        *(.setup)           // Include all contents of the `.setup` section.
    }

    . += vaddr;             // Offset the location counter by the virtual address.

    /* Kernel code section */
    .text : AT(ADDR(.text) - vaddr) // Place the `.text` section at an adjusted physical address.
    {
        *(.text)            // Include all contents of the `.text` section.
    }
    _etext = .;             // Define the symbol `_etext` to mark the end of the `.text` section.

    /* Initialized data section */
    .data ALIGN(4096) : AT(ADDR(.data) - vaddr) // Place the `.data` section at an adjusted physical address.
    {
        *(.data)            // Include all contents of the `.data` section.
        *(.rodata*)         // Include all read-only data sections.
    }
    _edata = .;             // Define the symbol `_edata` to mark the end of the `.data` section.

    /* Uninitialized data section */
    .bss ALIGN(4096) : AT(ADDR(.bss) - vaddr) // Place the `.bss` section at an adjusted physical address.
    {
        *(COMMON*)          // Include all common symbols.
        *(.bss*)            // Include all contents of the `.bss` section.
    }
    _end = .;               // Define the symbol `_end` to mark the end of the `.bss` section.

    /* Discard unnecessary sections */
    /DISCARD/ :
    {
        *(.eh_frame)        // Remove exception handling frame information not needed for kernel execution.
    }
}
