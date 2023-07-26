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

#if MARL_WINDOWS

#include "osfiber_windows.h"

MARL_EXPORT
void marl_main_fiber_init(struct marl_fiber_context *ctx) {
  ctx->fiber = ConvertThreadToFiberEx(NULL, FIBER_FLAG_FLOAT_SWITCH);
  ctx->from_thread = TRUE;
}

MARL_EXPORT
void marl_fiber_create(struct marl_fiber_context* ctx,
                                  void* stack,
                                  uint32_t stack_size,
                                  void (*target)(void*),
                                  void* arg) {
  ctx->fiber = CreateFiberEx(stack_size - 1, stack_size, FIBER_FLAG_FLOAT_SWITCH,
                             target, arg);
  ctx->from_thread = FALSE;
}

MARL_EXPORT 
void marl_fiber_deinit(struct marl_fiber_context *ctx) {
  if (ctx->from_thread) {
    ConvertFiberToThread();
  } else {
    DeleteFiber(ctx->fiber);
  }
}

MARL_EXPORT
void marl_fiber_swap(struct marl_fiber_context* from,
                            const struct marl_fiber_context* to) {
  SwitchToFiber(to->fiber);                           
}

#endif
