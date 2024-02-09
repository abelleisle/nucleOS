const Arch = @import("arch.zig");
const Type = @import("type/queue.zig");
const logging = @import("log.zig");

// zig fmt: off
pub const Task = struct {
    context: *Arch.Task.Context,
    stack  : []const u8,
    pid    : Arch.Task.PID,
    name   : []const u8,
};

pub const TaskCallback = *const fn () void;
// zig fmt: on

/// Create a new task
///
/// param name: The name of the task
/// param callback: The task body to enter
pub fn Create(name: []const u8, callback: *const fn () void, stack: []u8) Task {
    // zig fmt: off
    var task: Task = .{
        .context = Arch.Task.Context.init(callback, stack),
        .stack = stack,
        .pid = obtainPID(),
        .name = name,
    };
    // zig fmt: on

    if (lastTask) |_| {
        nextTask = &task;
    } else {
        lastTask = &task;
    }

    return task;
}

pub fn schedule() void {
    Arch.Interrupt.disable();

    if (lastTask) |t| {
        if (nextTask) |n| {
            logging.log(.debug, "Scheduling!\n");
            const old_ptr: u32 = @intFromPtr(t);
            const new_ptr: u32 = @intFromPtr(n);
            nextTask = t;
            lastTask = n;
            Arch.Task.switch_to_thread(old_ptr, new_ptr);
        }
    }

    Arch.Interrupt.enable();
}

pub fn reap() void {}

fn obtainPID() Arch.Task.PID {
    currentPID += 1;
    return currentPID;
}

/// Stored in BSS
var currentPID: Arch.Task.PID = 1;
var lastTask: ?*Task = null;
var nextTask: ?*Task = null;

pub fn init() void {
    currentPID = 0;
}
