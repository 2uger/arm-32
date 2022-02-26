.global activate
activate:
    push {lr}
    ldr r1, =user_space_code
    mov r2, #3
    ldr r3, =0x20002000
    msr PSP, r3
    msr CONTROL, r2
    mov pc, r1

user_space_code:
    ldr r0, =0x41
    ldr r0, =0x0D
    svc #9
    ldr r1, =0x0D
