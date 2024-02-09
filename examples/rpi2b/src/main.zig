const uart = @import("driver/uart.zig");
const kernel = @import("kernel");
const timer = @import("driver/timer.zig");

const std = @import("std");

var main_stack: [1000]u8 = std.mem.zeroes([1000]u8);
fn main_task() void {
    while (true) {
        uart.puts("In main_task!\r\n");
        timer.delay(100000000);
        kernel.Task.schedule();
    }
}

var second_stack: [1000]u8 = std.mem.zeroes([1000]u8);
fn second_task() void {
    while (true) {
        uart.puts("In second_task!\r\n");
        timer.delay(100000000);
        kernel.Task.schedule();
    }
}

fn log_callback(msg: []const u8) void {
    uart.puts(msg);
}

export fn rpi_main(r0: u32, r1: u32, atags: u32) callconv(.C) void {
    _ = r0;
    _ = r1;
    _ = atags;

    uart.init();
    uart.puts("Hello world from the kernel!\r\n");

    try kernel.init();
    kernel.logging.init(.debug, &log_callback);
    kernel.logging.log(.info, "Test log\n");

    const msg = kernel.magic();
    uart.puts(msg);

    uart.puts("Creating task!\r\n");
    const mt = kernel.Task.Create("Main Task", main_task, &main_stack);
    // const st = kernel.Task.Create("Second Task", second_task, &second_stack);
    uart.puts("Done creating task!\r\n");

    uart.puts(mt.name);
    // uart.puts(st.name);

    // while (true) {
    //     uart.putc(uart.getc());
    //     uart.putc('\n');
    // }

    // second_task();
    kernel.start();
}

pub fn panic(message: []const u8, stack_trace: ?*std.builtin.StackTrace, size: ?usize) noreturn {
    uart.puts("\n!KERNEL PANIC!\n");
    uart.puts(message);
    uart.puts("\n");
    _ = stack_trace;
    _ = size;
    while (true) {}
}

comptime {
    asm (@embedFile("boot.S"));
}
