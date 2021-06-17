/*
 * Define all memory regions for easy access
 * It's only 12kB of RAM start from 0x1000.0000
 * Kernel -- high 4kB
 * User   -- low 8kB
 */

#define MEM_BOUND_LOW 0x1000.0000
#define MEM_BOUND_HIGH 0x1000.2000

#define KERNEL_SPACE_BASE MEM_BOUND_HIGH - 0x0000.0100
#define KERNEL_SPACE_STACK MEM_BOUN_HIGH

#define USER_SPACE_BASE MEM_BOUND_LOW
