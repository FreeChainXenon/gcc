/* Redefinitions for FreeChainXenon
   Copyright (C) 2025 Aiden Isik

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#undef TARGET_DEBUG_STACK
#define TARGET_DEBUG_STACK 1

/* Force the pointer size to 32 bits (even though we run in 64-bit mode) */
#undef POINTER_SIZE_UNITS
#define POINTER_SIZE_UNITS 4
#undef POINTER_SIZE
#define POINTER_SIZE 32
#undef Pmode
#define Pmode SImode
#undef POINTERS_EXTEND_UNSIGNED
#define POINTERS_EXTEND_UNSIGNED 1

/* Make sure TARGET_64BIT is set to 1 */
#undef TARGET_64BIT
#define TARGET_64BIT 1
#undef TARGET_32BIT
#define TARGET_32BIT 0

/* Manually set flags */
#undef TARGET_DEFAULT
#define TARGET_DEFAULT (/*OPTION_MASK_EABI |*/ OPTION_MASK_ALTIVEC | OPTION_MASK_PPC_GFXOPT | OPTION_MASK_PPC_GPOPT \
			| OPTION_MASK_MFCRF | MASK_POWERPC64 | MASK_64BIT)

/* Redefine parameter boundary */
#undef PARM_BOUNDARY
#define PARM_BOUNDARY 64

/* Redefine some debug data alignment. Could be useful later? */
#undef DWARF_CIE_DATA_ALIGNMENT
#define DWARF_CIE_DATA_ALIGNMENT -8

/* Redefine the save area mode */
#undef STACK_SAVEAREA_MODE
#define STACK_SAVEAREA_MODE(LEVEL)	\
  (LEVEL == SAVE_FUNCTION ? VOIDmode	\
  : LEVEL == SAVE_NONLOCAL ? (TARGET_32BIT ? DImode : PTImode) : Pmode)

/* Redefine stack size mode */
#undef STACK_SIZE_MODE
#define STACK_SIZE_MODE DImode

/* Change the fixed area for the 360's stack frame convention */
#undef RS6000_SAVE_AREA
#define RS6000_SAVE_AREA 0x10 + (RS6000_ALIGN (crtl->outgoing_args_size.to_constant (), 16) - crtl->outgoing_args_size.to_constant ()) + 0x40

/* Redefine the starting frame offset, since it relies on the size of the fixed area */
#undef RS6000_STARTING_FRAME_OFFSET
#define RS6000_STARTING_FRAME_OFFSET \
    (cfun->calls_alloca \
        ? (RS6000_ALIGN (crtl->outgoing_args_size + RS6000_SAVE_AREA, 16)) \
        : (RS6000_ALIGN (crtl->outgoing_args_size, 16) + RS6000_SAVE_AREA))

/* Redefine the offset of the first stack argument, since it relies on the size of the fixed area */
#undef FIRST_PARM_OFFSET
#define FIRST_PARM_OFFSET(FNDECL) RS6000_SAVE_AREA

/* Redefine stack pointer offset, since it relies on the size of the fixed area */
#undef STACK_POINTER_OFFSET
#define STACK_POINTER_OFFSET RS6000_SAVE_AREA

/* Redefine the offset from the stack pointer to items allocated by alloca() and friends */
#undef STACK_DYNAMIC_OFFSET
#define STACK_DYNAMIC_OFFSET(FUNDECL) \
    RS6000_ALIGN (crtl->outgoing_args_size.to_constant () + STACK_POINTER_OFFSET, 16)
