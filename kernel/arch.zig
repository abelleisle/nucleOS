const currentArch = switch (@import("std").zig.CrossTarget.getCpuArch()) {
    .x86 => @import("arch/x86/x86.zig"),
    else => @panic("CPU Arch not supported"),
};

const init = currentArch.init;
