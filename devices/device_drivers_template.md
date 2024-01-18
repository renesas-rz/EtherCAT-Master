Device Drivers                                           {#devicedrivers}
==============

This table contains a list of all available native drivers,
depending on the kernel version.

The `generic` and the `ccat` driver are independent of the kernel version.

To find out which native driver is required for your network card,
you can use `lspci -vv` or look in `/sys`:
```sh
admin@ipc:~> ls -l /sys/class/net/eth5/device/driver
lrwxrwxrwx 1 root root 0  6. Nov 15:35 /sys/class/net/eth5/device/driver -> ../../../../bus/pci/drivers/e1000
```
or
```sh
admin@ipc:~> basename $(readlink /sys/class/net/eth5/device/driver)
e1000
```

In this example, `eth5` uses the `e1000` driver.
