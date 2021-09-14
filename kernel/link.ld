SECTIONS
{
    /* Load it directly to ram and start executing */
    . = 0x0;
    _text_base = .;
    .text : {
        *(.text .text.*)
    }
    _text_end = .;

    . = _ram_base + _text_end;
    .rodata : {
        *(.rodata*) 
    }
    
    .data : {
        *(.sdata .sdata.*) /* do not need to distinguish this from .data */
        *(.data .data.*)
    }

    _bss_base = .;
    .bss : {
        *(.bss .bss.*)
    }
    _bss_end = .;
}
_ram_base = 0x20000000;
