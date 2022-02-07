/*
 * Define all memory regions for easy access
 * It's only 12kB of RAM start from 0x2000.0000
 * Kernel -- high 4kB
 * User   -- low 8kB
 */

#define MEM_LOW  0x20001000
#define MEM_HIGH 0x20010000

#define KSPACE_BASE   MEM_HIGH - 0x00001000

#define USPACE_BASE MEM_LOW
