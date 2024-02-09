/* Copyright (c) 2024 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hello.h"

namespace app {
void WelcomeMessage(::pw::StringBuilder& buffer,
                    std::string_view greeting,
                    std::string_view name) {
  buffer << greeting << ", " << name << "!";
}
}  // namespace app
