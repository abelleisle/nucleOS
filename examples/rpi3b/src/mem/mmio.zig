const std = @import("std");
const assert = std.debug.assert;

/// Create a memory-mapped IO instance that can be used to read/write data
/// to memory-mapped IO registers.
///
/// The data stored as this address can be stored using a type `packedT`.
/// An example of using MMIO is as follows with GPIO_registers:
/// const GPIO_regs = extern struct {
///     GPPUD        : mmio.Mmio(u32),
///     GPPUDCLK0    : mmio.Mmio(u32),
/// };
/// pub const GPIO  = @as(*volatile GPIO_regs, @ptrFromInt(0x3F200000));
///
/// const ud = GPIO.GPPUD.read();
/// GPIO.GPPUD.write(0x44);
pub fn Mmio(comptime packedT: type) type {
    const size = @bitSizeOf(packedT);

    if ((size % 8) != 0) @compileError("packedT must be sized by 8-bits");
    if (!std.math.isPowerOfTwo(size / 8)) @compileError("packedT must be a valid address size (8,16,32,64,etc)..");

    const intT = std.meta.Int(.unsigned, size);
    if (@sizeOf(intT) != (size / 8))
        @compileError(std.fmt.comptimePrint("intT and packedT must be the same size. They are sized {} and {} respectively.", .{ @sizeOf(intT), (size / 8) }));

    // This is the actual struct we're using as the MMIO instance.
    // Notice that the only field is `raw`. This means that the size of the
    // struct is exactly equal to the size of the data it references.
    return extern struct {
        const mmio = @This();

        raw: intT,
        pub const rawT = packedT;

        /// Read data from referenced memory address.
        pub inline fn read(addr: *volatile mmio) rawT {
            return @bitCast(addr.raw);
        }

        /// Write data to referenced memory address.
        /// Will check against sizing for safety.
        pub inline fn write(addr: *volatile mmio, val: rawT) void {
            comptime {
                assert(@bitSizeOf(rawT) == @bitSizeOf(intT));
            }
            addr.write_raw(@bitCast(val));
        }

        /// Directly write to the referenced memory address
        pub inline fn write_raw(addr: *volatile mmio, val: intT) void {
            addr.raw = val;
        }

        /// Write provided field values to the memory data referenced
        /// by this mmio instance.
        pub inline fn modify(addr: *volatile mmio, fields: anytype) void {
            var val = mmio.read(addr);
            inline for (@typeInfo(@TypeOf(fields)).Struct.fields) |field| {
                @field(val, field.name) = @field(fields, field.name);
            }
            mmio.write(addr, val);
        }

        /// Toggle the given fields of the given struct.
        /// Can be used if packedT is a struct with 'u1' fields.
        pub inline fn toggle(addr: *volatile mmio, fields: anytype) void {
            var val = mmio.read(addr);
            inline for (@typeInfo(@TypeOf(fields)).Struct.fields) |field| {
                @field(val, @tagName(field.default_value.?)) = !@field(val, @tagName(field.default_value.?));
            }
            mmio.write(addr, val);
        }
    };
}
