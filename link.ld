_ram_base = 0x20000000;

MEMORY {
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 16k
    RAM (rwx) : ORIGIN = _ram_base, LENGTH = 12k
}

SECTIONS
{
    _text_base = .;
    .text : { *(.text*) } > ROM
    _text_end = .;

    _data_base = .;
    .data : {
        *(.rodata .rodata.*)
        *(.data .data.*)
    } > RAM AT> ROM
    _data_end = .;

    _bss_base = .;
    .bss : { *(.bss .bss.*) } > RAM
    _bss_end = .;
}
