// Copyright (c) 2023 Google LLC
// SPDX-License-Identifier: Apache-2.0

#define PW_LOG_MODULE_NAME "codelab"

#include "pw_chrono/system_clock.h"
#include "pw_log/log.h"
#include "pw_thread/sleep.h"

using namespace std::chrono_literals;

int main() {
  while (true) {
    PW_LOG_INFO("Hello %s", CONFIG_BOARD);
    pw::this_thread::sleep_for(1s);
  }
  PW_UNREACHABLE;
}
