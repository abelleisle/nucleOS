const std = @import("std");

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

// zig fmt: off
const GPIO_regs = extern struct {
    reserved_base: [148]u8,
    GPPUD        : mmio.Mmio(u32),
    GPPUDCLK0    : mmio.Mmio(u32),
};

const UART_regs = extern struct {
    DR        : mmio.Mmio(u32),
    RSR       : mmio.Mmio(u32),
    reserved24: [16]u8,
    FR        : mmio.Mmio(u32),
    reserved32: [4]u8,
    ILPR      : mmio.Mmio(u32),
    IBRD      : mmio.Mmio(u32),
    FBRD      : mmio.Mmio(u32),
    LCRH      : mmio.Mmio(u32),
    CR        : mmio.Mmio(u32),
    IFLS      : mmio.Mmio(u32),
    IMSC      : mmio.Mmio(u32),
    RIS       : mmio.Mmio(u32),
    MIS       : mmio.Mmio(u32),
    ICR       : mmio.Mmio(u32),
    DMACR     : mmio.Mmio(u32),
    reserved52: [52]u8,
    ITCR      : mmio.Mmio(u32),
    ITIP      : mmio.Mmio(u32),
    ITOP      : mmio.Mmio(u32),
    TDR       : mmio.Mmio(u32),
};

pub const UART0 = @as(*volatile UART_regs, @ptrFromInt(0x3F201000));
pub const UART1 = @as(*volatile UART_regs, @ptrFromInt(0x3F201000));
pub const GPIO  = @as(*volatile GPIO_regs, @ptrFromInt(0x3F200000));
// zig fmt: on

pub fn num(n: u1) UART {
    return @as(UART, @enumFromInt(n));
}

pub const UART = enum(u1) {
    _, // Dummy field for our enum

    const WriteError = error{};
    const ReadError = error{};
    pub const Writer = std.io.Writer(UART, WriteError, write);
    // pub const Reader = std.io.Reader(UART, ReadError, gets);

    pub fn writer(uart: UART) Writer {
        return .{ .context = uart };
    }

    fn uart_regs(uart: UART) *volatile UART_regs {
        return switch (@intFromEnum(uart)) {
            0 => UART0,
            1 => UART1,
        };
    }

    pub fn init(uart: UART) void {
        const u_regs = uart.uart_regs();
        const g_regs = GPIO;

        u_regs.CR.write(0x00000000);

        g_regs.GPPUD.write(0x00000000);
        timer.delay(150);

        g_regs.GPPUDCLK0.write((1 << 14) | (1 << 15));
        timer.delay(150);

        g_regs.GPPUDCLK0.write(0x00000000);

        u_regs.ICR.write(0x7FF);

        u_regs.IBRD.write(1);
        u_regs.FBRD.write(40);

        u_regs.LCRH.write((1 << 4) | (1 << 5) | (1 << 6));

        u_regs.IMSC.write((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

        u_regs.CR.write((1 << 0) | (1 << 8) | (1 << 9));
    }

    pub fn putc(uart: UART, char: u8) void {
        const r = uart.uart_regs();
        while ((r.FR.read() & (1 << 5)) != 0) {}
        r.DR.write(char);
    }

    pub fn getc(uart: UART) u8 {
        const r = uart.uart_regs();
        while ((r.FR.read() & (1 << 4)) != 0) {}
        return @intCast(r.DR.read());
    }

    pub fn puts(uart: UART, str: []const u8) void {
        for (str) |c| {
            putc(uart, c);
        }
    }

    pub fn write(uart: UART, payload: []const u8) WriteError!usize {
        puts(uart, payload);
        return payload.len;
    }
};
