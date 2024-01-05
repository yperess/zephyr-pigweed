//
// Created by peress on 05/01/24.
//

#pragma once

#include "pw_string/string_builder.h"

namespace app {

void WelcomeMessage(pw::StringBuilder &buffer, const std::string_view board,
                    const std::string_view bin_name);

} // namespace app
