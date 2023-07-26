// Copyright 2019 The Marl Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Minimal assembly implementations of fiber context switching for Unix-based
// platforms.
//
// Note: Unlike makecontext, swapcontext or the Windows fiber APIs, these
// assembly implementations *do not* save or restore signal masks,
// floating-point control or status registers, FS and GS segment registers,
// thread-local storage state nor any SIMD registers. This should not be a
// problem as the marl scheduler requires fibers to be executed on the same
// thread throughout their lifetime.

#ifndef MARL_OSFIBER_H_
#define MARL_OSFIBER_H_

#include <stdint.h>
#include "osfiber_macro.h"

#if defined(MARL_WINDOWS)
#include "osfiber_windows.h"
#elif defined(MARL_USE_UCONTEXT)
#include "osfiber_ucontext.h"
#elif defined(__x86_64__)
#include "osfiber_asm_x64.h"
#elif defined(__i386__)
#include "osfiber_asm_x86.h"
#elif defined(__aarch64__)
#include "osfiber_asm_aarch64.h"
#elif defined(__arm__)
#include "osfiber_asm_arm.h"
#elif defined(__powerpc64__)
#include "osfiber_asm_ppc64.h"
#elif defined(__mips__) && _MIPS_SIM == _ABI64
#include "osfiber_asm_mips64.h"
#elif defined(__riscv) && __riscv_xlen == 64
#include "osfiber_asm_rv64.h"
#elif defined(__loongarch__) && _LOONGARCH_SIM == _ABILP64
#include "osfiber_asm_loongarch64.h"
#elif defined(__EMSCRIPTEN__)
#include "osfiber_emscripten.h"
#else
#error "Unsupported target"
#endif

#ifdef __cplusplus
extern "C" {
#endif

MARL_EXPORT
extern void marl_main_fiber_init(struct marl_fiber_context *);

MARL_EXPORT
extern void marl_fiber_init(struct marl_fiber_context *, void *stack,
                            uint32_t stack_size, void (*target)(void *),
                            void *arg);

MARL_EXPORT
extern void marl_fiber_deinit(struct marl_fiber_context *);

MARL_EXPORT
extern void marl_fiber_swap(struct marl_fiber_context *from,
                            const struct marl_fiber_context *to);
#ifdef __cplusplus
} // extern "C"
#endif

#endif // MARL_OSFIBER_H_
