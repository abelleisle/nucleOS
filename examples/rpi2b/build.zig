const std = @import("std");

pub fn build(b: *std.Build) !void {
    const want_gdb = b.option(bool, "gdb", "Build for using gdb with qemu") orelse false;
    const want_pty = b.option(bool, "pty", "Create a separate TTY path") orelse false;
    const want_display = b.option(bool, "display", "Use display for qemu") orelse false;

    // const target = b.standardTargetOptions(.{});
    const target = .{
        .cpu_arch = std.Target.Cpu.Arch.arm,
        .cpu_model = std.zig.CrossTarget.CpuModel{ .explicit = &std.Target.arm.cpu.cortex_a7 },
        .cpu_features_add = std.Target.arm.cpu.cortex_a5.features,
        .os_tag = std.Target.Os.Tag.freestanding,
        .abi = std.Target.Abi.gnueabi,
    };
    const optimize = b.standardOptimizeOption(.{});

    const elf = b.addExecutable(.{
        .name = "rpi-os",
        // In this case the main source file is merely a path, however, in more
        // complicated build scripts, this could be a generated file.
        .root_source_file = .{ .path = "src/kernel.zig" },
        .target = target,
        .optimize = optimize,
    });
    elf.setLinkerScript(.{ .path = "ld/linker.ld" });
    elf.addAssemblyFile(.{ .path = "src/boot.S" });
    b.installArtifact(elf);

    // const run_cmd = b.addRunArtifact(exe);
    // run_cmd.step.dependOn(b.getInstallStep());
    // if (b.args) |args| {
    //     run_cmd.addArgs(args);
    // }
    // const run_step = b.step("run", "Run the app");
    // run_step.dependOn(&run_cmd.step);

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
    run_qemu.step.dependOn(&elf.step);

    run_qemu.addArgs(&[_][]const u8{
        "-kernel",
        // elf.getEmittedBin().generated.getPath(),
        "zig-out/bin/rpi-os",
    });

    const qemu = b.step("qemu", "Simulate the OS in qemu");
    qemu.dependOn(&run_qemu.step);

    const unit_tests = b.addTest(.{
        .root_source_file = .{ .path = "src/main.zig" },
        .target = target,
        .optimize = optimize,
    });
    const run_unit_tests = b.addRunArtifact(unit_tests);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_unit_tests.step);
}
