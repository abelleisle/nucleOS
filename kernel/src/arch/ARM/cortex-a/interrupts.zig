pub inline fn enable() void {
    asm volatile ("CPSIE I;");
}

pub inline fn disable() void {
    asm volatile ("CPSID I;");
}
