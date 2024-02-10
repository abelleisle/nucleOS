const std = @import("std");

/// Generate and build the documents for NucleOS
pub fn build(b: *std.Build) !void {
    // // zig fmt: off
    // const target = .{
    //     .cpu_arch = std.Target.Cpu.Arch.arm,
    //     .cpu_model = std.zig.CrossTarget.CpuModel{ .explicit = &std.Target.arm.cpu.cortex_a7 },
    //     .cpu_features_add = std.Target.arm.cpu.cortex_a5.features,
    //     .os_tag = std.Target.Os.Tag.freestanding,
    //     .abi = std.Target.Abi.gnueabi,
    // };
    // const optimize = b.standardOptimizeOption(.{});
    // // zig fmt: on
    //
    const kernel = @import("kernel/build.zig").kernel(b);
    //
    // const root_source_file = std.Build.FileSource.relative("./examples/posix_test/main.zig");
    //
    // const exe_step = b.step("exe", "Install executable for all targets");
    //
    // const exe = b.addExecutable(.{
    //     .name = "exe",
    //     .target = target,
    //     .optimize = optimize,
    //     .root_source_file = root_source_file,
    // });

    // exe.addModule("kernel", kernel);

    // const exe_install = b.addInstallArtifact(exe, .{});
    // exe_step.dependOn(&exe_install.step);
    //
    // b.default_step.dependOn(exe_step);

    const example_rpi2 = @import("examples/rpi3b/build.zig");
    try example_rpi2.build(b, kernel, "rpi3b");
}

fn install(b: *std.Build, exe: *std.Build.CompileStep, comptime name: []const u8) void {
    const install_step = b.step(name, "Build '" ++ name ++ "' demo");
    install_step.dependOn(&b.addInstallArtifact(exe, .{}).step);

    const run_step = b.step(name ++ "-run", "Run '" ++ name ++ "' demo");
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(install_step);
    run_step.dependOn(&run_cmd.step);

    b.getInstallStep().dependOn(install_step);
}
