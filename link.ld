MEMORY {
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 16k
    KRAM (rwx) : ORIGIN = _kernel_base, LENGTH = 12k
}

SECTIONS
{
    /* Load it directly to ram and start executing */
    . = 0x0;
    .reset : {
        *entry.o (.text)
        . = ALIGN(0x4);
    } > ROM

    
    _text_base = .;
    .text : {
        *(.text*)
    } > KRAM
    _text_end = .;

    .rodata : {
        *(.rodata*) 
    } > KRAM
    
    _data_base = .;
    .data : {
        *(.sdata .sdata.*) /* do not need to distinguish this from .data */
        *(.data .data.*)
    } > KRAM
    _data_end = .;

    _bss_base = .;
    .bss : {
        *(.bss .bss.*)
    } > KRAM
    _bss_end = .;
}
_ram_base = 0x20000000;
_kernel_base = 0x20005000;
