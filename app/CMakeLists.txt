# Copyright (c) 2024 Google LLC
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(zephyr-pigweed LANGUAGES C CXX)

if(NOT CONFIG_TEST)
  target_sources(app PRIVATE src/main.cc)
else()
  target_sources(app PRIVATE src/test_main.cc)
  target_link_libraries(app
    PRIVATE
      hello_world.test.lib
      pw_unit_test.light
      pw_unit_test.logging_event_handler
  )
endif()

target_link_libraries(app PRIVATE hello_world)
