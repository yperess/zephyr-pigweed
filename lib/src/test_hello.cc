/* Copyright (c) 2024 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <cstring>

#include "hello.h"

namespace {
TEST(HelloWorld, ContainsGreeting) {
  pw::StringBuffer<128> buffer;
  pw::InlineString<6> greeting = "Hello";
  pw::InlineString<6> name = "World";
  app::WelcomeMessage(buffer, greeting, name);
  EXPECT_TRUE(buffer.ok());
  EXPECT_NE(nullptr, strstr(buffer.c_str(), "Hello"));

  greeting = "Hi";
  name = "Wayne";
  buffer.clear();
  app::WelcomeMessage(buffer, greeting, name);
  EXPECT_TRUE(buffer.ok());
  EXPECT_NE(nullptr, strstr(buffer.c_str(), "Hi"));
}

TEST(HelloWorld, ContainsName) {
  pw::StringBuffer<128> buffer;
  pw::InlineString<6> greeting = "Hello";
  pw::InlineString<6> name = "World";
  app::WelcomeMessage(buffer, greeting, name);
  EXPECT_TRUE(buffer.ok());
  EXPECT_NE(nullptr, strstr(buffer.c_str(), "World"));

  greeting = "Hi";
  name = "Wayne";
  buffer.clear();
  app::WelcomeMessage(buffer, greeting, name);
  EXPECT_TRUE(buffer.ok());
  EXPECT_NE(nullptr, strstr(buffer.c_str(), "Wayne"));
}
}  // namespace
