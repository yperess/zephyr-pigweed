/* Copyright (c) 2024 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pw_unit_test/framework.h"
#include "pw_unit_test/logging_event_handler.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  pw::unit_test::LoggingEventHandler handler;
  pw::unit_test::RegisterEventHandler(&handler);
  return RUN_ALL_TESTS();
}
