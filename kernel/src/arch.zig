const std = @import("std");
const builtin = @import("builtin");
const crosstarget = builtin.cpu.arch;
const crossmodel = builtin.cpu.model;

pub usingnamespace switch (crosstarget) {
    .arm, .thumb => switch (crossmodel) {
        &std.Target.arm.cpu.cortex_m4 => @import("arch/ARM/cortex-m/arm.zig"),
        &std.Target.arm.cpu.cortex_a7 => @import("arch/ARM/cortex-a/arm.zig"),
        else => @compileError("NucleOS doesn't support that specific thumb model.."),
    },
    .x86_64 => @import("arch/x86/x86.zig"),
    else => @compileError("NucleOS not yet supported by this platform"),
};
