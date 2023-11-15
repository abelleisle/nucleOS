const std = @import("std");
const kernel = @import("kernel");

pub fn main() void {
    const magic = kernel.init();
    std.debug.print("Arch magic number: {}", .{magic});

    const log_len = kernel.log("Hello world");
    std.debug.print("Kernel log length: {}", .{log_len});
}
