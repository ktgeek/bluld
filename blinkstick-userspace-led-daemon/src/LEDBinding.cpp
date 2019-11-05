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
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <errno.h>
#include <iostream>

#include <blinkstick_userspace_led_daemon/LEDBinding.hpp>
#include <blinkstick_userspace_led_daemon/BlinkStick.hpp>
#include <blinkstick_userspace_led_daemon/RGBColor.hpp>
#include <blinkstick_userspace_led_daemon/LEDBindingRegistrationException.hpp>

using namespace BlinkstickUserspace;

LEDBinding::LEDBinding(std::string name, BlinkStickPtr blinkstick, uint8_t index, RGBColorPtr color)
    : mName(name), mBlinkstick(blinkstick), mIndex(index), mColor(color)
{
  if (!mColor)
  {
    mColor = RGBColor::getFriendlyColor("red");
  }

  registerUserSpaceLED();
}

LEDBinding::~LEDBinding()
{
  setOff();
  close(mULedsFileDescriptor);
}

void LEDBinding::registerUserSpaceLED()
{
  struct uleds_user_dev dev;
  strncpy(dev.name, mName.c_str(), LED_MAX_NAME_SIZE);
  dev.max_brightness = 100;

  mULedsFileDescriptor = open("/dev/uleds", O_RDWR);

  if (mULedsFileDescriptor == -1)
  {
    throw LEDBindingRegistrationException(errno, "Unable to open /dev/uleds");
  }

  const ssize_t written = write(mULedsFileDescriptor, &dev, sizeof(dev));
  if (written == -1)
  {
    throw LEDBindingRegistrationException(errno, "Unable to open /dev/uleds");
  }
}

struct pollfd LEDBinding::getPollFd() noexcept
{
  struct pollfd fd;
  fd.fd = mULedsFileDescriptor;
  fd.events = POLLIN;

  return fd;
}

int LEDBinding::getBrightness()
{
  int returnVal;
  const ssize_t dataRead = read(mULedsFileDescriptor, &returnVal, sizeof(returnVal));

  // TODO: throw an exception in this case
  if (dataRead < 1)
  {
    return 0;
  }

  return returnVal;
}

bool LEDBinding::setOn()
{
  return mBlinkstick->setColor(mIndex, mColor);
}

bool LEDBinding::setOff()
{
  return mBlinkstick->setOff(mIndex);
}

bool LEDBinding::processBrightnessChange()
{
  const int brightness = getBrightness();

  if (brightness)
  {
    return setOn();
  }
  else
  {
    return setOff();
  }
}

std::string LEDBinding::getName() noexcept
{
  return mName;
}
