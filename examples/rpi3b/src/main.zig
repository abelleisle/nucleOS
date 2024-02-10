const std = @import("std");

const cpu = @import("cpu");
usingnamespace @import("bsp");
usingnamespace @import("boot");

const uart = @import("driver/uart.zig");

export fn kernel_init() void {
    uart.init();
    uart.puts("Hello, world!\r\n");

    while (true) {
        uart.putc(uart.getc());
    }
}

pub fn panic(message: []const u8, stack_trace: ?*std.builtin.StackTrace, size: ?usize) noreturn {
    _ = size;
    _ = stack_trace;
    _ = message;
    while (true) {
        cpu.wait_forever();
    }
}
