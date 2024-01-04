const std = @import("std");

/// Generate and build the documents for NucleOS
pub fn build(b: *std.Build) !void {
    // zig fmt: off
    const target = std.zig.CrossTarget{
        .cpu_arch = .thumb,
        .cpu_model = .{ .explicit = &std.Target.arm.cpu.cortex_m4 },
        .os_tag = .freestanding,
        .abi = .eabi
    };
    // zig fmt: on

    const kernel = @import("kernel/build.zig").kernel(b, target);

    const optimize = b.standardOptimizeOption(.{});
    const root_source_file = std.Build.FileSource.relative("./examples/posix_test/main.zig");

    const exe_step = b.step("exe", "Install executable for all targets");

    const exe = b.addExecutable(.{
        .name = "exe",
        .target = target,
        .optimize = optimize,
        .root_source_file = root_source_file,
    });

    exe.addModule("kernel", kernel);

    const exe_install = b.addInstallArtifact(exe, .{});
    exe_step.dependOn(&exe_install.step);

    b.default_step.dependOn(exe_step);
}
