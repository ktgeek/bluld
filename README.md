# BlULd - The Blinkstick User space LED daemon

The [Blinkstick](https://www.blinkstick.com) family of products are "Smart LED controllers with integrated USB
firmware." They register as USB HID devices so Linux doesn't recognize them as part of the LED class.  This daemon will
use the Linux user space LED driver to bridge the gap.

My intended use is to bring some "blinking lights" to x86-based router devices running [OpenWRT](https://openwrt.org),
such as the [Protectli](https://protectli.com/6-port/), but it should be generic enough for any Linux machine.

## Using

`bluld` makes the assumption that only one blinkstick device is connected. At launch time you must give it the number of
LEDs on your Blinkstick as well as the colors you would like them to be.  (A list of friendly colors is at the bottom of
this README.)

Example:

```
# bluld 4 aqua indigo olive yellow
```

When `bluld` is running, you should see an entry for each LED in `/sys/class/leds`. From there, you can use the
Blinkstick LEDs like any other registered LED.

## Building

### Requirements

* Linux kernel > 4.10 (this is where /dev/uleds was introduced.)
* hidapi-libusb

### Making

```
# cmake .
# make
```

## Colors

This is a list of friendly color names that `bluld` understands.

* aqua
* aliceblue
* antiquewhite
* black
* blue
* cyan
* darkblue
* darkcyan
* darkgreen
* darkturquoise
* deepskyblue
* green
* lime
* mediumblue
* mediumspringgreen
* navy
* springgreen
* teal
* midnightblue
* dodgerblue
* lightseagreen
* forestgreen
* seagreen
* darkslategray
* limegreen
* mediumseagreen
* turquoise
* royalblue
* steelblue
* darkslateblue
* mediumturquoise
* indigo
* darkolivegreen
* cadetblue
* cornflowerblue
* mediumaquamarine
* dimgray
* slateblue
* olivedrab
* slategray
* lightslategray
* mediumslateblue
* lawngreen
* aquamarine
* chartreuse
* grey
* maroon
* olive
* purple
* lightskyblue
* skyblue
* blueviolet
* darkmagenta
* darkred
* saddlebrown
* darkseagreen
* lightgreen
* mediumpurple
* darkviolet
* palegreen
* darkorchid
* yellowgreen
* sienna
* brown
* darkgray
* greenyellow
* lightblue
* paleturquoise
* lightsteelblue
* powderblue
* firebrick
* darkgoldenrod
* mediumorchid
* rosybrown
* darkkhaki
* silver
* mediumvioletred
* indianred
* peru
* chocolate
* tan
* lightgray
* thistle
* goldenrod
* orchid
* palevioletred
* crimson
* gainsboro
* plum
* burlywood
* lightcyan
* lavender
* darksalmon
* palegoldenrod
* violet
* azure
* honeydew
* khaki
* lightcoral
* sandybrown
* beige
* mintcream
* wheat
* whitesmoke
* ghostwhite
* lightgoldenrodyellow
* linen
* salmon
* oldlace
* bisque
* blanchedalmond
* coral
* cornsilk
* darkorange
* deeppink
* floralwhite
* fuchsia
* gold
* hotpink
* ivory
* lavenderblush
* lemonchiffon
* lightpink
* lightsalmon
* lightyellow
* magenta
* mistyrose
* moccasin
* navajowhite
* orange
* orangered
* papayawhip
* peachpuff
* pink
* red
* seashell
* snow
* tomato
* white
* yellow
* warmwhite

