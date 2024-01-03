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
