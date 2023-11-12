/// Build the kernel based on hardware.
/// We can expose modules using the 'n' prefix. Example: 'nArch' will be the
///  architecture-specific module of NucleOS.
///
/// This makes it easy to enable hardware specific settings.
/// For example, if we're compiling for x86, the nArch module will be created
///  with the base file: kernel/arch/x86/x86.zig.
/// At this point, the kernel can use @import("nArch") to import architecture
///  dependant code without relying on the zig standard library
///  (std.zig.crossTarget...)
