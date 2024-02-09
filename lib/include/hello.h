/* Copyright (c) 2024 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "pw_string/string.h"
#include "pw_string/string_builder.h"

namespace app {
void WelcomeMessage(::pw::StringBuilder& buffer,
                    const ::pw::InlineString<>& greeting,
                    const ::pw::InlineString<>& name);
}  // namespace app
