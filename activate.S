.global activate
activate:
    // r0 - pointer to Thread structure
    push {lr}
    ldr r1, [r0, #8] // sp 
    ldr r2, [r0, #12] // pc
    mov r3, #3
    msr PSP, r1
    msr CONTROL, r3
    mov pc, r2

.global user_space_code
user_space_code:
    mov r0, #0x41
    svc #9

.data
to_print_addr:
    .word to_print

.data
to_print:
    .word 'o'
    .word 'l'
    .word 'e'
    .word 'g'
    .word '\n'
