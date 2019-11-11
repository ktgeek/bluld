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
#include <unistd.h>
#include <poll.h>

#include <hidapi/hidapi.h>

#include <blinkstick_userspace_led_daemon/BluldRunner.hpp>
#include <blinkstick_userspace_led_daemon/RGBColor.hpp>
#include <blinkstick_userspace_led_daemon/BlinkStick.hpp>
#include <blinkstick_userspace_led_daemon/LEDBinding.hpp>
#include <blinkstick_userspace_led_daemon/LEDBindingRegistrationException.hpp>
#include <blinkstick_userspace_led_daemon/BluldInitializationException.hpp>

typedef std::vector<std::string> StringVector;
typedef std::shared_ptr<StringVector> StringVectorPtr;

using namespace BlinkstickUserspace;

BluldRunner::BluldRunner() noexcept
    : mLEDBindings(nullptr)
{
}

BluldRunner::~BluldRunner() noexcept
{
  mLEDBindings = nullptr;
  hid_exit();
}

void BluldRunner::signal_handler(int sig)
{
  if (sig == SIGINT || sig == SIGTERM)
  {
    mKeepRunning = false;
  }
}

std::tuple<size_t, StringVectorPtr> BluldRunner::parse_args(int argc, char **argv)
{
  size_t led_count;
  if (argc < 2)
  {
    led_count = 1;
  }
  else
  {
    led_count = std::stoi(argv[1]);
  }

  StringVectorPtr colorList = StringVectorPtr(new StringVector());

  const size_t argc_size = static_cast<size_t>(argc);

  for (size_t i = 0; (i < led_count) && ((i + 2) < argc_size); i++)
  {
    colorList->push_back(argv[i + 2]);
  }

  return std::tuple<size_t, StringVectorPtr>(led_count, colorList);
}

void BluldRunner::init_led_bindings(const size_t led_count, const StringVectorPtr color_list, BlinkStickPtr blinkstick)
{
  mLEDBindings = LEDBindingVectorPtr(new LEDBindingVector());

  for (size_t i = 0; i < led_count; i++)
  {
    std::string ledName("blinkstick:");

    std::string colorName;
    RGBColorPtr color(nullptr);
    try
    {
      colorName = color_list->at(i);
      color = RGBColor::getFriendlyColor(colorName);
    }
    catch (std::out_of_range &_e)
    {
      colorName = "";
    }

    ledName.append(colorName).append(":").append(std::to_string(i));

    try
    {
      LEDBinding *binding = new LEDBinding(ledName, blinkstick, i, color);
      LEDBindingPtr ledBinding = LEDBindingPtr(binding);
      mLEDBindings->push_back(ledBinding);
    }
    catch (LEDBindingRegistrationException &e)
    {
      std::throw_with_nested(BluldInitializationException("Unable to initialize LED"));
    }
  }
}

void BluldRunner::init(int argc, char **argv)
{
  std::tuple<size_t, StringVectorPtr> args = parse_args(argc, argv);

  hid_init();

  BlinkStickPtr blinkstick = BlinkStick::find();
  if (!blinkstick)
  {
    throw BluldInitializationException("Unable to locate blinkstick");
  }

  init_led_bindings(std::get<0>(args), std::get<1>(args), blinkstick);

  RGBColor::releaseFriendlyColors();
}

void BluldRunner::run()
{
  const size_t bindingsCount = mLEDBindings->size();

  struct pollfd fds[bindingsCount];
  for (unsigned int i = 0; i < bindingsCount; i++)
  {
    fds[i] = mLEDBindings->at(i)->getPollFd();
  }

  mKeepRunning = true;
  while (mKeepRunning)
  {
    int events = poll(fds, bindingsCount, -1);

    if (events == -1 && errno == EINTR)
    {
      continue;
    }

    if (events > 0)
    {
      for (unsigned int i = 0; i < bindingsCount; i++)
      {
        if (fds[i].revents && POLLIN)
        {
          mLEDBindings->at(i)->processBrightnessChange();
        }
      }
    }
  }
}

