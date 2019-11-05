
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
#include <linux/uleds.h>
#include <poll.h>

#include <blinkstick_userspace_led_daemon/blinkstick_userspace_led_daemon_fwd.hpp>

namespace BlinkstickUserspace
{
class LEDBinding
{
public:
  LEDBinding(std::string name, BlinkStickPtr blinkstick, uint8_t index, RGBColorPtr color = nullptr);
  ~LEDBinding();

  struct pollfd getPollFd() noexcept;

  int getBrightness();

  bool setOn();
  bool setOff();

  bool processBrightnessChange();

  std::string getName() noexcept;

private:
  void registerUserSpaceLED();

  std::string mName;
  BlinkStickPtr mBlinkstick;
  uint8_t mIndex;
  RGBColorPtr mColor;
  int mULedsFileDescriptor;
};
} // namespace BlinkstickUserspace
