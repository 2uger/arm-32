.syntax unified

.global call_svc
call_svc:
    svc #7
    bx lr

.data
_svc: .asciz "\nSVC handler\n"

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
    bl get_current_active_thread
    pop {r10}
    bl swtch

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
    mov r3, r0
    bl save_ctx 
    mov r0, r3
    bl print_thread_info

    bl get_next_unused_thread
    bl set_active_thread
    pop {r10}
    bl swtch

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