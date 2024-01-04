/// arch.x86.task.zig
/// Task context information
///  Used to store hardware context information, like the register page
pub const Context = union {
    sp: u64,
};

/// POSIX PID type
pub const PID: type = u64;

pub fn CreateContext(spack_pointer: u64, callback: *const fn () void) Context {
    _ = spack_pointer;
    _ = callback;
    return Context{ .sp = 0 };
}
