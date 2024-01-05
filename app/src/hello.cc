#include "hello.h"

namespace app {

void WelcomeMessage(pw::StringBuilder &buffer, const std::string_view board,
                    const std::string_view bin_name) {
  buffer << board << " / " << bin_name << ".exe";
}

}  // namespace app
