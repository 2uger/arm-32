SECTIONS
{
	 . = KERNEL_BASE; /* Это флэшка (ROM) */
	.text : {
        *(.text*)
	} 

    .rodata : {
        . = ALIGN(8);
        *(.rodata*) 
    }
    
    data : {
        . = ALIGN(8);
        *(.sdata .sdata.*) /* do not need to distinguish this from .data */
        . = ALIGN(8);
        *(.data .data.*)
    }

    .bss : {
        . = ALIGN(8);
        *(.bss .bss.*)
    }
}
