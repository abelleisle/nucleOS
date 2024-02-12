// Me
const serial = @This();

// Global includes
const std = @import("std");
const fmt = std.fmt;

// Driver includes
const uart = @import("uart.zig");

var uart_instance: ?uart.UART = null;
var uart_logger: ?uart.UART.Writer = null;

pub fn init() void {
    uart_instance = uart.num(0);
    if (uart_instance) |u| {
        u.init();
        uart_logger = u.writer();
    }
}

pub fn print(comptime format: []const u8, args: anytype) void {
    if (uart_logger) |u| {
        u.print(format, args) catch {};
    }
}

// This overrides the logging for std.log
// zig fmt: off
pub fn log(
    comptime level: std.log.Level,
    comptime scope: @Type(.EnumLiteral),
    comptime format: []const u8,
    args: anytype
) void {
    const level_prefix = comptime "[{}.{:0>6}] " ++ level.asText();
    const prefix = comptime level_prefix ++ switch (scope) {
        .default => ": ",
        else => " (" ++ @tagName(scope) ++ "): ",
    };

    if (uart_logger) |u| {
        // const current_time = time.get_time_since_boot();
        // const seconds = current_time.to_us() / std.time.us_per_s;
        // const microseconds = current_time.to_us() % std.time.us_per_s;
        const seconds = 0;
        const microseconds = 0;

        u.print(prefix ++ format ++ "\r\n", .{ seconds, microseconds } ++ args) catch {};
    }
}
// zig fmt: on
