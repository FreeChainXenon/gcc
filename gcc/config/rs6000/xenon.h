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

#if TARGET_64BIT == 0
	#error "Building for 32 bit, should be 64 bit!"
#endif

/* Force the pointer size to 32 bits (even though we run in 64-bit mode) */
//#undef POINTER_SIZE
//#define POINTER_SIZE 32

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
