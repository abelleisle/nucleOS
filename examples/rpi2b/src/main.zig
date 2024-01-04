const uart = @import("driver/uart.zig");
const kernel = @import("kernel");

var main_stack: [1000]u8 = undefined;
fn main_task() void {
    uart.puts("In main_task!\r\n");
    while (true) {}
}

export fn kernel_main(r0: u32, r1: u32, atags: u32) callconv(.C) void {
    _ = r0;
    _ = r1;
    _ = atags;

    uart.init();
    uart.puts("Hello world from kernel!\r\n");

    try kernel.init();

    const msg = kernel.magic();
    uart.puts(msg);

    const mt = kernel.Task.Create("Main Task", main_task, &main_stack);
    _ = mt;

    // while (true) {
    //     uart.putc(uart.getc());
    //     uart.putc('\n');
    // }

    kernel.start();
}
