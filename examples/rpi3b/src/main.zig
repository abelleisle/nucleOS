const std = @import("std");
const builtin = @import("builtin");

const cpu = @import("cpu");
usingnamespace @import("bsp");
usingnamespace @import("boot");

const serial = @import("driver/serial.zig");

export fn kernel_init() noreturn {
    serial.init();
    serial.print("Hello, world!\r\n", .{});

    var x: u8 = 255;
    x += 1;

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
    std.log.err("! ========================================================= !", .{});
    std.log.err("!                       KERNEL PANIC                        !", .{});
    std.log.err("! ========================================================= !", .{});
    std.log.err("Reason: {s}", .{message});

    var index: usize = 0;
    var iter = std.debug.StackIterator.init(@returnAddress(), null);
    while (iter.next()) |address| : (index += 1) {
        if (index == 0) {
            std.log.err("Stack Trace: ", .{});
        }
        std.log.err("{d: >3}: 0x{X:0>8}", .{ index, address });
    }

    if (builtin.mode == .Debug) {
        std.log.info("Attaching to breakpoint..", .{});
        @breakpoint();
    }

    hang();
}

fn hang() noreturn {
    while (true) {
        cpu.wait_forever();
    }
}
