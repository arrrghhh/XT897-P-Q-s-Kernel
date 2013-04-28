#ifndef _ASMARM_BUG_H
#define _ASMARM_BUG_H


#ifdef CONFIG_BUG

/*
 * Use a suitable undefined instruction to use for ARM/Thumb2 bug handling.
 * We need to be careful not to conflict with those used by other modules and
 * the register_undef_hook() system.
 */
#ifdef CONFIG_THUMB2_KERNEL
#define BUG_INSTR_VALUE 0xde02
#define BUG_INSTR_TYPE ".hword "
#else
#define BUG_INSTR_VALUE 0xe7f001f2
#define BUG_INSTR_TYPE ".word "
#endif


#ifdef CONFIG_DEBUG_BUGVERBOSE

extern void __bug(const char *file, int line) __attribute__((noreturn));

/* give file/line information */
#define BUG()		__bug(__FILE__, __LINE__)

#else

/* this just causes an oops */
#define BUG() do { *(volatile int *)0 = 0; } while (1)

#endif

#define HAVE_ARCH_BUG
#endif  /* CONFIG_BUG */

#include <asm-generic/bug.h>

#endif
