.syntax unified

.global call_svc
call_svc:
    mov r2, #2
    svc #7
    bx lr

.data
_svc: .asciz "SVC handler\n"

.text
.global svc_handler
.type svc_handler, %function
svc_handler:
    push {lr}
    ldr r0, =_svc
    bl kprintf

    bl get_current_active_thread
    bl save_ctx

    bl syscall
    pop {pc}

.data
_systick: .asciz "Systick handler\n"

.text
.global systick_handler
.type systick_handler, %function
systick_handler:
    push {lr}
    ldr r0, =_systick
    bl kprintf

    bl get_current_active_thread
    bl save_ctx 

    bl get_next_unused_thread
    bl set_active_thread
    pop {r10}
    bl swtch

    pop {pc}

.data
_pendsv: .asciz "PENDSV handler\n"

.text
.global pendsv_handler
.type pendsv_handler, %function
pendsv_handler:
    push {lr}
    ldr r0, =_pendsv
    bl kprintf
    pop {pc}

.data
_default: .asciz "DEFAULT handler\n"

.text
.global default_handler
.type default_handler, %function
default_handler:
    push {lr}
    ldr r0, =_default
    bl kprintf
    pop {pc}