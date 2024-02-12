const std = @import("std");
const builtin = @import("builtin");

const cpu = @import("cpu");
usingnamespace @import("bsp");
usingnamespace @import("boot");

const serial = @import("driver/serial.zig");

export fn kernel_init() noreturn {
    serial.init();
    serial.print("Hello, world!\r\n", .{});

    while (true) {
        // serial.writeByte(serial.readByte());
    }

    hang();
}

pub const std_options = struct {
    pub const log_level = .debug;
    pub const logFn = log;
};

pub const log = serial.log;

pub fn panic(message: []const u8, _: ?*std.builtin.StackTrace, _: ?usize) noreturn {
    std.log.err("!\n! ========================================================= !\n", .{});
    std.log.err("! KERNEL PANIC\n", .{});
    std.log.err("! Reason: {s}\n", .{message});

    hang();
}

fn hang() noreturn {
    while (true) {
        cpu.wait_forever();
    }
}
