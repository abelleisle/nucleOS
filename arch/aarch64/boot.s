// SPDX-License-Identifier: MIT OR Apache-2.0
//
// Copyright (c) 2021-2022 Andre Richter <andre.o.richter@gmail.com>

//--------------------------------------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------------------------------------

// Load the address of a symbol into a register, PC-relative.
//
// The symbol must lie within +/- 4 GiB of the Program Counter.
//
// # Resources
//
// - https://sourceware.org/binutils/docs-2.36/as/AArch64_002dRelocations.html
.macro ADR_REL register, symbol
	adrp	\register, \symbol
	add	\register, \register, #:lo12:\symbol
.endm

//--------------------------------------------------------------------------------------------------
// Public Code
//--------------------------------------------------------------------------------------------------
.section .text._start

//------------------------------------------------------------------------------
// fn _start()
//------------------------------------------------------------------------------
_start:
	// Only proceed on the boot core. Park it otherwise.
	mrs	x0, MPIDR_EL1
	ldr	x1, CONST_CORE_ID_MASK // provided by bsp/__board_name__/cpu.rs
	and	x0, x0, x1
	ldr	x1, BOOT_CORE_ID       // provided by bsp/__board_name__/cpu.rs
	cmp	x0, x1
	b.ne	.L_parking_loop

	// If execution reaches here, it is the boot core.

	// Initialize DRAM.
	ADR_REL	x0, __bss_start
	ADR_REL x1, __bss_end_exclusive

.L_bss_init_loop:
	cmp	x0, x1
	b.eq	.L_prepare_zig
	stp	xzr, xzr, [x0], #16
	b	.L_bss_init_loop

	// Prepare the jump to Zig code.
.L_prepare_zig:
	// Set the stack pointer.
	ADR_REL	x0, __boot_core_stack_end_exclusive
	mov	sp, x0

	// Jump to Zig code.
	b	_start_zig

	// Infinitely wait for events (aka "park the core").
.L_parking_loop:
	wfe
	b	.L_parking_loop

.size	_start, . - _start
.type	_start, function
.global	_start
