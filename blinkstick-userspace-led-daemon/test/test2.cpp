// MIT License
//
// Copyright (c) 2019 Keith T. Garner
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include <blinkstick_userspace_led_daemon/BlinkStick.hpp>
#include <blinkstick_userspace_led_daemon/RGBColor.hpp>

#include <unistd.h>

using namespace BlinkstickUserspace;

int main()
{
  BlinkStickVectorPtr blinkSticks = BlinkStick::find_all();

  printf("We found %ld blinkstick(s)\n", blinkSticks->size());
  int count = 0;
  for (BlinkStickPtr blinkStick : *blinkSticks)
  {
    printf("Blinkstick %d\n", ++count);
    printf("%s\n", blinkStick->toString().c_str());
    printf("  InfoBlock1: %s\n", blinkStick->getInfoBlock(1).c_str());

    blinkStick->setManyOff(8);

    RGBColorVectorPtr setColors = RGBColorVectorPtr(new RGBColorVector());
    setColors->push_back(RGBColor::getFriendlyColor("aqua"));
    setColors->push_back(RGBColor::getFriendlyColor("lime"));
    setColors->push_back(RGBColor::getFriendlyColor("teal"));
    setColors->push_back(RGBColor::getFriendlyColor("indigo"));
    setColors->push_back(RGBColor::getFriendlyColor("mistyrose"));
    setColors->push_back(RGBColor::getFriendlyColor("orange"));
    setColors->push_back(RGBColor::getFriendlyColor("snow"));
    blinkStick->setColors(7, setColors);

    RGBColorVectorPtr colors = blinkStick->getColors();
    printf("Colors: ");
    for (RGBColorPtr color : *colors)
    {
      printf("%s ", color->toString().c_str());
    }
    printf("\n");

    blinkStick->setManyOff(8);

    blinkStick->setColor(0, RGBColor::getFriendlyColor("aqua"));
    blinkStick->setColor(4, RGBColor::getFriendlyColor("mistyrose"));
    printf("%s\n", blinkStick->getColor(0)->toString().c_str());
    printf("%s\n", blinkStick->getColor(4)->toString().c_str());

    blinkStick->setManyOff(8);
  }
}
