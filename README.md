# Sample project for Zephyr + Pigweed

## Environment
```shell
$ west init -l manifest
$ west update
$ source third_party/pigweed/bootstrap.sh
$ pip install -r third_party/zephyr/scripts/requirements.txt
```

## Building

### native_sim
```shell
$ ZEPHYR_TOOLCHAIN_VARIANT=llvm west build -p -b native_sim -t run app
```

### qemu_cortex_a53
```shell
$ ZEPHYR_TOOLCHAIN_VARIANT=zephyr west build -p -b qemu_cortex_a53 -t run app
```

## Testing

```shell
$ west twister -cvi -p native_sim -p qemu_cortex_a53 -T app
```
