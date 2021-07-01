/*
 * Define all memory regions for easy access
 * It's only 12kB of RAM start from 0x1000.0000
 * Kernel -- high 4kB
 * User   -- low 8kB
 */

#define MEM_LOW 0x10000000
#define MEM_HIGH 0x10003000

#define KSPACE_BASE   MEM_HIGH - 0x00001000

#define USPACE_BASE MEM_LOW
