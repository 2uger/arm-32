SECTIONS
{
	 . = 0x0; /* Это флэшка (ROM) */
	.text : {
		start.o(.text)
		main.o(.text) 
	} 
	. = 0x20000000; /* С этого адреса начинается RAM */
	.data : { *(.data) }
	.bss : { *(.bss) }
	. = ALIGN(8);
	. = . + 0x1000; /* Отдаем под стек 4кБ */
	stack_top = .;
}
