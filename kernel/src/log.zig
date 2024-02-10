const std = @import("std");

const Level = enum(u8) {
    none = 0, // This is reserved for no logging at all
    severe = 1,
    err = 2,
    warning = 3,
    info = 4,
    debug = 5,
};

var logCallback: ?*const fn ([]const u8) void = null;
var logLevel: Level = .none;

pub fn init(comptime level: Level, log_callback: *const fn ([]const u8) void) void {
    logLevel = level;
    logCallback = log_callback;
}

pub fn log(comptime level: Level, msg: []const u8) void {
    if (logCallback) |cb| {
        if ((logLevel != .none) and (@intFromEnum(level) <= @intFromEnum(logLevel))) {
            cb(msg);
        }
    }
}
