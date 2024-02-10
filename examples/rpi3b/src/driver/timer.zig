pub inline fn delay(count: i32) void {
    var dec = count;
    while (dec >= 0) : (dec -= 1) {
        asm volatile ("nop");
    }
}
