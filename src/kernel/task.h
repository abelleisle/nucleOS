#ifndef TASK_H
#define TASK_H

#include "stdint.h"

struct task_t {
    uint32_t *sp; /**< Last value of stack pointer for this stack. */
    uint32_t *stack; /**< Location of the stack of this task. */
    uint32_t *heap; /**< Location of heap for this task. */

    uint32_t pid; /**< Process I.D. */
};

uint32_t* init_task(struct task_t *init, uint32_t stack_size);

#endif // TASK_H
