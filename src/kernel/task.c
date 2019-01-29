#include "task.h"

#include "stdlib.h"

static uint32_t task_pid = 0;

uint32_t* init_task(struct task_t *init, uint32_t stack_size)
{
    init->pid = task_pid++;

    init->stack = (uint32_t*)malloc(stack_size);
    init->sp = init->stack + stack_size - 68; // remove size of stack, and regs
    init->heap = 0; // keep heap clear until needed

    return init->sp;
}
