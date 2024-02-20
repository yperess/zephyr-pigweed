# SPDX-License-Identifier: Apache-2.0

*** Settings ***
Resource                      ${KEYWORDS}

*** Test Cases ***
Should Greet The User
    # `Prepare Machine` keyword comes from $ZEPHYR_BASE/tests/robot/common.robot file, which is imported as a resource
    Prepare Machine
    Start Emulation
    Wait For Prompt On Uart   pigweed: codelab Goodbye, World!  # this is a mistake, obviously

