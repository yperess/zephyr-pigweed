/* Copyright (c) 2024 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hello.h"

namespace app {
void WelcomeMessage(::pw::StringBuilder& buffer,
                    const ::pw::InlineString<>&,
                    const ::pw::InlineString<>&) {
  buffer << "Hello, World!";
}
}  // namespace app
