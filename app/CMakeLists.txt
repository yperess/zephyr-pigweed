# Copyright (c) 2023 Google LLC
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(zephyr-pigweed)
enable_language(C CXX)

zephyr_library_named(hello_world)
target_sources(hello_world
  PRIVATE
    include/hello.h
    src/hello.cc
)
target_include_directories(hello_world
  PUBLIC
    include
)
target_link_libraries(hello_world PRIVATE pw_string)
target_link_libraries(app PRIVATE hello_world)

if(CONFIG_TEST)
  add_subdirectory(test)
else()
  target_sources(app
    PRIVATE
      src/main.cc
  )
  target_link_libraries(app
    PRIVATE
      pw_string
  )
endif()
