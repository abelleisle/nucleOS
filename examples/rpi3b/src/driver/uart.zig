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
    GPPUD        : u32,
    GPPUDCLK0    : u32,
};

const UART_regs = extern struct {
    DR        : u32,
    RSR       : u32,
    reserved24: [16]u8,
    FR        : u32,
    reserved32: [4]u8,
    ILPR      : u32,
    IBRD      : u32,
    FBRD      : u32,
    LCRH      : u32,
    CR        : u32,
    IFLS      : u32,
    IMSC      : u32,
    RIS       : u32,
    MIS       : u32,
    ICR       : u32,
    DMACR     : u32,
    reserved52: [52]u8,
    ITCR      : u32,
    ITIP      : u32,
    ITOP      : u32,
    TDR       : u32,
};

pub const UART0 = @as(*volatile UART_regs, @ptrFromInt(0x3F201000));
pub const UART1 = @as(*volatile UART_regs, @ptrFromInt(0x3F201000));
pub const GPIO  = @as(*volatile GPIO_regs, @ptrFromInt(0x3F200000));
// pub const GPIO = GPIO_Inst(0x3F200000);

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

        mmio.write(u_regs.CR, 0x00000000);

        mmio.write(g_regs.GPPUD, 0x00000000);
        timer.delay(150);

        mmio.write(g_regs.GPPUDCLK0, (1 << 14) | (1 << 15));
        timer.delay(150);

        mmio.write(g_regs.GPPUDCLK0, 0x00000000);

        mmio.write(u_regs.ICR, 0x7FF);

        mmio.write(u_regs.IBRD, 1);
        mmio.write(u_regs.FBRD, 40);

        mmio.write(u_regs.LCRH, (1 << 4) | (1 << 5) | (1 << 6));

        mmio.write(u_regs.IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

        mmio.write(u_regs.CR, (1 << 0) | (1 << 8) | (1 << 9));
    }

    pub fn putc(uart: UART, char: u8) void {
        const r = uart.uart_regs();
        while ((mmio.read(r.FR) & (1 << 5)) != 0) {}
        mmio.write(r.DR, char);
    }

    pub fn getc(uart: UART) u8 {
        const r = uart.uart_regs();
        while ((mmio.read(r.FR) & (1 << 4)) != 0) {}
        return @intCast(mmio.read(r.DR));
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
