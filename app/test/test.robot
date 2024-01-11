*** Settings ***
Resource                      ${KEYWORDS}

*** Test Cases ***
Should Run Test
    Prepare Machine
    Wait For Line On Uart     PASSED
