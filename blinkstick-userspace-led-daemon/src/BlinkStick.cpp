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

#include <blinkstick_userspace_led_daemon/RGBColor.hpp>
#include <blinkstick_userspace_led_daemon/BlinkStick.hpp>
#include <blinkstick_userspace_led_daemon/BlinkStickCommunicationException.hpp>

using namespace BlinkstickUserspace;

BlinkStick::BlinkStick(hid_device *device)
    : mDevice(device)
{
}

BlinkStick::~BlinkStick()
{
  hid_close(mDevice);
}

BlinkStickPtr BlinkStick::find()
{
  BlinkStickVectorPtr blinkSticks = find_all();
  if (blinkSticks->size() < 1)
  {
    return nullptr;
  }

  return blinkSticks->front();
}

BlinkStickVectorPtr BlinkStick::find_all()
{
  BlinkStickVectorPtr blinkSticks = BlinkStickVectorPtr(new BlinkStickVector());

  struct hid_device_info *device_info_base = hid_enumerate(VENDOR_ID, PRODUCT_ID);
  if (!device_info_base)
  {
    return blinkSticks;
  }

  struct hid_device_info *device_info = device_info_base;

  open_hid_and_store(blinkSticks, device_info->path);

  while ((device_info = device_info->next))
  {
    open_hid_and_store(blinkSticks, device_info->path);
  }

  hid_free_enumeration(device_info_base);

  return blinkSticks;
}

void BlinkStick::open_hid_and_store(BlinkStickVectorPtr blinkSticks, char* path)
{
  hid_device *hidDevice = hid_open_path(path);

  if (hidDevice)
  {
    blinkSticks->push_back(BlinkStickPtr(new BlinkStick(hidDevice)));
  }
}

std::string BlinkStick::getManufacturer()
{
  wchar_t tmpstring[255];

  const int result = hid_get_manufacturer_string(mDevice, tmpstring, 255);

  if (result == -1)
  {
    throw BlinkStickCommunicationException("Unable to retrieve Manufacturer");
  }

  return std::string(std::begin(tmpstring), std::end(tmpstring) - 1);
}

std::string BlinkStick::getProduct()
{
  wchar_t tmpstring[255];

  const int result = hid_get_product_string(mDevice, tmpstring, 255);

  if (result == -1)
  {
    throw BlinkStickCommunicationException("Unable to retrieve Product");
  }

  return std::string(std::begin(tmpstring), std::end(tmpstring) - 1);
}

std::string BlinkStick::getSerialNumber()
{
  wchar_t tmpstring[255];

  const int result = hid_get_serial_number_string(mDevice, tmpstring, 255);

  if (result == -1)
  {
    throw BlinkStickCommunicationException("Unable to get serial number");
  }

  return std::string(std::begin(tmpstring), std::end(tmpstring) - 1);
}

std::string BlinkStick::getInfoBlock(int id)
{
  unsigned char data[33];
  data[0] = id == 1 ? INFO_BLOCK_1 : INFO_BLOCK_2;
  const int read = getFeatureReportWithRetry(data, sizeof(data));

  if (read < 2)
  {
    return "";
  }

  std::string result(std::begin(data) + 1, std::end(data));
  return result;
}

RGBColorPtr BlinkStick::getColor()
{
  unsigned char data[4];
  data[0] = FIRST_LED_COLOR;

  const int result = getFeatureReportWithRetry(data, sizeof(data));

  if (result == -1)
  {
    // couldn't read from the stick
    return nullptr;
  }

  return RGBColorPtr(new RGBColor(data[1], data[2], data[3]));
}

RGBColorPtr BlinkStick::getColor(uint8_t index)
{
  if (index == 0)
  {
    return getColor();
  }

  // When we call getColors, we don't what to give it the
  // index we're looking for, but the total number of leds.
  // Since we're 0 based, we need to +1 here.
  RGBColorVectorPtr colors = getColors(index + 1);

  return colors->back();
}

RGBColorVectorPtr BlinkStick::getColors(uint8_t led_count)
{
  RGBColorVectorPtr colors = RGBColorVectorPtr(new RGBColorVector());

  if (led_count == 1)
  {
    colors->push_back(getColor());
    return colors;
  }

  unsigned char report_id;
  int max_leds;
  std::tie(report_id, max_leds) = getReportData(led_count);

  // +2 because 1) report and 2) channel
  unsigned char data[max_leds * 3 + 2];
  data[0] = report_id;

  const int read = getFeatureReportWithRetry(data, sizeof(data));

  if (read < 0)
  {
    return colors;
  }

  for (int i = 2; i <= led_count * 3; i = i + 3)
  {
    // Colors come back from the stick as green, red, blue
    colors->push_back(RGBColorPtr(new RGBColor(data[i + 1], data[i], data[i + 2])));
  }

  return colors;
}

