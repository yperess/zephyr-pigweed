// Copyright (c) 2023 Google LLC
// SPDX-License-Identifier: Apache-2.0

#define PW_LOG_MODULE_NAME "codelab"

#include "pw_log/log.h"

int main() {
  PW_LOG_INFO("Hello %s", CONFIG_BOARD);
  return 0;
}
