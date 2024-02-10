inline fn wait_forever() void {
    while (true) {
        asm volatile ("wfe");
    }
}
