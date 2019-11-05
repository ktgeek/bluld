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

#include <memory>

#include <poll.h>
#include <signal.h>

#include <blinkstick_userspace_led_daemon/blinkstick_userspace_led_daemon_fwd.hpp>

namespace BlinkstickUserspace
{
class BlubdRunner
{
  public:
    BlubdRunner() noexcept;
    ~BlubdRunner() noexcept;

    void init(int argc, char** argv);
    void run();
    // void run2();
    void signal_handler(int sig);

  private:
    std::tuple<size_t, StringVectorPtr> parse_args(int argc, char **argv);
    void init_led_bindings(const size_t led_count, const StringVectorPtr color_list, BlinkStickPtr blinkstick);

    LEDBindingVectorPtr mLEDBindings;
    bool mKeepRunning;
};
} // namespace BlinkstickUserspace
