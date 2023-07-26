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


#include "osfiber_macro.h"
#include <assert.h>

#if MARL_USE_UCONTEXT

#include "osfiber_ucontext.h"
#include <stdint.h>

MARL_EXPORT
void marl_main_fiber_init(struct marl_fiber_context *ctx) {
  int res = getcontext(&ctx->context);
  MARL_ASSERT(res == 0);
}

MARL_EXPORT
void marl_fiber_init(struct marl_fiber_context* ctx,
                                  void* stack,
                                  uint32_t stack_size,
                                  void (*target)(void*),
                                  void* arg) {
  int res = getcontext(&ctx->context);
  MARL_ASSERT(res == 0);
  ctx->context.uc_stack.ss_sp = stack;
  ctx->context.uc_stack.ss_size = stack_size;
  ctx->context.uc_link = (void*)0;

  makecontext(&ctx->context, (void (*)())(target), 1, arg);
}

MARL_EXPORT 
void marl_fiber_deinit(struct marl_fiber_context *ctx) {
}

MARL_EXPORT
void marl_fiber_swap(struct marl_fiber_context* from,
                            const struct marl_fiber_context* to) {
  int res = swapcontext(&from->context, &to->context);
  MARL_ASSERT(res == 0);
}

#endif
