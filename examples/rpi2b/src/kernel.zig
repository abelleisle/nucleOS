const uart = @import("driver/uart.zig");

export fn kernel_main(r0: u32, r1: u32, atags: u32) callconv(.C) void {
    _ = r0;
    _ = r1;
    _ = atags;

    uart.init();
    uart.puts("Hello world from kernel!\r\n");

    while (true) {
        uart.putc(uart.getc());
        uart.putc('\n');
    }
}
