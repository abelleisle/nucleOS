const Arch = @import("arch.zig");
const Type = @import("type/queue.zig");
const TaskList = Type.LinkedList(*Task);

// zig fmt: off
pub const Task = struct {
    context: *Arch.Task.Context,
    stack  : []const u8,
    pid    : Arch.Task.PID,
    name   : []const u8,
    node   : TaskList.Node
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
        .node = .{ .data = undefined },
    };
    task.node.data = &task;
    // zig fmt: on

    taskList.append(&task.node);

    return task;
}

pub fn schedule() void {
    Arch.Interrupt.disable();

    Arch.Interrupt.enable();
}

pub fn reap() void {}

fn obtainPID() Arch.Task.PID {
    currentPID += 1;
    return currentPID;
}

/// Stored in BSS
var taskList: TaskList = TaskList{};
var currentPID: Arch.Task.PID = 1;

pub fn init() void {
    currentPID = 0;
}
