const arch = @import("arch.zig");
pub const Task = @import("task.zig");

pub fn init() !void {
    Task.init();
}

pub fn start() void {
    while (true) {}
}

pub fn log(msg: []const u8) usize {
    return msg.len;
}

pub fn magic() []const u8 {
    return arch.MagicString;
}
