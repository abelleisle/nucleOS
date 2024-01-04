/// arch.x86.task.zig
/// Task context information
///  Used to store hardware context information, like the register page
pub const Context = packed struct {
    sp: Address,
    stack: Address,
    stackLen: Address,

    pub fn init(stack: []Address, callback: *const fn () void) Context {
        var sp = stack.len - 1;
        const stack_addr: usize = @intFromPtr(stack.ptr);

        // zig fmt: off
        stack[sp] = (@as(u32, 1) << 24);   sp -= 1; // xPSR
        stack[sp] = @intFromPtr(callback); sp -= 1; // PC
        stack[sp] = 0xE;                   sp -= 1; // LR
        stack[sp] = 0xC;                   sp -= 1; // R12
        stack[sp] = 0x3;                   sp -= 1; // R3
        stack[sp] = 0x2;                   sp -= 1; // R2
        stack[sp] = 0x1;                   sp -= 1; // R1
        stack[sp] = 0x0;                   sp -= 1; // R0
        
        stack[sp] = 0xB;                   sp -= 1; // R11
        stack[sp] = 0xA;                   sp -= 1; // R10
        stack[sp] = 0x9;                   sp -= 1; // R9
        stack[sp] = 0x8;                   sp -= 1; // R8
        stack[sp] = 0x7;                   sp -= 1; // R7
        stack[sp] = 0x6;                   sp -= 1; // R6
        stack[sp] = 0x5;                   sp -= 1; // R5
        stack[sp] = 0x4;                   sp -= 1; // R4

        const c = Context{
            .sp = stack_addr + sp,
            .stack = stack_addr,
            .stackLen = stack.len
        };
        // zig fmt: on

        // Fill the stack with data to avoid memory snooping
        while (sp >= 0) : (sp -= 1) {
            stack[sp] = 0xDEADBEEF;
        }

        return c;
    }
};

pub const PID: type = u32; // ARM PID type
pub const Address: type = u32; // ARM Address size
pub const Register: type = u32; // ARM Register size

const TaskHandle = @import("../../../task.zig").Task;

// zig fmt: off
pub fn do_context_switch(prev_task: *TaskHandle, next_task: *const TaskHandle, lr: Address) callconv(.Inline) void {
    prev_task.context.sp = asm volatile (
        \\mov       r1, %[next]
        \\mov       r2, %[lr]
        \\push      {{r3}}
        \\mrs       r0, PSP
        \\tst       r2, #0x10
        \\it        eq
        \\vstmdbeq  r0!, {{s16-s31}}
        \\mrs       r3, control
        \\stmdb     r0!, {{r2-r11}}
        \\mov       %[prev], r0
        \\ldmia     r1!, {{r2-r11}}
        \\mov       lr, r2
        \\msr       control, r3
        \\tst       lr, #0x10
        \\it        eq
        \\vldmiaeq  r1!, {{s16-s31}}
        \\isb
        \\pop       {{r3}}
        \\msr       psp, r1
        : [prev] "=r" (-> Address)
        : [next] "r" (next_task.context.sp), [lr] "r" (lr)
    );
}
// zig fmt: on
