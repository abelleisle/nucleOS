const std = @import("std");
const kernel = @import("kernel");

fn callback() void {}

pub fn main() void {
    const magic = kernel.init();
    std.debug.print("Arch magic number: {}", .{magic});

    const log_len = kernel.log("Hello world");
    std.debug.print("Kernel log length: {}", .{log_len});

    const blash = kernel.init();
    _ = blash;

    const t = kernel.Task.Create("Test Task", callback);
    _ = t;
}
