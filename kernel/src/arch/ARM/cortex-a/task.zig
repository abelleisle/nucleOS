const builtin = @import("builtin");

pub const PID: type = u32;

pub const Context = struct {
    r0: u32,
    r1: u32,
    r2: u32,
    r3: u32,
    r4: u32,
    r5: u32,
    r6: u32,
    r7: u32,
    r8: u32,
    r9: u32,
    r10: u32,
    r11: u32,
    cpsr: u32,
    sp: u32,
    lr: u32,

    pub fn init(callback: *const fn () void, stack: []u8) *Context {
        const context_start = @intFromPtr(stack.ptr) + stack.len - @sizeOf(Context);

        var ctx: *Context = @ptrFromInt(context_start);

        const reap = @import("../../../task.zig").reap;
        const reap_ptr = &reap;

        ctx.r0 = 0x00000000;
        ctx.r1 = 0x11111111;
        ctx.r2 = 0x22222222;
        ctx.r3 = 0x33333333;
        ctx.r4 = 0x44444444;
        ctx.r5 = 0x55555555;
        ctx.r6 = 0x66666666;
        ctx.r7 = 0x77777777;
        ctx.r8 = 0x88888888;
        ctx.r9 = 0x99999999;
        ctx.r10 = 0xAAAAAAAA;
        ctx.r11 = 0xBBBBBBBB;
        ctx.cpsr = 0x13 | (8 << 1); // Run in supervisor mode with irqs only
        ctx.sp = @intFromPtr(reap_ptr);
        ctx.lr = @intFromPtr(callback);

        return ctx;
    }
};

extern fn switch_to_thread(old: u32, new: u32) void;

comptime {
    if (builtin.cpu.arch.isThumb()) {
        asm (
            \\.global switch_to_thread
            \\
            \\// void switch_to_thread(process_control_block_t * old, process_control_block_t * new)
            \\// takes old thread off cpu and puts new thread on.
            \\// Old thread should be put back in run queue before this is called
            \\switch_to_thread:
            \\    // Save the current thread's state
            \\    push    {lr}     // Push stack pointer and link register
            \\    push    {sp}
            \\    mrs     r12, cpsr   // Get the current program state register
            \\    push    {r0-r12}    // Save all general purpose registers and program state
            \\    str     sp, [r0]    // Store the stack pointer into the saved_state field of the current process
            \\    // Restore the new thread's state
            \\    ldr     sp, [r1]    // Load the stack pointer of the new process
            // \\    ldr     r0, =#(10000)// Set Quantum time to 10 ms (10000 us)
            // \\    bl      timer_set   // reset the timer to go off in another quantum
            \\    pop     {r0-r12}    // restore the general purpose registers
            \\    msr     cpsr_c, r12   // Restore the new thread's program status register
            // \\    pop     {lr, pc}    // we have no idea what lr should be, so just give it a garbage value. pc gets the stored lr so this function returns to there
            \\    pop     {lr}    // we have no idea what lr should be, so just give it a garbage value. pc gets the stored lr so this function returns to there
            \\    pop     {pc}    // we have no idea what lr should be, so just give it a garbage value. pc gets the stored lr so this function returns to there
            // \\    bx      lr
        );
    } else if (builtin.cpu.arch.isARM()) {
        asm (
            \\.global switch_to_thread
            \\
            \\// void switch_to_thread(process_control_block_t * old, process_control_block_t * new)
            \\// takes old thread off cpu and puts new thread on.
            \\// Old thread should be put back in run queue before this is called
            \\switch_to_thread:
            \\    // Save the current thread's state
            \\    push    {lr}     // Push stack pointer and link register
            \\    push    {sp}
            \\    mrs     r12, cpsr   // Get the current program state register
            \\    push    {r0-r12}    // Save all general purpose registers and program state
            \\    str     sp, [r0]    // Store the stack pointer into the saved_state field of the current process
            \\    // Restore the new thread's state
            \\    ldr     sp, [r1]    // Load the stack pointer of the new process
            // \\    ldr     r0, =#(10000)// Set Quantum time to 10 ms (10000 us)
            // \\    bl      timer_set   // reset the timer to go off in another quantum
            \\    pop     {r0-r12}    // restore the general purpose registers
            \\    msr     cpsr_c, r12   // Restore the new thread's program status register
            // \\    pop     {lr, pc}    // we have no idea what lr should be, so just give it a garbage value. pc gets the stored lr so this function returns to there
            \\    pop     {lr}    // we have no idea what lr should be, so just give it a garbage value. pc gets the stored lr so this function returns to there
            \\    pop     {pc}    // we have no idea what lr should be, so just give it a garbage value. pc gets the stored lr so this function returns to there
            // \\    bx      lr
        );
    } else {
        @compileError("`switch_to_thread` not defined for this ISA");
    }
}
