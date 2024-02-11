const std = @import("std");
const builtin = @import("builtin");

const cpu = @import("cpu");
usingnamespace @import("bsp");
usingnamespace @import("boot");

const uart = @import("driver/uart.zig");

export fn kernel_init() noreturn {
    uart.init();
    uart.puts("Hello, world!\r\n");

    while (true) {
        uart.putc(uart.getc());
    }

    hang();
}

pub fn panic(message: []const u8, _: ?*std.builtin.StackTrace, _: ?usize) noreturn {
    uart.puts("!\n! ========================================================= !\n");
    uart.puts("! KERNEL PANIC\n");
    uart.puts("! Reason: ");
    uart.puts(message);

    hang();
}

fn hang() noreturn {
    while (true) {
        cpu.wait_forever();
    }
}
