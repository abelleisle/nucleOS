pub inline fn write(addr: u32, data: u32) void {
    var reg: *@TypeOf(addr) = @ptrFromInt(addr);
    reg.* = data;
}

pub inline fn read(addr: u32) u32 {
    const reg: *@TypeOf(addr) = @ptrFromInt(addr);
    return reg.*;
}
