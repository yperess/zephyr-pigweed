# Sample project for Zephyr + Pigweed

## Environment

```shell
$ git clone git@github.com:google/pigweed.git third_party/pigweed
$ source third_party/pigweed/bootstrap.sh
$ pw package install zephyr
```

Pigweed provides a way to get both the Pigweed and Zephyr nodes for the West manifest. This is done
via a call to:

```shell
$ pw zephyr manifest
```

We can take output and place it into `manifest/west.yml` along with any other modules we'd like for
our application. At this point, we can also make changes to the fixed commit of Pigweed or the repo
of Zephyr (if we want to change away  from the default one used by Pigweed). This demo does switch
to the main Zephyr repo since some changes are in the release candidates of 3.6 and aren't yet in
the Pigweed fork. Once we're ready, we can run:

```shell
$ west init -l manifest
$ west update
```

Next, we want to use our project root directory as an entry point where we can have common code like
libraries, boards, and configurations. We will do this by adding a `module.yml` file inside a
`manifest/zephyr/` directory:

```yaml
build:
  # Path to the Kconfig file that will be sourced into Zephyr Kconfig tree under
  # Zephyr > Modules > {module_name}. Path is relative from where the west.yml
  # file is located.
  kconfig: ../Kconfig
  # Path to the folder that contains the CMakeLists.txt file to be included by
  # Zephyr build system. The `../` is the root of this repository.
  cmake: ../
```

## Application code

### The `hello_world` library
We're now ready for the application code. We'll start by creating a library under `lib/`. Normally, under Zephyr this
would look like:

```cmake
zephyr_library_named(hello_world)
zephyr_library_sources(include/hello.h src/hello.cc)
# Can't use zephyr_library_include_directories() because it makes the dirs PRIVATE
target_include_directories(hello_world PUBLIC include)
# Can't use zephyr_library_link_libraries() because it makes the libraries PRIVATE
target_link_libraries(hello_world PUBLIC pw_string)
```

Instead, we're able to leverage Pigweed's build tooling and create:

```cmake
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
```

### The application
For our main application we'll allocate a `pw::StringBuffer`, generate a welcome message, then log it via
`PW_LOG_INFO()`. All this can be found in `app/src/main.cc`. The primary CMake file here sets up the project,
adds the sources, and links the `hello_world` library we created.

We can run this application via:
```shell
$ west build -p -b native_sim -t run app/
```

## Adding tests
Side by side with the code, we're going to add a `test_hello.cc` which will get compiled via the CMake function
`pw_add_test()` and linked into `app` by adding `hello_world.test.lib` as a dependency. The test uses gTest APIs
to verify the behavior of `app::WelcomeMessage()`.

### Run the test
```shell
$ west twister -cvi -T app/
```

At this point the test should pass, but if you look closely at the implementation, it's clearly
flawed. We'll fix it later in the Embedded C++101 section below.

## Testing on more targets
Zephyr comes with several QEMU targets. To run our tests against them, we don't need to change anything except for
adding the new targets to the `testcase.yaml` file:

```yaml
platform_allow:
  - qemu_riscv64
  - qemu_cortex_a53
```

We can now run the tests again via the same `west twister ...` command as before and see the new runs.
