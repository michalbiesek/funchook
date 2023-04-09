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
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include "funchook_internal.h"
#include "disasm.h"

typedef struct {
    funchook_t *funchook;
    ip_displacement_t *rip_disp;
    const insn_t *src;
    const insn_t *dst_base;
    insn_t *dst;
} make_trampoline_context_t;

int funchook_make_trampoline(funchook_t *funchook, ip_displacement_t *disp, const insn_t *func, insn_t *trampoline, size_t *trampoline_size)
{
    make_trampoline_context_t ctx;
    funchook_disasm_t disasm;
    int rv;
    const funchook_insn_t *insn;

    memset(disp, 0, sizeof(*disp));
    memset(trampoline, 0, TRAMPOLINE_SIZE);
    *trampoline_size = 0;
    ctx.funchook = funchook;
    ctx.rip_disp = disp;
    ctx.src = func;
    ctx.dst_base = ctx.dst = trampoline;

    rv = funchook_disasm_init(&disasm, funchook, func, MAX_INSN_CHECK_SIZE, (size_t)func);
    if (rv != 0) {
        return rv;
    }

    funchook_log(funchook, "  Original Instructions:\n");

    while ((rv = funchook_disasm_next(&disasm, &insn)) == 0) {
        funchook_insn_info_t info = funchook_disasm_riscv_insn_info(&disasm, insn);
        uint32_t ins = *ctx.src;
        // size_t addr;
        // uint32_t regno;

        funchook_disasm_log_instruction(&disasm, insn);
        // avail_regs &= ~info.regs;
        switch (info.insn_id) {
        default:
            *(ctx.dst++) = ins;
            break;
        case FUNCHOOK_RISCV_INSN_JAL:
            break;
        case FUNCHOOK_RISCV_INSN_BEQ:
            break;
        case FUNCHOOK_RISCV_INSN_BLT:
            break;
        case FUNCHOOK_RISCV_INSN_BGE:
            break;
        case FUNCHOOK_RISCV_INSN_LW:
            break;
        case FUNCHOOK_RISCV_INSN_LD:
            break;
        }
        ctx.src++;
    }
    if (rv != FUNCHOOK_ERROR_END_OF_INSTRUCTION) {
        goto cleanup;
    }
    rv = 0;
    if (ctx.src - func < REL4G_JUMP_SIZE) {
        funchook_set_error_message(funchook, "Too short instructions");
        rv = FUNCHOOK_ERROR_TOO_SHORT_INSTRUCTIONS;
        goto cleanup;
    }
cleanup:
    funchook_disasm_cleanup(&disasm);

    return rv;
}

static int funchook_write_jump_with_prehook(funchook_t *funchook, funchook_entry_t *entry, const uint8_t *dst)
{
    static const uint32_t template[TRANSIT_CODE_SIZE] = TRANSIT_CODE_TEMPLATE;
    memcpy(entry->transit, template, sizeof(template));
    extern void funchook_hook_caller_asm(void);
    *(void**)(entry->transit + TRANSIT_HOOK_CALLER_ADDR) = (void*)funchook_hook_caller_asm;
    funchook_log(funchook, "  Write jump 0x"ADDR_FMT" -> 0x"ADDR_FMT" with hook caller 0x"ADDR_FMT"\n",
                 (size_t)entry->transit, (size_t)dst, (size_t)funchook_hook_caller);
    return 0;
}

int funchook_fix_code(funchook_t *funchook, funchook_entry_t *entry, const ip_displacement_t *disp)
{
    void *hook_func = entry->hook_func ? entry->hook_func : entry->trampoline;

    /* func -> transit */
    // funchook_write_relative_4g_jump(funchook, entry->target_func, entry->transit, entry->new_code);
    /* transit -> hook_func */
    if (entry->prehook) {
        funchook_write_jump_with_prehook(funchook, entry, hook_func);
    // } else {
    //     funchook_write_absolute_jump(funchook, entry->transit, hook_func, FUNCHOOK_ARM64_REG_X9);
    }
    return 0;
}

void *funchook_arg_get_int_reg_addr(const funchook_arg_handle_t *arg_handle, int pos)
{
    return NULL;
}

void *funchook_arg_get_flt_reg_addr(const funchook_arg_handle_t *arg_handle, int pos)
{
    return NULL;
}

void *funchook_arg_get_stack_addr(const funchook_arg_handle_t *arg_handle, int pos)
{
    return NULL;
}