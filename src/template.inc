// -*- c -*-
// Created by asm/template.rb

#if defined(CPU_X86_64)

// x86_64
#define TRANSIT_CODE_TEMPLATE { \
  /* 0000000000000000 <transit>: */ \
  /*    0: */ 0x4c,0x8d,0x1d,0xf9,0xff,0xff,0xff, /* lea    -0x7(%rip),%r11        # 0 <transit> */ \
  /*    7: */ 0xff,0x25,0x00,0x00,0x00,0x00,      /* jmp    *0x0(%rip)        # d <hook_caller_addr> */ \
  /* 000000000000000d <hook_caller_addr>: */ \
  /*    d: */ 0x0f,0x1f,0x40,0x00,                /* nopl   0x0(%rax) */ \
  /*   11: */ 0x0f,0x1f,0x40,0x00,                /* nopl   0x0(%rax) */ \
  }
#define TRANSIT_HOOK_CALLER_ADDR 0xd
#define TRANSIT_CODE_SIZE 0x15

#elif defined(CPU_X86)

// Windows 32-bit and Linux i686
#define TRANSIT_CODE_TEMPLATE { \
  /* 00000000 <transit>: */ \
  /*    0: */ 0x55,                               /* push   %ebp */ \
  /*    1: */ 0x89,0xe5,                          /* mov    %esp,%ebp */ \
  /*    3: */ 0x51,                               /* push   %ecx */ \
  /*    4: */ 0x52,                               /* push   %edx */ \
  /*    5: */ 0xe8,0x22,0x00,0x00,0x00,           /* call   2c <get_eip> */ \
  /*    a: */ 0x8d,0x40,0xf6,                     /* lea    -0xa(%eax),%eax */ \
  /*    d: */ 0x83,0xec,0x08,                     /* sub    $0x8,%esp */ \
  /*   10: */ 0x8d,0x4d,0x04,                     /* lea    0x4(%ebp),%ecx */ \
  /*   13: */ 0x51,                               /* push   %ecx */ \
  /*   14: */ 0x50,                               /* push   %eax */ \
  /*   15: */ 0x8d,0x80,0x30,0x00,0x00,0x00,      /* lea    0x30(%eax),%eax */ \
  /*   1b: */ 0xff,0x10,                          /* call   *(%eax) */ \
  /*   1d: */ 0x58,                               /* pop    %eax */ \
  /*   1e: */ 0x83,0xc4,0x0c,                     /* add    $0xc,%esp */ \
  /*   21: */ 0x5a,                               /* pop    %edx */ \
  /*   22: */ 0x59,                               /* pop    %ecx */ \
  /*   23: */ 0xc9,                               /* leave   */ \
  /*   24: */ 0x8d,0x80,0x34,0x00,0x00,0x00,      /* lea    0x34(%eax),%eax */ \
  /*   2a: */ 0xff,0x20,                          /* jmp    *(%eax) */ \
  /* 0000002c <get_eip>: */ \
  /*   2c: */ 0x8b,0x04,0x24,                     /* mov    (%esp),%eax */ \
  /*   2f: */ 0xc3,                               /* ret     */ \
  /* 00000030 <hook_caller_addr>: */ \
  /*   30: */ 0x0f,0x1f,0x40,0x00,                /* nopl   0x0(%eax) */ \
  /* 00000034 <hook_func_addr>: */ \
  /*   34: */ 0x0f,0x1f,0x40,0x00,                /* nopl   0x0(%eax) */ \
  }
#define TRANSIT_HOOK_CALLER_ADDR 0x30
#define TRANSIT_HOOK_FUNC_ADDR 0x34
#define TRANSIT_CODE_SIZE 0x38

#elif defined(CPU_ARM64)

// ARM64
#define TRANSIT_CODE_TEMPLATE { \
  /* 0000000000000000 <transit>: */ \
  /*    0: */ 0xa9bf7bfd,                         /* stp x29, x30, [sp, #-16]! */ \
  /*    4: */ 0x910003fd,                         /* mov x29, sp */ \
  /*    8: */ 0xa9bf03e1,                         /* stp x1, x0, [sp, #-16]! */ \
  /*    c: */ 0xa9bf0be3,                         /* stp x3, x2, [sp, #-16]! */ \
  /*   10: */ 0xa9bf13e5,                         /* stp x5, x4, [sp, #-16]! */ \
  /*   14: */ 0xa9bf1be7,                         /* stp x7, x6, [sp, #-16]! */ \
  /*   18: */ 0xa9bf4be8,                         /* stp x8, x18, [sp, #-16]! */ \
  /*   1c: */ 0xadbf03e1,                         /* stp q1, q0, [sp, #-32]! */ \
  /*   20: */ 0xadbf0be3,                         /* stp q3, q2, [sp, #-32]! */ \
  /*   24: */ 0xadbf13e5,                         /* stp q5, q4, [sp, #-32]! */ \
  /*   28: */ 0xadbf1be7,                         /* stp q7, q6, [sp, #-32]! */ \
  /*   2c: */ 0x10fffea0,                         /* adr x0, 0 <transit> */ \
  /*   30: */ 0xd10043a1,                         /* sub x1, x29, #0x10 */ \
  /*   34: */ 0x580001e9,                         /* ldr x9, 70 <hook_caller_addr> */ \
  /*   38: */ 0xd63f0120,                         /* blr x9 */ \
  /*   3c: */ 0xacc11be7,                         /* ldp q7, q6, [sp], #32 */ \
  /*   40: */ 0xacc113e5,                         /* ldp q5, q4, [sp], #32 */ \
  /*   44: */ 0xacc10be3,                         /* ldp q3, q2, [sp], #32 */ \
  /*   48: */ 0xacc103e1,                         /* ldp q1, q0, [sp], #32 */ \
  /*   4c: */ 0xa8c14be8,                         /* ldp x8, x18, [sp], #16 */ \
  /*   50: */ 0xa8c11be7,                         /* ldp x7, x6, [sp], #16 */ \
  /*   54: */ 0xa8c113e5,                         /* ldp x5, x4, [sp], #16 */ \
  /*   58: */ 0xa8c10be3,                         /* ldp x3, x2, [sp], #16 */ \
  /*   5c: */ 0xa8c103e1,                         /* ldp x1, x0, [sp], #16 */ \
  /*   60: */ 0xa8c17bfd,                         /* ldp x29, x30, [sp], #16 */ \
  /*   64: */ 0x580000a9,                         /* ldr x9, 78 <hook_func_addr> */ \
  /*   68: */ 0xd61f0120,                         /* br x9 */ \
  /*   6c: */ 0xd503201f,                         /* nop */ \
  /* 0000000000000070 <hook_caller_addr>: */ \
  /*   70: */ 0xd503201f,                         /* nop */ \
  /*   74: */ 0xd503201f,                         /* nop */ \
  /* 0000000000000078 <hook_func_addr>: */ \
  /*   78: */ 0xd503201f,                         /* nop */ \
  /*   7c: */ 0xd503201f,                         /* nop */ \
  }
