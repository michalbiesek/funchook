/* -*- indent-tabs-mode: nil -*-
 *
 * This file is part of Funchook.
 * https://github.com/kubo/funchook
 *
 * Funchook is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 2 of the License, or (at your
 * option) any later version.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this library with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module. An independent module is a module which is not derived from or
 * based on this library. If you modify this library, you may extend this
 * exception to your version of the library, but you are not obliged to
 * do so. If you do not wish to do so, delete this exception statement
 * from your version.
 *
 * Funchook is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Funchook. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FUNCHOOK_RISCV_H
#define FUNCHOOK_RISCV_H 1


#define FUNCHOOK_RISCV_REG_S0 (1u<<9)
#define FUNCHOOK_RISCV_REG_S1 (1u<<10)
#define FUNCHOOK_RISCV_REG_S2 (1u<<11)
#define FUNCHOOK_RISCV_REG_S3 (1u<<12)
#define FUNCHOOK_RISCV_REG_S4 (1u<<13)
#define FUNCHOOK_RISCV_REG_S5 (1u<<14)
#define FUNCHOOK_RISCV_REG_S6 (1u<<15)
#define FUNCHOOK_RISCV_REG_S7 (1u<<16)
#define FUNCHOOK_RISCV_REG_S8 (1u<<17)
#define FUNCHOOK_RISCV_REG_S9 (1u<<18)
#define FUNCHOOK_RISCV_REG_S10 (1u<<19)
#define FUNCHOOK_RISCV_REG_S11 (1u<<20)

#define FUNCHOOK_RISCV_CORRUPTIBLE_REGS (FUNCHOOK_RISCV_REG_S0 \
  | FUNCHOOK_RISCV_REG_S1 | FUNCHOOK_RISCV_REG_S2 \
  | FUNCHOOK_RISCV_REG_S3 | FUNCHOOK_RISCV_REG_S4 \
  | FUNCHOOK_RISCV_REG_S5 | FUNCHOOK_RISCV_REG_S6 \
  | FUNCHOOK_RISCV_REG_S7 | FUNCHOOK_RISCV_REG_S8 \
  | FUNCHOOK_RISCV_REG_S9 | FUNCHOOK_RISCV_REG_S10 \
  | FUNCHOOK_RISCV_REG_S11)

typedef enum {
    FUNCHOOK_RISCV_INSN_OTHER = 0,
    FUNCHOOK_RISCV_INSN_JAL,    //ok
    FUNCHOOK_RISCV_INSN_BEQ,    //ok
    FUNCHOOK_RISCV_INSN_BLT,    //ok
    FUNCHOOK_RISCV_INSN_BGE,    //ok
    FUNCHOOK_RISCV_INSN_LW,     //ok
    FUNCHOOK_RISCV_INSN_LD,     //ok
} funchook_riscv_insn_id_t;

#define MAX_INSN_CHECK_SIZE 64
#define JUMP32_SIZE 2
#define LITERAL_POOL_OFFSET (3 * JUMP32_SIZE + 2)
#define LITERAL_POOL_NUM (JUMP32_SIZE + 1)
#define TRAMPOLINE_SIZE (LITERAL_POOL_OFFSET + 2 * LITERAL_POOL_NUM)

#define FUNCHOOK_ENTRY_AT_PAGE_BOUNDARY 1

typedef uint8_t insn_t;

typedef struct funchook_entry {
    uint8_t transit[TRANSIT_CODE_SIZE];
    void *original_target_func;
    void *target_func;
    void *hook_func;
    funchook_hook_t prehook;
    void *user_data;
    char *arg_types;
    uint32_t flags;
    uint8_t trampoline[TRAMPOLINE_SIZE];
    uint8_t old_code[JUMP32_SIZE];
    uint8_t new_code[JUMP32_SIZE];
} funchook_entry_t;

typedef struct {
    int dummy;
} ip_displacement_t;

typedef struct {
    funchook_riscv_insn_id_t insn_id;
    uint32_t regs;
} funchook_insn_info_t;

#endif
