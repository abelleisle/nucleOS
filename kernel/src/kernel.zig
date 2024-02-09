const arch = @import("arch.zig");
pub const Task = @import("task.zig");
pub const logging = @import("log.zig");

pub fn init() !void {
    Task.init();
}

pub fn start() void {
    Task.schedule();
    while (true) {}
}

pub fn magic() []const u8 {
    return arch.MagicString;
}
