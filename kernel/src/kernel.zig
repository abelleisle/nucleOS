const arch = @import("arch.zig");
pub const Task = @import("task.zig");

pub fn init() usize {
    return arch.MagicNumber;
}

pub fn log(msg: []const u8) usize {
    return msg.len;
}
