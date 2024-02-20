# Renode

[Renode](https://www.renode.io) is an open source simulation framework by [Antmicro](https://www.antmicro.com).

This tutorial will guide you through the initial steps of running Zephyr+Pigweed tests in Renode.

## Getting Renode

If you follow instructions from README, then Renode is already available in your Pigweed environment.

You can download prebuilt packages separately from the [nightly builds page](https://builds.renode.io) (using portable packages is recommended) or build straight [from sources](https://github.com/renode/renode).

## Running test of Zephyr + Pigweed in Renode

### Pigweed tests

If you followed the tutorial, you have enabled two QEMU targets in `testcase.yaml`. Let's add some more:

```yaml
platform_allow:
  - qemu_riscv64
  - qemu_cortex_a53
  - renode_cortex_a53
  - hifive_unleashed
```

Note that Renode does not require additional artificial targets. You can create a very custom target for simulation purposes (like `renode_cortex_a53`) or use an actual physical target (like `hifive_unleashed`).

Now run the tests again:

```shell
$ west twister -cvi -T app/
```

The results are similar to:
```
INFO    - 1/3 qemu_riscv64              app.hello                                          PASSED (qemu 2.015s)
INFO    - 2/3 qemu_cortex_a53           app.hello                                          PASSED (qemu 2.028s)
INFO    - 3/3 renode_cortex_a53         app.hello                                          PASSED (renode 6.107s)
```

This covers platforms considered "default" by Zephyr.

To run tests for a non-default platform, like `hifive_unleashed`, run:

```shell
$ west twister -cvi -p hifive_unleashed -T app/
```

or, to enable testing on all targets at the same time:

```shell
$ west twister -cvi -l -T app/
```

### Robot tests

Renode provides tight integration with the [Robot Framework](https://robotframework.org/).
It's a Python-based testing system, allowing you to write tests in natural language.

To enable these tests, expand your `testcase.yaml`:

```yaml
  app.hello.robot:
    harness: robot
    harness_config:
      robot_test_path: app.robot
    platform_allow:
      - renode_cortex_a53
      - hifive_unleashed
```

The `app.robot` file contains the test definition:

```
*** Settings ***
Resource                      ${KEYWORDS}

*** Test Cases ***
Should Read Version From Shell
    Prepare Machine
    Start Emulation
    Wait For Prompt On Uart   pigweed: codelab Goodbye, World!
```

Running these tests will fail with a helpful message:

```
+++++ Starting test 'app.Should Greet The User'
!!!!! Emulation's state saved to "/home/antmicro/Antmicro/chromium-os/zephyr-pigweed/twister-out/renode_cortex_a53/app.hello.robot//snapshots/app.Should_Greet_The_User.fail0.save"
!!!!! Log saved to "/home/antmicro/Antmicro/chromium-os/zephyr-pigweed/twister-out/renode_cortex_a53/app.hello.robot//logs/app.Should_Greet_The_User.fail0.log"
+++++ Finished test 'app.Should Greet The User' in 14.02 seconds with status failed
      ╔═
      ║ InvalidOperationException: Terminal tester failed!
      ║
      ║ Full report:
      ║ ([host: 2/20/2024 1:34:40 AM, virt:       0] Attached to UART event: success)
      ║ [host: 2/20/2024 1:34:40 AM, virt:      24] *** Booting Zephyr OS build zephyr-v3.5.0-49-g04fd1c40cc9f ***
      ║ [host: 2/20/2024 1:34:40 AM, virt:      24] [00:00:00.007,000] <inf> pigweed: codelab Hello, World!
      ║  [[no newline]]
      ║ ([host: 2/20/2024 1:34:51 AM, virt:  8018.3] Line containing >>pigweed: codelab Goodbye, World!<< event: failure)
```

Robot also creates its own HTML logs in `twister-out/renode_cortex_a53/app.hello.robot/report.html`.

### Running outside of tests

Renode can also be used for more interactive scenarios.

You can run Renode without the test harness:

```shell
$ west build -p -b hifive_unleashed -t run app
```

To enable more visual output, open the file `boards/arm64/renode_cortex_a53/support/cortex_a53.resc` and uncomment the line:
```
showAnalyzer uart0
```

Start Renode with `renode` and enter the following commands:
```
(monitor) set bin @twister-out/renode_cortex_a53/app.hello/zephyr/zephyr.elf
(monitor) i @boards/arm64/renode_cortex_a53/support/cortex_a53.resc
(Cortex A53) s
```

### Extracting more knowledge from simulation

Renode provides multiple tracing features without requiring you to instrument the binary.

Follow the steps above, but before the `s` command run:
```
(Cortex A53) cpu LogFunctionNames true true
```

Add more context with information about peripheral accesses:
```
(Cortex A53) sysbus LogAllPeripheralsAccess true
```

Generate execution trace from a run. You can use either [Speedscope](https://www.speedscope.app/):
```
(Cortex A53) cpu EnableProfilerCollapsedStack $CWD/profile
```

Or you can use [Perfetto](https://ui.perfetto.dev/):
```
(Cortex A53) cpu EnableProfilerPerfetto $CWD/perfetto
```

## Learn more

* [Renode documentation](https://docs.renode.io/)
* [Renode Zephyr Dashboard](https://zephyr-dashboard.renode.io/)
* [Renode U-Boot Dashboard](https://u-boot-dashboard.renode.io/)
* [Antmicro blog](https://antmicro.com/blog/)

## Reach out

If you have questions and would like to learn more how Renode can help you with your project, reach out at [contact@antmicro.com](mailto:contact@antmicro.com)!
