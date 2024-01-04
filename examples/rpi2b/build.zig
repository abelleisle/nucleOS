const std = @import("std");

const Target = .{
    .cpu_arch = std.Target.Cpu.Arch.arm,
    .cpu_model = std.zig.CrossTarget.CpuModel{ .explicit = &std.Target.arm.cpu.cortex_a7 },
    .cpu_features_add = std.Target.arm.cpu.cortex_a5.features,
    .os_tag = std.Target.Os.Tag.freestanding,
    .abi = std.Target.Abi.gnueabi,
};

pub fn build(b: *std.Build, kernel: *std.Build.Module, comptime name: []const u8) !void {
    // const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const elf = b.addExecutable(.{
        .name = name,
        // In this case the main source file is merely a path, however, in more
        // complicated build scripts, this could be a generated file.
        .root_source_file = .{ .path = thisDir() ++ "src/main.zig" },
        .target = Target,
        .optimize = optimize,
    });
    elf.setLinkerScript(.{ .path = thisDir() ++ "ld/linker.ld" });
    elf.addAssemblyFile(.{ .path = thisDir() ++ "src/boot.S" });
    elf.addModule("kernel", kernel);
    const install_step = b.step(name, "Build rpi-os demo");
    install_step.dependOn(&b.addInstallArtifact(elf, .{}).step);

    try qemu(b, elf, name);
}

fn qemu(b: *std.Build, executable: *std.Build.Step.Compile, comptime name: []const u8) !void {
    const want_gdb = b.option(bool, "gdb", "Build for using gdb with qemu") orelse false;
    const want_pty = b.option(bool, "pty", "Create a separate TTY path") orelse false;
    const want_display = b.option(bool, "display", "Use display for qemu") orelse false;

    var qemu_args = std.ArrayList([]const u8).init(b.allocator);
    defer qemu_args.deinit();
    try qemu_args.appendSlice(&[_][]const u8{
        "qemu-system-arm",
        "-m",
        "1G",
        "-M",
        "raspi2b",
        "-serial",
        if (want_pty) "pty" else "stdio",
        "-display",
        if (want_display) "gtk" else "none",
    });
    if (want_gdb) {
        try qemu_args.appendSlice(&[_][]const u8{ "-S", "-s" });
    }

    const run_qemu = b.addSystemCommand(try qemu_args.toOwnedSlice());
    run_qemu.step.dependOn(&executable.step);

    run_qemu.addArgs(&[_][]const u8{
        "-kernel",
    });
    run_qemu.addFileArg(executable.getEmittedBin());

    const qemu_step = b.step(name ++ "-qemu", "Simulate the OS in qemu");
    qemu_step.dependOn(&run_qemu.step);

    // const optimize = b.standardOptimizeOption(.{});
    // const unit_tests = b.addTest(.{
    //     .root_source_file = .{ .path = "src/main.zig" },
    //     .target = Target,
    //     .optimize = optimize,
    // });
    // const run_unit_tests = b.addRunArtifact(unit_tests);
    // const test_step = b.step("test", "Run unit tests");
    // test_step.dependOn(&run_unit_tests.step);
}

inline fn thisDir() []const u8 {
    return comptime (std.fs.path.dirname(@src().file) orelse ".") ++ "/";
}
