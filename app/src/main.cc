// Copyright (c) 2023 Google LLC
// SPDX-License-Identifier: Apache-2.0

#define PW_LOG_MODULE_NAME "codelab"

#include "pw_chrono/system_clock.h"
#include "pw_log/log.h"
#include "pw_string/string_builder.h"
#include "pw_thread/sleep.h"

#include "hello.h"

using namespace std::chrono_literals;

int main() {
  pw::StringBuffer<128> greeting;
  app::WelcomeMessage(greeting, CONFIG_BOARD, CONFIG_KERNEL_BIN_NAME);
  while (true) {
    PW_LOG_INFO("Hello %s", greeting.c_str());
    pw::this_thread::sleep_for(1s);
  }
  PW_UNREACHABLE;
}
