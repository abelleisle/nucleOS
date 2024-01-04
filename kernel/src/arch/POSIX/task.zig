/// arch.POSIX.task.zig
/// Task context information
///  Used to store hardware context information, like the register page
pub const Context = union {
    sp: usize,
};

/// POSIX PID type
pub const ID: type = usize;

pub fn CreateContext(callback: *const fn () void) Context {
    _ = callback;
    return Context{ .sp = 0 };
}
