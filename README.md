# BlULB - The Blinkstick User-space LED Daemon

The [Blinkstick](https://www.blinkstick.com) family of products are "Smart LED controllers with integrated USB firmware." They register as USB HID devices so Linux doesn't recognize them as part of the LED class.  This deamon will use the Linux userspace LED driver to bridge the gap.

My intended use is to bring some "blinking lights" to x86-based router devices running [OpenWRT](https://openwrt.org),
such as the [Protectli](https://protectli.com/6-port/), but it should be generic enough for any Linux machine.

*This is very much an early work in progress and not ready for use.  It doesn't even have a build system yet!*
