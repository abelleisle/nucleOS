const nArch = @import("arch.zig");

/// The kernel entrypoint for NucleOS.
/// This is where it all begins and what gets called from the bootloader.
/// This function is used to initialize hardware and start the boot sequence.
/// The actual task subsystem begins in `nMain()`.
fn nEntry() void {
    nArch.init();

    nMain();
}

/// The kernel main function.
/// This is where the kernel starts its subsystems, such as:
///   Task System
///   Log System
///   Coredump handler
///   Network Stack
///   etc..
fn nMain() void {}
