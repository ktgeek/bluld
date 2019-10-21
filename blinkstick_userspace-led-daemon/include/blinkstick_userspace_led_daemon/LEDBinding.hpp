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
#include <memory>

#include <linux/uleds.h>
#include <poll.h>

namespace BlinkstickUserspace
{
class LEDBinding
{
  public:
    LEDBinding(std::string name, uint8_t red = 255, uint8_t green = 0, uint8_t blue = 0);
    LEDBinding(std::string name, std::shared_ptr<void *> blinkLed, uint8_t red = 255, uint8_t green = 0, uint8_t blue = 0);
    ~LEDBinding();

    void registerUserSpaceLED();

    struct pollfd getPollFd();

    int getBrightness();

    std::string getName();

  private:
    uint8_t mRed;
    uint8_t mGreen;
    uint8_t mBlue;

    std::string mName;
    // TODO: Make this a more appropriate pointer when we ge that far.
    std::shared_ptr<void *> mBlinkLed;
    struct uleds_user_dev mUledsUserDevStruct;
    int mULedsFileDescriptor;
};

typedef std::shared_ptr<LEDBinding> LEDBindingPtr;
}