#define TRANSIT_HOOK_CALLER_ADDR 0x1c
#define TRANSIT_HOOK_FUNC_ADDR 0x1e
#define TRANSIT_CODE_SIZE 0x20

#elif defined(CPU_RISCV)

// RISCV 64
#define TRANSIT_CODE_TEMPLATE { \
  /* 0000000000000000 <transit>: */ \
  /*    0: */ 0x7119,                             /* addi sp,sp,-128 */ \
  /*    2: */ 0xe006,                             /* sd ra,0(sp) */ \
  /*    4: */ 0xe422,                             /* sd s0,8(sp) */ \
  /*    6: */ 0xe826,                             /* sd s1,16(sp) */ \
  /*    8: */ 0xec2a,                             /* sd a0,24(sp) */ \
  /*    a: */ 0xf02e,                             /* sd a1,32(sp) */ \
  /*    c: */ 0xf432,                             /* sd a2,40(sp) */ \
  /*    e: */ 0xf836,                             /* sd a3,48(sp) */ \
  /*   10: */ 0xfc3a,                             /* sd a4,56(sp) */ \
  /*   12: */ 0xe0be,                             /* sd a5,64(sp) */ \
  /*   14: */ 0xe4c2,                             /* sd a6,72(sp) */ \
  /*   16: */ 0xe8c6,                             /* sd a7,80(sp) */ \
  /*   18: */ 0xecca,                             /* sd s2,88(sp) */ \
  /*   1a: */ 0xf0ce,                             /* sd s3,96(sp) */ \
  /*   1c: */ 0x00000517,                         /* auipc a0,0x0 */ \
  /*   20: */ 0x00053503,                         /* ld a0,0(a0) # 1c <transit+0x1c> */ \
  /*   24: */ 0x010c,                             /* addi a1,sp,128 */ \
  /*   26: */ 0x00000317,                         /* auipc t1,0x0 */ \
  /*   2a: */ 0x00033303,                         /* ld t1,0(t1) # 26 <transit+0x26> */ \
  /*   2e: */ 0x000300e7,                         /* jalr t1 */ \
  /*   32: */ 0x6082,                             /* ld ra,0(sp) */ \
  /*   34: */ 0x6422,                             /* ld s0,8(sp) */ \
  /*   36: */ 0x64c2,                             /* ld s1,16(sp) */ \
  /*   38: */ 0x6562,                             /* ld a0,24(sp) */ \
  /*   3a: */ 0x7582,                             /* ld a1,32(sp) */ \
  /*   3c: */ 0x7622,                             /* ld a2,40(sp) */ \
  /*   3e: */ 0x76c2,                             /* ld a3,48(sp) */ \
  /*   40: */ 0x7762,                             /* ld a4,56(sp) */ \
  /*   42: */ 0x6786,                             /* ld a5,64(sp) */ \
  /*   44: */ 0x6826,                             /* ld a6,72(sp) */ \
  /*   46: */ 0x68c6,                             /* ld a7,80(sp) */ \
  /*   48: */ 0x6966,                             /* ld s2,88(sp) */ \
  /*   4a: */ 0x7986,                             /* ld s3,96(sp) */ \
  /*   4c: */ 0x6109,                             /* addi sp,sp,128 */ \
  /*   4e: */ 0x00000317,                         /* auipc t1,0x0 */ \
  /*   52: */ 0x00033303,                         /* ld t1,0(t1) # 4e <transit+0x4e> */ \
  /*   56: */ 0x8302,                             /* jr t1 */ \
  /* 0000000000000058 <hook_caller_addr>: */ \
  /*   58: */ 0x0001,                             /* nop */ \
  /*   5a: */ 0x0001,                             /* nop */ \
  /* 000000000000005c <hook_func_addr>: */ \
  /*   5c: */ 0x0001,                             /* nop */ \
  /*   5e: */ 0x0001,                             /* nop */ \
  }
#define TRANSIT_HOOK_CALLER_ADDR 0x25
#define TRANSIT_HOOK_FUNC_ADDR 0x27
#define TRANSIT_CODE_SIZE 0x29

#endif
