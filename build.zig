const std = @import("std");

/// Generate and build the documents for NucleOS
pub fn build(b: *std.Build) !void {
    const target = .{ .cpu_arch = .x86, .os_tag = .linux };

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
