
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
#pragma once

#include <cstdint>
#include <map>

#include <blinkstick_userspace_led_daemon/blinkstick_userspace_led_daemon_fwd.hpp>

namespace BlinkstickUserspace
{

typedef std::tuple<uint8_t, uint8_t, uint8_t> RGBTuple;

class RGBColor
{
public:
  RGBColor();

  RGBColor(uint8_t red, uint8_t green, uint8_t blue);

  RGBTuple getValues();

  static RGBColorPtr getFriendlyColor(std::string name);

  std::string toString();

private:
  uint8_t mRed;
  uint8_t mGreen;
  uint8_t mBlue;

  static std::map<std::string, RGBColorPtr> sFriendlyColors;
};
} // namespace BlinkstickUserspace
