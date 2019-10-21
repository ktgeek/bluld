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

using namespace BlinkstickUserspace;

BlinkStick::BlinkStick(hid_device* device)
  : mDevice(device)
{
  wchar_t tmpstring[255];
  hid_get_manufacturer_string(device, tmpstring, 255);
  mManufacturer = std::string(std::begin(tmpstring), std::end(tmpstring) - 1);

  hid_get_product_string(device, tmpstring, 255);
  mProduct = std::string(std::begin(tmpstring), std::end(tmpstring) - 1);

  hid_get_serial_number_string(device, tmpstring, 255);
  mSerialNumber = std::string(std::begin(tmpstring), std::end(tmpstring) - 1);
}

BlinkStick::~BlinkStick()
{
}

BlinkStickVectorPtr BlinkStick::find_all()
{
  BlinkStickVectorPtr blinkSticks = BlinkStickVectorPtr(new BlinkStickVector());

  struct hid_device_info *device_info = hid_enumerate(VENDOR_ID, PRODUCT_ID);
  if (device_info == NULL)
  {
    return blinkSticks;
  }

  BlinkStickPtr blinkStick = BlinkStickPtr(new BlinkStick(hid_open_path(device_info->path)));
  blinkSticks->push_back(blinkStick);

  while (device_info = device_info->next)
  {
    blinkStick = BlinkStickPtr(new BlinkStick(hid_open_path(device_info->path)));
    blinkSticks->push_back(blinkStick);
  }

  return blinkSticks;
}

BlinkStickPtr BlinkStick::find()
{
  BlinkStickVectorPtr blinkSticks = find_all();
  if (blinkSticks->size() < 1)
  {
    return BlinkStickPtr(NULL);
  }

  return blinkSticks->front();
}

std::string BlinkStick::getInfoBlock(int id)
{
  unsigned char data[33];
  data[0] = id == 1 ? INFO_BLOCK_1 : INFO_BLOCK_2;
  int read = hid_get_feature_report(mDevice, data, sizeof(data));

  if (read < 2)
  {
    return std::string("");
  }

  std::string result(std::begin(data) + 1, std::end(data));
  return result;
}

void BlinkStick::getColors()
{
  unsigned char data[33];
  data[0] = COLORS;

  int read = hid_get_feature_report(mDevice, data, sizeof(data));
}

std::string BlinkStick::toString()
{
  std::string result = std::string("Manufacturer: ").append(mManufacturer).append("\n");
  result.append("Product: ").append(mProduct).append("\n");
  result.append("Serial Number: ").append(mSerialNumber).append("\n");

  return result;
}
