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
$ west build -p -b native_sim -t run app
```

### qemu_cortex_a53
```shell
$ west build -p -b qemu_cortex_a53 -t run app
```

### renode
```shell
$ west build -p -b renode_cortex_a53 -t run app -- -DBOARD_ROOT="."
```

## Testing

```shell
$ west twister -cvi -A app/boards -x="BOARD_ROOT=." -T app/
```
