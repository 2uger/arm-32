SECTIONS
{
    /* Load it directly to ram and start executing */
    . = 0x0;
    .text : {
        *(.text .text.*)
    }

    .rodata : {
        *(.rodata*) 
    }
    
    .data : {
        *(.sdata .sdata.*) /* do not need to distinguish this from .data */
        *(.data .data.*)
    }

    .bss : {
        *(.bss .bss.*)
    }
    _kernel_end = .;
}
