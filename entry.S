kernel_vector:
    .word 0x20002000   // Stack pointer
    .word entry       // entry point
    .word default_handler
    .word default_handler 
    .word default_handler 
    .word default_handler 
    .word default_handler 
    .word default_handler 
    .word default_handler 
    .word default_handler 
    .word default_handler 
    .word svc_handler 
    .word default_handler 
    .word default_handler 
    .word default_handler 
    .word systick_handler 

.type entry, %function
entry:
    bl cp_data2ram
    bl zero_bss
    bl timerinit
    bl init_thread_pool
    bl scheduler

cp_data2ram:
    .extern _data_base
    .extern _ram_base
    .extern _bss_base
    ldr r0, =_data_base
    ldr r1, =_ram_base
    ldr r2, =_bss_base
    cmp r1, r2
    blt cp_loop
    mov pc, r14
cp_loop:
    ldr r3, [r0]
    str r3, [r1]
    add r0, r0, #0x4
    add r1, r1, #0x4
    cmp r1, r2
    blt cp_loop
    mov pc, r14 

zero_bss:
    .extern _bss_base
    .extern _bss_end
    ldr r0, =_bss_base
    ldr r1, =_bss_end
    cmp r0, r1
    blt zero_bss_loop
    mov pc, r14
zero_bss_loop:
    mov r3, #0x0
    str r3, [r0]
    add r0, r0, #0x4
    cmp r0, r1
    blt zero_bss_loop
    mov pc, r14
