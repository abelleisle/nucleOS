export const PAGE_SHIFT: u32 = 12;
export const TABLE_SHIFT: u32 = 9;
export const SECTION_SHIFT: 32 = PAGE_SHIFT + TABLE_SHIFT;

export const PAGE_SIZE: u32 = (1 << PAGE_SHIFT);
export const SECTION_SIZE: u32 = (1 << SECTION_SHIFT);

export const LOW_MEMORY: u32 = (2 * SECTION_SIZE);

comptime {
    asm (@embedFile("boot.S"));
    asm (@embedFile("mem.S"));
}
