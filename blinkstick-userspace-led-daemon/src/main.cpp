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
#include <cstdint>
#include <iostream>
#include <memory>

#include <blinkstick_userspace_led_daemon/RGBColor.hpp>
#include <blinkstick_userspace_led_daemon/LEDBinding.hpp>
#include <blinkstick_userspace_led_daemon/LEDBindingRegistrationException.hpp>
#include <blinkstick_userspace_led_daemon/BlinkStick.hpp>

using namespace BlinkstickUserspace;

typedef std::vector<std::string> StringVector;
typedef std::shared_ptr<StringVector> StringVectorPtr;

LEDBindingVectorPtr init_led_bindings(const size_t led_count, const StringVectorPtr color_list)
{
  BlinkStickPtr blinkstick = BlinkStick::find();

  if (!blinkstick)
  {
    exit(-1);
  }

  LEDBindingVectorPtr ledBindings = LEDBindingVectorPtr(new LEDBindingVector());

  for (size_t i = 0; i < led_count; i++)
  {
    std::string ledName("blinkstick:");

    std::string colorName;
    RGBColorPtr color;
    try
    {
      colorName = color_list->at(i);
      color = RGBColor::getFriendlyColor(colorName);
    }
    catch(std::out_of_range &e)
    {
      colorName = "";
    }

    ledName.append(colorName).append(":").append(std::to_string(i));;

    try
    {
      LEDBinding *binding = new LEDBinding(ledName, blinkstick, i, color);
      LEDBindingPtr ledBinding = LEDBindingPtr(binding);
      ledBindings->push_back(ledBinding);
    }
    catch(LEDBindingRegistrationException &e)
    {
      std::cerr << e.getMessage() << ", errno: " << e.getErrorNo() << std::endl;
    }
  }

  return ledBindings;
}

size_t get_led_count(int argc, char** argv)
{
  if (argc < 2)
  {
    return 1;
  }

  return std::stoi(argv[1]);
}

// This is bad code and I feel bad. When I get to running on OpenWRT I will replace it with calls to uci.
StringVectorPtr get_color_list(const size_t led_count, int argc, char **argv)
{
  StringVectorPtr colorList = StringVectorPtr(new StringVector());

  if (led_count < 1)
  {
    return colorList;
  }


  const size_t argc_size = static_cast<size_t>(argc);

  for (size_t i = 0; (i < led_count) && ((i + 2) < argc_size); i++)
  {
    colorList->push_back(argv[i + 2]);
  }

  return colorList;
}

LEDBindingVectorPtr init_bluld(int argc, char** argv)
{
  const size_t led_count = get_led_count(argc, argv);
  const StringVectorPtr color_list = get_color_list(led_count, argc, argv);

  return init_led_bindings(led_count, color_list);
}

void poll_forever(LEDBindingVectorPtr ledBindings)
{
  const size_t bindingsCount = ledBindings->size();
  struct pollfd fds[bindingsCount];

  for (unsigned int i = 0; i < bindingsCount; i++)
  {
    fds[i] = ledBindings->at(i)->getPollFd();
  }

  while (1)
  {
    int events = poll(fds, bindingsCount, -1);

    if (events > 0)
    {
      for (unsigned int i = 0; i < bindingsCount; i++)
      {
        if (fds[i].revents && POLLIN)
        {
          ledBindings->at(i)->processBrightnessChange();
        }
      }
    }
  }
}

int main(int argc, char** argv)
{
  hid_init();

  LEDBindingVectorPtr ledBindings = init_bluld(argc, argv);

  poll_forever(ledBindings);

  hid_exit();
}
