*** Keywords ***
Create Machine
    [Arguments]                     ${elf_file}=${EMPTY}
    IF  "${elf_file}" != "${EMPTY}"
        Execute Command                 $bin=@${elf_file}
    END
    
    Execute Script                  ${CURDIR}/cortex_a53.resc
    Execute Command                 logFile @log.txt
    Create Terminal Tester          sysbus.uart0
    
*** Test Cases ***
Should Run Application
    Create Machine                  ${CURDIR}/../binaries/app.elf

    Wait For Line On UART           <inf> pigweed: codelab Hello qemu_cortex_a53 / zephyr.exe
    Wait For Line On UART           <inf> pigweed: codelab Hello qemu_cortex_a53 / zephyr.exe
    Wait For Line On UART           <inf> pigweed: codelab Hello qemu_cortex_a53 / zephyr.exe

Should Run Test
    Create Machine                  ${CURDIR}/../binaries/test.elf
    Wait For Line On UART           PASSED
