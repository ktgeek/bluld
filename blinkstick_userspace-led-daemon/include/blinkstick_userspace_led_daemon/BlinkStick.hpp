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

#include <hidapi/hidapi.h>

#include <blinkstick_userspace_led_daemon/blinkstick_userspace_led_daemon_fwd.hpp>

namespace BlinkstickUserspace
{
class BlinkStick
{
  public:
    BlinkStick(hid_device* device);
    ~BlinkStick();

    static BlinkStickPtr find();
    static BlinkStickVectorPtr find_all();

    std::string getInfoBlock(int id);
    void getColors();

    std::string toString();

  private:
    static int const VENDOR_ID = 0x20a0;
    static int const PRODUCT_ID = 0x41e5;

    static int const COLORS = 0x1;
    static int const INFO_BLOCK_1 = 0x2;
    static int const INFO_BLOCK_2 = 0x3;
    static int const MODE = 0x4;

    std::string mManufacturer;
    std::string mProduct;
    std::string mSerialNumber;

    hid_device* mDevice;
};

} // namespace BlinkstickUserspace
