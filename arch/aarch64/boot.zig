export const CONST_CORE_ID_MASK = 0b11;
comptime {
    asm (@embedFile("boot.s"));
}

export fn _start_zig() void {
    kernel_init();
}
