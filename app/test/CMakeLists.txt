# Copyright (c) 2024 Google LLC
# SPDX-License-Identifier: Apache-2.0

target_sources(app
  PRIVATE
    main.cc
    test_tokenization.cc
)
target_link_libraries(app
  PRIVATE
    pw_unit_test.light
    pw_unit_test.logging_event_handler
)
