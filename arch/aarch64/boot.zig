const std = @import("std");

// zig fmt: off
// const bootasm = std.fmt.comptimePrint(
//     @embedFile("boot.s"),
//               // CONST_CORE_ID_MASK, core mask that designates how many cores
//               // our system has.
//     .{"0b11"} // instruction: and x0, x0, {s}
// );
// zig fmt: on

comptime {
    asm (@embedFile("boot.s"));
}

extern fn kernel_init() void;

export fn _start_zig() void {
    kernel_init();
}
