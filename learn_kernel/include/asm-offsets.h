#ifndef __ASM_OFFSETS_H__
#define __ASM_OFFSETS_H__
/*
 * DO NOT MODIFY.
 *
 * This file was generated by Kbuild
 *
 */

#define S_TASK_SIZE 560 /* sizeof(struct task_struct) */
#define S_FRAME_SIZE 272 /* sizeof(struct pt_regs) */
#define THREAD_CPU_CONTEXT 0 /* offsetof(struct task_struct, cpu_context) */
#define TIF_PREEMPT_COUNT 120 /* offsetof(struct task_struct, preempt_count) */
#define THREAD_FLAG 128 /* offsetof(struct task_struct, flag) */
#define S_X0 0 /* offsetof(struct pt_regs, regs) */
#define S_X8 64 /* offsetof(struct pt_regs, regs[8]) */
#define S_X30 240 /* offsetof(struct pt_regs, regs[30]) */
#define S_SP 248 /* offsetof(struct pt_regs, sp) */
#define S_PC 256 /* offsetof(struct pt_regs, pc) */
#define S_PSTATE 264 /* offsetof(struct pt_regs, pstate) */
#define S_PGD 144 /* offsetof(struct task_struct, mm) */

#endif