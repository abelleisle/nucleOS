const std = @import("std");

pub fn kernel(b: *std.Build, target: std.zig.CrossTarget) *std.Build.Module {
    _ = target;
    const kernel_module = b.createModule(.{ .source_file = .{ .path = thisDir() ++ "/src/kernel.zig" } });

    // if (target.cpu_arch) |arch| {
    //     // zig fmt: off
    //     switch (arch) {
    //         .x86 => kernel_module.dependencies.put(
    //             "arch", b.createModule(
    //                 .{ .source_file = .{ .path = thisDir() ++ "/arch/x86/x86.zig" } })
    //             ) catch @panic("OOM"),
    //         else => @panic("Unsupported target"),
    //     }
    //     // zig fmt: on
    // } else {
    //     @panic("Target CPU architecture required");
    // }

    return kernel_module;
}

inline fn thisDir() []const u8 {
    return comptime std.fs.path.dirname(@src().file) orelse ".";
}
