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
  BlinkStick(hid_device *device);
  ~BlinkStick();

  static BlinkStickPtr find();
  static BlinkStickVectorPtr find_all();

  std::string getManufacturer();
  std::string getProduct();
  std::string getSerialNumber();
  std::string getInfoBlock(int id);

  RGBColorPtr getColor();
  RGBColorPtr getColor(uint8_t index);
  RGBColorVectorPtr getColors(uint8_t led_count = 8);

  bool setColor(RGBColorPtr color);
  bool setColor(uint8_t index, RGBColorPtr color);
  bool setColors(uint8_t led_count, RGBColorVectorPtr colors);

  bool setOff();
  bool setOff(uint8_t index);
  bool setManyOff(uint8_t led_count = 8);

  std::string toString();

private:
  static const int VENDOR_ID = 0x20a0;
  static const int PRODUCT_ID = 0x41e5;

  static const uint8_t FIRST_LED_COLOR = 0x1;
  static const uint8_t INFO_BLOCK_1 = 0x2;
  static const uint8_t INFO_BLOCK_2 = 0x3;
  static const uint8_t MODE = 0x4;
  static const uint8_t OTHER_LED_COLOR = 0x5;
  static const uint8_t EIGHT_LED_REPORT = 0x6;
  static const uint8_t SIXTEEN_LED_REPORT = 0x7;
  static const uint8_t THIRTY_TWO_LED_REPORT = 0x8;
  static const uint8_t SIXTY_FOUR_LED_REPORT = 0x9;

  static const int COMMUNICATION_RETRY_ATTEMPS = 10;

  static void open_hid_and_store(BlinkStickVectorPtr, char* path);

  typedef std::tuple<unsigned char, int> color_report_data;
  color_report_data getReportData(uint8_t led_count);
  int sendFeatureReportWithRetry(unsigned char *data, size_t size);
  int getFeatureReportWithRetry(unsigned char *data, size_t size);

  hid_device *mDevice;
};

} // namespace BlinkstickUserspace
