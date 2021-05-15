# BlULd - The Blinkstick User space LED daemon

The [Blinkstick](https://www.blinkstick.com) family of products are "Smart LED controllers with integrated USB
firmware." They register as USB HID devices so Linux doesn't recognize them as part of the LED class.  This daemon will
use the Linux user space LED driver to bridge the gap.

I use it to bring some "blinking lights" to x86-based router devices running [OpenWRT](https://openwrt.org),
such as the [Protectli](https://protectli.com/6-port/), but it should be generic enough for any Linux machine.

## Using

`bluld` makes the assumption that only one blinkstick device is connected. At launch time you must give it the number of
LEDs on your Blinkstick as well as the colors you would like them to be. You can use friendly color names, or pass a hex
value that MUST be prepented with `#`. (A list of friendly colors that bluld knows is at the bottom of this README.)

Example:

```
# bluld 5 aqua indigo olive yellow #010203
```

When `bluld` is running, you should see an entry for each LED in `/sys/class/leds` named `blinkstick:<number>` where
number is the number of the led, as in `blinkstick:2`. From there, you can use the Blinkstick LEDs like any other
registered LED.

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

* aqua ![#00ffff](https://via.placeholder.com/15/00ffff/000000?text=+) `#00ffff`
* aliceblue ![#f0f8ff](https://via.placeholder.com/15/f0f8ff/000000?text=+) `#f0f8ff`
* antiquewhite ![#faebd7](https://via.placeholder.com/15/faebd7/000000?text=+) `#faebd7`
* black ![#000000](https://via.placeholder.com/15/000000/000000?text=+) `#000000`
* blue ![#0000ff](https://via.placeholder.com/15/0000ff/000000?text=+) `#0000ff`
* cyan ![#00ffff](https://via.placeholder.com/15/00ffff/000000?text=+) `#00ffff`
* darkblue ![#00008b](https://via.placeholder.com/15/00008b/000000?text=+) `#00008b`
* darkcyan ![#008b8b](https://via.placeholder.com/15/008b8b/000000?text=+) `#008b8b`
* darkgreen ![#006400](https://via.placeholder.com/15/006400/000000?text=+) `#006400`
* darkturquoise ![#00ced1](https://via.placeholder.com/15/00ced1/000000?text=+) `#00ced1`
* deepskyblue ![#00bfff](https://via.placeholder.com/15/00bfff/000000?text=+) `#00bfff`
* green ![#008000](https://via.placeholder.com/15/008000/000000?text=+) `#008000`
* lime ![#00ff00](https://via.placeholder.com/15/00ff00/000000?text=+) `#00ff00`
* mediumblue ![#0000cd](https://via.placeholder.com/15/0000cd/000000?text=+) `#0000cd`
* mediumspringgreen ![#00fa9a](https://via.placeholder.com/15/00fa9a/000000?text=+) `#00fa9a`
* navy ![#000080](https://via.placeholder.com/15/000080/000000?text=+) `#000080`
* springgreen ![#00ff7f](https://via.placeholder.com/15/00ff7f/000000?text=+) `#00ff7f`
* teal ![#008080](https://via.placeholder.com/15/008080/000000?text=+) `#008080`
* midnightblue ![#191970](https://via.placeholder.com/15/191970/000000?text=+) `#191970`
* dodgerblue ![#1e90ff](https://via.placeholder.com/15/1e90ff/000000?text=+) `#1e90ff`
* lightseagreen ![#20b2aa](https://via.placeholder.com/15/20b2aa/000000?text=+) `#20b2aa`
* forestgreen ![#228b22](https://via.placeholder.com/15/228b22/000000?text=+) `#228b22`
* seagreen ![#2e8b57](https://via.placeholder.com/15/2e8b57/000000?text=+) `#2e8b57`
* darkslategrey ![#2f4f4f](https://via.placeholder.com/15/2f4f4f/000000?text=+) `#2f4f4f`
* limegreen ![#32cd32](https://via.placeholder.com/15/32cd32/000000?text=+) `#32cd32`
* mediumseagreen ![#3cb371](https://via.placeholder.com/15/3cb371/000000?text=+) `#3cb371`
* turquoise ![#40e0d0](https://via.placeholder.com/15/40e0d0/000000?text=+) `#40e0d0`
* royalblue ![#4169e1](https://via.placeholder.com/15/4169e1/000000?text=+) `#4169e1`
* steelblue ![#4682b4](https://via.placeholder.com/15/4682b4/000000?text=+) `#4682b4`
* darkslateblue ![#483d8b](https://via.placeholder.com/15/483d8b/000000?text=+) `#483d8b`
* mediumturquoise ![#48d1cc](https://via.placeholder.com/15/48d1cc/000000?text=+) `#48d1cc`
* indigo ![#4b0082](https://via.placeholder.com/15/4b0082/000000?text=+) `#4b0082`
* darkolivegreen ![#556b2f](https://via.placeholder.com/15/556b2f/000000?text=+) `#556b2f`
* cadetblue ![#5f9ea0](https://via.placeholder.com/15/5f9ea0/000000?text=+) `#5f9ea0`
* cornflowerblue ![#6495ed](https://via.placeholder.com/15/6495ed/000000?text=+) `#6495ed`
* mediumaquamarine ![#66cdaa](https://via.placeholder.com/15/66cdaa/000000?text=+) `#66cdaa`
* dimgrey ![#696969](https://via.placeholder.com/15/696969/000000?text=+) `#696969`
* slateblue ![#6a5acd](https://via.placeholder.com/15/6a5acd/000000?text=+) `#6a5acd`
* olivedrab ![#6b8e23](https://via.placeholder.com/15/6b8e23/000000?text=+) `#6b8e23`
* slategrey ![#708090](https://via.placeholder.com/15/708090/000000?text=+) `#708090`
* lightslategrey ![#778899](https://via.placeholder.com/15/778899/000000?text=+) `#778899`
* mediumslateblue ![#7b68ee](https://via.placeholder.com/15/7b68ee/000000?text=+) `#7b68ee`
* lawngreen ![#7cfc00](https://via.placeholder.com/15/7cfc00/000000?text=+) `#7cfc00`
* aquamarine ![#7fffd4](https://via.placeholder.com/15/7fffd4/000000?text=+) `#7fffd4`
* chartreuse ![#7fff00](https://via.placeholder.com/15/7fff00/000000?text=+) `#7fff00`
* grey ![#808080](https://via.placeholder.com/15/808080/000000?text=+) `#808080`
* maroon ![#800000](https://via.placeholder.com/15/800000/000000?text=+) `#800000`
* olive ![#808000](https://via.placeholder.com/15/808000/000000?text=+) `#808000`
* purple ![#800080](https://via.placeholder.com/15/800080/000000?text=+) `#800080`
* lightskyblue ![#87cefa](https://via.placeholder.com/15/87cefa/000000?text=+) `#87cefa`
* skyblue ![#87ceeb](https://via.placeholder.com/15/87ceeb/000000?text=+) `#87ceeb`
* blueviolet ![#8a2be2](https://via.placeholder.com/15/8a2be2/000000?text=+) `#8a2be2`
* darkmagenta ![#8b008b](https://via.placeholder.com/15/8b008b/000000?text=+) `#8b008b`
* darkred ![#8b0000](https://via.placeholder.com/15/8b0000/000000?text=+) `#8b0000`
* saddlebrown ![#8b4513](https://via.placeholder.com/15/8b4513/000000?text=+) `#8b4513`
* darkseagreen ![#8fbc8f](https://via.placeholder.com/15/8fbc8f/000000?text=+) `#8fbc8f`
* lightgreen ![#90ee90](https://via.placeholder.com/15/90ee90/000000?text=+) `#90ee90`
* mediumpurple ![#9370db](https://via.placeholder.com/15/9370db/000000?text=+) `#9370db`
* darkviolet ![#9400d3](https://via.placeholder.com/15/9400d3/000000?text=+) `#9400d3`
* palegreen ![#98fb98](https://via.placeholder.com/15/98fb98/000000?text=+) `#98fb98`
* darkorchid ![#9932cc](https://via.placeholder.com/15/9932cc/000000?text=+) `#9932cc`
* yellowgreen ![#9acd32](https://via.placeholder.com/15/9acd32/000000?text=+) `#9acd32`
* sienna ![#a0522d](https://via.placeholder.com/15/a0522d/000000?text=+) `#a0522d`
* brown ![#a52a2a](https://via.placeholder.com/15/a52a2a/000000?text=+) `#a52a2a`
* darkgrey ![#a9a9a9](https://via.placeholder.com/15/a9a9a9/000000?text=+) `#a9a9a9`
* greenyellow ![#adff2f](https://via.placeholder.com/15/adff2f/000000?text=+) `#adff2f`
* lightblue ![#add8e6](https://via.placeholder.com/15/add8e6/000000?text=+) `#add8e6`
* paleturquoise ![#afeeee](https://via.placeholder.com/15/afeeee/000000?text=+) `#afeeee`
* lightsteelblue ![#b0c4de](https://via.placeholder.com/15/b0c4de/000000?text=+) `#b0c4de`
* powderblue ![#b0e0e6](https://via.placeholder.com/15/b0e0e6/000000?text=+) `#b0e0e6`
* firebrick ![#b22222](https://via.placeholder.com/15/b22222/000000?text=+) `#b22222`
* darkgoldenrod ![#b8860b](https://via.placeholder.com/15/b8860b/000000?text=+) `#b8860b`
* mediumorchid ![#ba55d3](https://via.placeholder.com/15/ba55d3/000000?text=+) `#ba55d3`
* rosybrown ![#bc8f8f](https://via.placeholder.com/15/bc8f8f/000000?text=+) `#bc8f8f`
* darkkhaki ![#bdb76b](https://via.placeholder.com/15/bdb76b/000000?text=+) `#bdb76b`
* silver ![#c0c0c0](https://via.placeholder.com/15/c0c0c0/000000?text=+) `#c0c0c0`
* mediumvioletred ![#c71585](https://via.placeholder.com/15/c71585/000000?text=+) `#c71585`
* indianred ![#cd5c5c](https://via.placeholder.com/15/cd5c5c/000000?text=+) `#cd5c5c`
* peru ![#cd853f](https://via.placeholder.com/15/cd853f/000000?text=+) `#cd853f`
* chocolate ![#d2691e](https://via.placeholder.com/15/d2691e/000000?text=+) `#d2691e`
* tan ![#d2b48c](https://via.placeholder.com/15/d2b48c/000000?text=+) `#d2b48c`
* lightgrey ![#d3d3d3](https://via.placeholder.com/15/d3d3d3/000000?text=+) `#d3d3d3`
* thistle ![#d8bfd8](https://via.placeholder.com/15/d8bfd8/000000?text=+) `#d8bfd8`
* goldenrod ![#daa520](https://via.placeholder.com/15/daa520/000000?text=+) `#daa520`
* orchid ![#da70d6](https://via.placeholder.com/15/da70d6/000000?text=+) `#da70d6`
* palevioletred ![#db7093](https://via.placeholder.com/15/db7093/000000?text=+) `#db7093`
* crimson ![#dc143c](https://via.placeholder.com/15/dc143c/000000?text=+) `#dc143c`
* gainsboro ![#dcdcdc](https://via.placeholder.com/15/dcdcdc/000000?text=+) `#dcdcdc`
* plum ![#dda0dd](https://via.placeholder.com/15/dda0dd/000000?text=+) `#dda0dd`
* burlywood ![#deb887](https://via.placeholder.com/15/deb887/000000?text=+) `#deb887`
* lightcyan ![#e0ffff](https://via.placeholder.com/15/e0ffff/000000?text=+) `#e0ffff`
* lavender ![#e6e6fa](https://via.placeholder.com/15/e6e6fa/000000?text=+) `#e6e6fa`
* darksalmon ![#e9967a](https://via.placeholder.com/15/e9967a/000000?text=+) `#e9967a`
* palegoldenrod ![#eee8aa](https://via.placeholder.com/15/eee8aa/000000?text=+) `#eee8aa`
* violet ![#ee82ee](https://via.placeholder.com/15/ee82ee/000000?text=+) `#ee82ee`
* azure ![#f0ffff](https://via.placeholder.com/15/f0ffff/000000?text=+) `#f0ffff`
* honeydew ![#f0fff0](https://via.placeholder.com/15/f0fff0/000000?text=+) `#f0fff0`
* khaki ![#f0e68c](https://via.placeholder.com/15/f0e68c/000000?text=+) `#f0e68c`
* lightcoral ![#f08080](https://via.placeholder.com/15/f08080/000000?text=+) `#f08080`
* sandybrown ![#f4a460](https://via.placeholder.com/15/f4a460/000000?text=+) `#f4a460`
* beige ![#f5f5dc](https://via.placeholder.com/15/f5f5dc/000000?text=+) `#f5f5dc`
* mintcream ![#f5fffa](https://via.placeholder.com/15/f5fffa/000000?text=+) `#f5fffa`
* wheat ![#f5deb3](https://via.placeholder.com/15/f5deb3/000000?text=+) `#f5deb3`
* whitesmoke ![#f5f5f5](https://via.placeholder.com/15/f5f5f5/000000?text=+) `#f5f5f5`
* ghostwhite ![#f8f8ff](https://via.placeholder.com/15/f8f8ff/000000?text=+) `#f8f8ff`
* lightgoldenrodyellow ![#fafad2](https://via.placeholder.com/15/fafad2/000000?text=+) `#fafad2`
* linen ![#faf0e6](https://via.placeholder.com/15/faf0e6/000000?text=+) `#faf0e6`
* salmon ![#fa8072](https://via.placeholder.com/15/fa8072/000000?text=+) `#fa8072`
* oldlace ![#fdf5e6](https://via.placeholder.com/15/fdf5e6/000000?text=+) `#fdf5e6`
* bisque ![#ffe4c4](https://via.placeholder.com/15/ffe4c4/000000?text=+) `#ffe4c4`
* blanchedalmond ![#ffebcd](https://via.placeholder.com/15/ffebcd/000000?text=+) `#ffebcd`
* coral ![#ff7f50](https://via.placeholder.com/15/ff7f50/000000?text=+) `#ff7f50`
* cornsilk ![#fff8dc](https://via.placeholder.com/15/fff8dc/000000?text=+) `#fff8dc`
* darkorange ![#ff8c00](https://via.placeholder.com/15/ff8c00/000000?text=+) `#ff8c00`
* deeppink ![#ff1493](https://via.placeholder.com/15/ff1493/000000?text=+) `#ff1493`
* floralwhite ![#fffaf0](https://via.placeholder.com/15/fffaf0/000000?text=+) `#fffaf0`
* fuchsia ![#ff00ff](https://via.placeholder.com/15/ff00ff/000000?text=+) `#ff00ff`
* gold ![#ffd700](https://via.placeholder.com/15/ffd700/000000?text=+) `#ffd700`
* hotpink ![#ff69b4](https://via.placeholder.com/15/ff69b4/000000?text=+) `#ff69b4`
* ivory ![#fffff0](https://via.placeholder.com/15/fffff0/000000?text=+) `#fffff0`
* lavenderblush ![#fff0f5](https://via.placeholder.com/15/fff0f5/000000?text=+) `#fff0f5`
* lemonchiffon ![#fffacd](https://via.placeholder.com/15/fffacd/000000?text=+) `#fffacd`
* lightpink ![#ffb6c1](https://via.placeholder.com/15/ffb6c1/000000?text=+) `#ffb6c1`
* lightsalmon ![#ffa07a](https://via.placeholder.com/15/ffa07a/000000?text=+) `#ffa07a`
* lightyellow ![#ffffe0](https://via.placeholder.com/15/ffffe0/000000?text=+) `#ffffe0`
* magenta ![#ff00ff](https://via.placeholder.com/15/ff00ff/000000?text=+) `#ff00ff`
* mistyrose ![#ffe4e1](https://via.placeholder.com/15/ffe4e1/000000?text=+) `#ffe4e1`
* moccasin ![#ffe4b5](https://via.placeholder.com/15/ffe4b5/000000?text=+) `#ffe4b5`
* navajowhite ![#ffdead](https://via.placeholder.com/15/ffdead/000000?text=+) `#ffdead`
* orange ![#ffa500](https://via.placeholder.com/15/ffa500/000000?text=+) `#ffa500`
* orangered ![#ff4500](https://via.placeholder.com/15/ff4500/000000?text=+) `#ff4500`
* papayawhip ![#ffefd5](https://via.placeholder.com/15/ffefd5/000000?text=+) `#ffefd5`
* peachpuff ![#ffdab9](https://via.placeholder.com/15/ffdab9/000000?text=+) `#ffdab9`
* pink ![#ffc0cb](https://via.placeholder.com/15/ffc0cb/000000?text=+) `#ffc0cb`
* red ![#ff0000](https://via.placeholder.com/15/ff0000/000000?text=+) `#ff0000`
* seashell ![#fff5ee](https://via.placeholder.com/15/fff5ee/000000?text=+) `#fff5ee`
* snow ![#fffafa](https://via.placeholder.com/15/fffafa/000000?text=+) `#fffafa`
* tomato ![#ff6347](https://via.placeholder.com/15/ff6347/000000?text=+) `#ff6347`
* white ![#ffffff](https://via.placeholder.com/15/ffffff/000000?text=+) `#ffffff`
* yellow ![#ffff00](https://via.placeholder.com/15/ffff00/000000?text=+) `#ffff00`
* warmwhite ![#fdf5e6](https://via.placeholder.com/15/fdf5e6/000000?text=+) `#fdf5e6`
