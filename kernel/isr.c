// Definition of all interrupt handlers in vector table

void nmi_handler(void) {
}

void hardfault_handler(void) {
}

void systick_handler(void) {
    proc = get_current_proc();
    proc.ustask = _save_psp();
}
