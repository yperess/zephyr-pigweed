/*
 * Copyright (c) 2024 Google Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstring>

#include "hello.h"

TEST(HelloWorld, ContainsBoardName) {
  pw::StringBuffer<128> buffer;
  app::WelcomeMessage(buffer, "Hello", "world");
  EXPECT_TRUE(buffer.ok());
  EXPECT_NE(nullptr, strstr(buffer.c_str(), "world"));
}
