SECTIONS
{
    /* Load it directly to ram and start executing */
	 . = 0x20000000;
    _kernel_start = .;
	.text : {
        *(.text .text.*)
	} 

    .rodata : {
        *(.rodata*) 
    }
    
    .data : {
        . = ALIGN(4);
        *(.sdata .sdata.*) /* do not need to distinguish this from .data */
        . = ALIGN(4);
        *(.data .data.*)
    }

    .bss : {
        . = ALIGN(4);
        *(.bss .bss.*)
    }
    _kernel_end = .;
}
