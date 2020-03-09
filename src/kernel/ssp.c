#include <stdint.h>
#include <stdlib.h>
 
#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xa7e93bd3
#else
#define STACK_CHK_GUARD 0x0e5bf4cd7cdba3ef
#endif
 
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn))
void abort()
{
    while (1);
}
 
__attribute__((noreturn))
void __stack_chk_fail(void)
{
#if __STDC_HOSTED__
    abort();
#elif __is_myos_kernel
    panic("Stack smashing detected");
#endif
}
