const arch = @import("arch");

pub fn init() usize {
    return arch.MagicNumber;
}

pub fn log(msg: []const u8) usize {
    return msg.len;
}
