# Copyright (c) 2024 Google LLC
# SPDX-License-Identifier: Apache-2.0

include($ENV{PW_ROOT}/pw_build/pigweed.cmake)

pw_add_library(hello_world STATIC
  HEADERS
    include/hello.h
  SOURCES
    src/hello.cc
  PUBLIC_INCLUDES
    include
  PUBLIC_DEPS
    pw_string
    zephyr_interface
)

pw_add_test(hello_world.test
  SOURCES
    src/test_hello.cc
  PRIVATE_DEPS
    hello_world
)
