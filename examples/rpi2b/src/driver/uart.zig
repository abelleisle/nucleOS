const mmio = @import("../mem/mmio.zig");
const timer = @import("../driver/timer.zig");

pub fn GPIO_Inst(comptime base: u32) type {
    const rtype = @TypeOf(base);
    return struct {
        const regs = struct {
            const BASE: rtype = base;
            const GPPUD: rtype = (base + 0x94);
            const GPPUDCLK0: rtype = (base + 0x98);
        };
    };
}

pub fn UART_Inst(comptime uart: u32) type {
    const rtype = @TypeOf(uart);
    return struct {
        const regs = struct {
            const BASE: rtype = uart;
            const DR: rtype = (uart + 0x00);
            const RSRECR: rtype = (uart + 0x04);
            const FR: rtype = (uart + 0x18);
            const ILPR: rtype = (uart + 0x20);
            const IBRD: rtype = (uart + 0x24);
            const FBRD: rtype = (uart + 0x28);
            const LCRH: rtype = (uart + 0x2C);
            const CR: rtype = (uart + 0x30);
            const IFLS: rtype = (uart + 0x34);
            const IMSC: rtype = (uart + 0x38);
            const RIS: rtype = (uart + 0x3C);
            const MIS: rtype = (uart + 0x40);
            const ICR: rtype = (uart + 0x44);
            const DMACR: rtype = (uart + 0x48);
            const ITCR: rtype = (uart + 0x80);
            const ITIP: rtype = (uart + 0x84);
            const ITOP: rtype = (uart + 0x88);
            const TDR: rtype = (uart + 0x8C);
        };
    };
}

pub const UART0 = UART_Inst(0x3F201000);
pub const GPIO = GPIO_Inst(0x3F200000);

pub fn init() void {
    mmio.write(UART0.regs.CR, 0x00000000);

    mmio.write(GPIO.regs.GPPUD, 0x00000000);
    timer.delay(150);

    mmio.write(GPIO.regs.GPPUDCLK0, (1 << 14) | (1 << 15));
    timer.delay(150);

    mmio.write(GPIO.regs.GPPUDCLK0, 0x00000000);

    mmio.write(UART0.regs.ICR, 0x7FF);

    mmio.write(UART0.regs.IBRD, 1);
    mmio.write(UART0.regs.FBRD, 40);

    mmio.write(UART0.regs.LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    mmio.write(UART0.regs.IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
        (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    mmio.write(UART0.regs.CR, (1 << 0) | (1 << 8) | (1 << 9));
}

pub fn putc(char: u8) void {
    while ((mmio.read(UART0.regs.FR) & (1 << 5)) != 0) {}
    mmio.write(UART0.regs.DR, char);
}

pub fn getc() u8 {
    while ((mmio.read(UART0.regs.FR) & (1 << 4)) != 0) {}
    return @intCast(mmio.read(UART0.regs.DR));
}

pub fn puts(str: []const u8) void {
    for (str) |c| {
        putc(c);
    }
}
