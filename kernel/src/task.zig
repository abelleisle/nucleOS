const arch = @import("arch.zig");

// zig fmt: off
pub const Task = struct {
    name    : []const u8,
    pid     : arch.Task.PID,
    context : arch.Task.Context,
};

pub const TaskCallback = *const fn () void;
// zig fmt: on

/// Create a new task
///
/// param name: The name of the task
/// param callback: The task body to enter
pub fn Create(name: []const u8, callback: *const fn () void) Task {
    const stack_addr: [*]arch.Task.Address = @ptrFromInt(0x100);
    const stack = stack_addr[0..100];

    // zig fmt: off
    const task: Task = .{
        .name = name,
        .pid = obtainPID(),
        .context = arch.Task.Context.init(stack, callback)
    };
    // zig fmt: on

    return task;
}

fn obtainPID() arch.Task.PID {
    currentPID += 1;
    return currentPID;
}

/// Stored in BSS
var currentPID: arch.Task.PID = 1;
fn init() void {
    currentPID = 0;
}
