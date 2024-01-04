const uart = @import("driver/uart.zig");
const kernel = @import("kernel");

export fn kernel_main(r0: u32, r1: u32, atags: u32) callconv(.C) void {
    _ = r0;
    _ = r1;
    _ = atags;

    uart.init();
    uart.puts("Hello world from kernel!\r\n");

    try kernel.init();

    const msg = kernel.magic();
    uart.puts(msg);

    while (true) {
        uart.putc(uart.getc());
        uart.putc('\n');
    }
}