bool BlinkStick::setColor(RGBColorPtr color)
{
  unsigned char data[4];
  data[0] = FIRST_LED_COLOR;

  std::tie(data[1], data[2], data[3]) = color->getValues();

  const int result = sendFeatureReportWithRetry(data, sizeof(data));
  if (result == -1)
  {
    return false;
  }

  return true;
}

bool BlinkStick::setColor(uint8_t index, RGBColorPtr color)
{
  if (index == 0)
  {
    return setColor(color);
  }

  unsigned char data[6] = {0};
  data[0] = OTHER_LED_COLOR;
  // This should be the channel. I've hard coded it for now as I don't really have
  // support for channel yet. (I don't think my Blinkstrick Strip uses it.)
  // data[1] = 0;
  data[2] = index;
  std::tie(data[3], data[4], data[5]) = color->getValues();

  const int result = sendFeatureReportWithRetry(data, sizeof(data));

  if (result == -1)
  {
    return false;
  }

  return true;
}

bool BlinkStick::setColors(uint8_t led_count, RGBColorVectorPtr colors)
{
  if (led_count == 1)
  {
    return setColor(colors->front());
  }

  unsigned char report_id;
  int max_leds;
  std::tie(report_id, max_leds) = getReportData(led_count);

  // +2 because 1) report and 2) channel
  unsigned char data[max_leds * 3 + 2] = {0};
  data[0] = report_id;

  for (int i = 0; i < led_count; i++)
  {
    int base = i * 3 + 2;
    RGBColorPtr color = colors->at(i);
    if (color != nullptr)
    {
      std::tie(data[base + 1], data[base], data[base + 2]) = color->getValues();
    }
  }

  const int result = sendFeatureReportWithRetry(data, sizeof(data));

  if (result == -1)
  {
    return false;
  }

  return true;
}

bool BlinkStick::setOff()
{
  unsigned char data[4] = {0};
  data[0] = FIRST_LED_COLOR;

  const int result = sendFeatureReportWithRetry(data, sizeof(data));

  if (result == -1)
  {
    return false;
  }

  return true;
}

bool BlinkStick::setOff(uint8_t index)
{
  if (index == 0)
  {
    return setOff();
  }

  unsigned char data[6] = {0};
  data[0] = OTHER_LED_COLOR;
  // This should be the channel. I've hard coded it for now as I don't really have
  // support for channel yet. (I don't think my Blinkstrick Strip uses it.)
  // data[1] = 0;
  data[2] = index;

  const int result = sendFeatureReportWithRetry(data, sizeof(data));

  if (result == -1)
  {
    return false;
  }

  return true;
}

bool BlinkStick::setManyOff(uint8_t led_count)
{
  unsigned char report_id;
  int max_leds;
  std::tie(report_id, max_leds) = getReportData(led_count);

  unsigned char data[max_leds * 3 + 2] = {0};
  data[0] = report_id;

  const int result = sendFeatureReportWithRetry(data, sizeof(data));

  if (result == -1)
  {
    return false;
  }

  return true;
}

std::string BlinkStick::toString()
{
  std::string result = std::string("Manufacturer: ").append(getManufacturer()).append("\n");
  result.append("Product: ").append(getProduct()).append("\n");
  result.append("Serial Number: ").append(getSerialNumber()).append("\n");

  return result;
}

BlinkStick::color_report_data BlinkStick::getReportData(uint8_t led_count) noexcept
{
  unsigned char report_id = SIXTY_FOUR_LED_REPORT;
  int max_leds = 64;

  if (led_count > 0 && led_count < 9)
  {
    report_id = EIGHT_LED_REPORT;
    max_leds = 8;
  }

  if (led_count > 8 && led_count < 17)
  {
    report_id = SIXTEEN_LED_REPORT;
    max_leds = 16;
  }

  if (led_count > 16 && led_count < 33)
  {
    report_id = THIRTY_TWO_LED_REPORT;
    max_leds = 32;
  }

  return std::make_tuple(report_id, max_leds);
}

// Back to back quick communication seems to fail sometimes, let's try up to 10 times;
int BlinkStick::sendFeatureReportWithRetry(unsigned char *data, size_t size) noexcept
{
  int result = -1;
  for (int attempt = 0; result < 0 && attempt < COMMUNICATION_RETRY_ATTEMPS; attempt++)
  {
    result = hid_send_feature_report(mDevice, data, size);
  }
  return result;
}

// Back to back quick communication seems to fail, let's do a retry.
int BlinkStick::getFeatureReportWithRetry(unsigned char *data, size_t size) noexcept
{
  int result = -1;
  for (int attempt = 0; result < 0 && attempt < COMMUNICATION_RETRY_ATTEMPS; attempt++)
  {
    result = hid_get_feature_report(mDevice, data, size);
  }

  return result;
}
