# DeviceInterface

This program aims to provide a intuitive way to tinker with USB connected device.

It supports lua scripting to specify the structure of a device (registers, parameters,
flags) and how it should perform io operations.

![](http://i.imgur.com/5vhlBUw.png)

## Installation

You can either compile the code yourself or just download the supplied Appimage,
do a `chmod` and execute it.

For more information regarding fancy Appimages on their [website](http://appimage.org/)

### Compilation

Just use following commands on project root
```
$ qmake && make
```
You can find produced binary in `bin` directory.

#### Requirements

* Qt >=5.7
* libudev

### Appimage

Go to [release page](https://github.com/free-easy/DeviceInterface/releases)
and download the appimage of this program.

Run the following command to make the downloaded file executable.

```sh
$ chmod -x ./DeviceInterface-x86_64.AppImage
```

#### Supported platforms
The appimage has been generated on Ubuntu 16.04 (64-bit), thus it will work:

* **Only** on 64-bit platforms
* Probably only on system with Ubuntu >= 16.04.

## Few words on devices in Linux

This program doesn't handle the way a device gets recognized by the OS, since it's
just a *interface* to a correctly plugged and recognized device.
Now the de-facto device handling on Linux system are done with udev-rules.
For more details see [here](http://www.reactivated.net/writing_udev_rules.html#hierarchy)

There's a example of udev-rule that I use in the `udev_rules` directory.

To apply a `udev-rule` follow these steps:

* Write the rule in a file with `.rules` as extension and a number followed by a hyphen as prefix
(e.g 90-awesome.rules). The bigger the number is the more the rule in the file takes precedence over other rules.
* Move the file in /etc/udev/rules.d/
* **Do not forget**: run `$ udevamd control --reload`. It might require `sudo`.

## TODO

- [x] Use Lua for configuration file
- [ ] Validate the configuration file
- [ ] Implement CommandPanel using MVC pattern
- [ ] Extend configuration to FirmwarePanel as well
- [ ] Create a independent repository for `libdevice` and link it to this project
- [ ] Don't show configuration dependent panels when there's no configuration file loaded.
Thus no need to have a configuration file when launching the program
through git submodule
