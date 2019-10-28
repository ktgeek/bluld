
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

using namespace BlinkstickUserspace;

const std::map<std::string, RGBColorPtr> RGBColor::sFriendlyColors = {
    {"aqua", RGBColorPtr(new RGBColor(0x00, 0xff, 0xff))},
    {"aliceblue", RGBColorPtr(new RGBColor(0xf0, 0xf8, 0xff))},
    {"antiquewhite", RGBColorPtr(new RGBColor(0xfa, 0xeb, 0xd7))},
    {"black", RGBColorPtr(new RGBColor(0x00, 0x00, 0x00))},
    {"blue", RGBColorPtr(new RGBColor(0x00, 0x00, 0xff))},
    {"cyan", RGBColorPtr(new RGBColor(0x00, 0xff, 0xff))},
    {"darkblue", RGBColorPtr(new RGBColor(0x00, 0x00, 0x8b))},
    {"darkcyan", RGBColorPtr(new RGBColor(0x00, 0x8b, 0x8b))},
    {"darkgreen", RGBColorPtr(new RGBColor(0x00, 0x64, 0x00))},
    {"darkturquoise", RGBColorPtr(new RGBColor(0x00, 0xce, 0xd1))},
    {"deepskyblue", RGBColorPtr(new RGBColor(0x00, 0xbf, 0xff))},
    {"green", RGBColorPtr(new RGBColor(0x00, 0x80, 0x00))},
    {"lime", RGBColorPtr(new RGBColor(0x00, 0xff, 0x00))},
    {"mediumblue", RGBColorPtr(new RGBColor(0x00, 0x00, 0xcd))},
    {"mediumspringgreen", RGBColorPtr(new RGBColor(0x00, 0xfa, 0x9a))},
    {"navy", RGBColorPtr(new RGBColor(0x00, 0x00, 0x80))},
    {"springgreen", RGBColorPtr(new RGBColor(0x00, 0xff, 0x7f))},
    {"teal", RGBColorPtr(new RGBColor(0x00, 0x80, 0x80))},
    {"midnightblue", RGBColorPtr(new RGBColor(0x19, 0x19, 0x70))},
    {"dodgerblue", RGBColorPtr(new RGBColor(0x1e, 0x90, 0xff))},
    {"lightseagreen", RGBColorPtr(new RGBColor(0x20, 0xb2, 0xaa))},
    {"forestgreen", RGBColorPtr(new RGBColor(0x22, 0x8b, 0x22))},
    {"seagreen", RGBColorPtr(new RGBColor(0x2e, 0x8b, 0x57))},
    {"darkslategrey", RGBColorPtr(new RGBColor(0x2f, 0x4f, 0x4f))},
    {"limegreen", RGBColorPtr(new RGBColor(0x32, 0xcd, 0x32))},
    {"mediumseagreen", RGBColorPtr(new RGBColor(0x3c, 0xb3, 0x71))},
    {"turquoise", RGBColorPtr(new RGBColor(0x40, 0xe0, 0xd0))},
    {"royalblue", RGBColorPtr(new RGBColor(0x41, 0x69, 0xe1))},
    {"steelblue", RGBColorPtr(new RGBColor(0x46, 0x82, 0xb4))},
    {"darkslateblue", RGBColorPtr(new RGBColor(0x48, 0x3d, 0x8b))},
    {"mediumturquoise", RGBColorPtr(new RGBColor(0x48, 0xd1, 0xcc))},
    {"indigo", RGBColorPtr(new RGBColor(0x4b, 0x00, 0x82))},
    {"darkolivegreen", RGBColorPtr(new RGBColor(0x55, 0x6b, 0x2f))},
    {"cadetblue", RGBColorPtr(new RGBColor(0x5f, 0x9e, 0xa0))},
    {"cornflowerblue", RGBColorPtr(new RGBColor(0x64, 0x95, 0xed))},
    {"mediumaquamarine", RGBColorPtr(new RGBColor(0x66, 0xcd, 0xaa))},
    {"dimgrey", RGBColorPtr(new RGBColor(0x69, 0x69, 0x69))},
    {"slateblue", RGBColorPtr(new RGBColor(0x6a, 0x5a, 0xcd))},
    {"olivedrab", RGBColorPtr(new RGBColor(0x6b, 0x8e, 0x23))},
    {"slategrey", RGBColorPtr(new RGBColor(0x70, 0x80, 0x90))},
    {"lightslategrey", RGBColorPtr(new RGBColor(0x77, 0x88, 0x99))},
    {"mediumslateblue", RGBColorPtr(new RGBColor(0x7b, 0x68, 0xee))},
    {"lawngreen", RGBColorPtr(new RGBColor(0x7c, 0xfc, 0x00))},
    {"aquamarine", RGBColorPtr(new RGBColor(0x7f, 0xff, 0xd4))},
    {"chartreuse", RGBColorPtr(new RGBColor(0x7f, 0xff, 0x00))},
    {"grey", RGBColorPtr(new RGBColor(0x80, 0x80, 0x80))},
    {"maroon", RGBColorPtr(new RGBColor(0x80, 0x00, 0x00))},
    {"olive", RGBColorPtr(new RGBColor(0x80, 0x80, 0x00))},
    {"purple", RGBColorPtr(new RGBColor(0x80, 0x00, 0x80))},
    {"lightskyblue", RGBColorPtr(new RGBColor(0x87, 0xce, 0xfa))},
    {"skyblue", RGBColorPtr(new RGBColor(0x87, 0xce, 0xeb))},
    {"blueviolet", RGBColorPtr(new RGBColor(0x8a, 0x2b, 0xe2))},
    {"darkmagenta", RGBColorPtr(new RGBColor(0x8b, 0x00, 0x8b))},
    {"darkred", RGBColorPtr(new RGBColor(0x8b, 0x00, 0x00))},
    {"saddlebrown", RGBColorPtr(new RGBColor(0x8b, 0x45, 0x13))},
    {"darkseagreen", RGBColorPtr(new RGBColor(0x8f, 0xbc, 0x8f))},
    {"lightgreen", RGBColorPtr(new RGBColor(0x90, 0xee, 0x90))},
    {"mediumpurple", RGBColorPtr(new RGBColor(0x93, 0x70, 0xdb))},
    {"darkviolet", RGBColorPtr(new RGBColor(0x94, 0x00, 0xd3))},
    {"palegreen", RGBColorPtr(new RGBColor(0x98, 0xfb, 0x98))},
    {"darkorchid", RGBColorPtr(new RGBColor(0x99, 0x32, 0xcc))},
    {"yellowgreen", RGBColorPtr(new RGBColor(0x9a, 0xcd, 0x32))},
    {"sienna", RGBColorPtr(new RGBColor(0xa0, 0x52, 0x2d))},
    {"brown", RGBColorPtr(new RGBColor(0xa5, 0x2a, 0x2a))},
    {"darkgrey", RGBColorPtr(new RGBColor(0xa9, 0xa9, 0xa9))},
    {"greenyellow", RGBColorPtr(new RGBColor(0xad, 0xff, 0x2f))},
    {"lightblue", RGBColorPtr(new RGBColor(0xad, 0xd8, 0xe6))},
    {"paleturquoise", RGBColorPtr(new RGBColor(0xaf, 0xee, 0xee))},
    {"lightsteelblue", RGBColorPtr(new RGBColor(0xb0, 0xc4, 0xde))},
    {"powderblue", RGBColorPtr(new RGBColor(0xb0, 0xe0, 0xe6))},
    {"firebrick", RGBColorPtr(new RGBColor(0xb2, 0x22, 0x22))},
    {"darkgoldenrod", RGBColorPtr(new RGBColor(0xb8, 0x86, 0x0b))},
    {"mediumorchid", RGBColorPtr(new RGBColor(0xba, 0x55, 0xd3))},
    {"rosybrown", RGBColorPtr(new RGBColor(0xbc, 0x8f, 0x8f))},
    {"darkkhaki", RGBColorPtr(new RGBColor(0xbd, 0xb7, 0x6b))},
    {"silver", RGBColorPtr(new RGBColor(0xc0, 0xc0, 0xc0))},
    {"mediumvioletred", RGBColorPtr(new RGBColor(0xc7, 0x15, 0x85))},
    {"indianred", RGBColorPtr(new RGBColor(0xcd, 0x5c, 0x5c))},
    {"peru", RGBColorPtr(new RGBColor(0xcd, 0x85, 0x3f))},
    {"chocolate", RGBColorPtr(new RGBColor(0xd2, 0x69, 0x1e))},
    {"tan", RGBColorPtr(new RGBColor(0xd2, 0xb4, 0x8c))},
    {"lightgrey", RGBColorPtr(new RGBColor(0xd3, 0xd3, 0xd3))},
    {"thistle", RGBColorPtr(new RGBColor(0xd8, 0xbf, 0xd8))},
    {"goldenrod", RGBColorPtr(new RGBColor(0xda, 0xa5, 0x20))},
    {"orchid", RGBColorPtr(new RGBColor(0xda, 0x70, 0xd6))},
    {"palevioletred", RGBColorPtr(new RGBColor(0xdb, 0x70, 0x93))},
    {"crimson", RGBColorPtr(new RGBColor(0xdc, 0x14, 0x3c))},
    {"gainsboro", RGBColorPtr(new RGBColor(0xdc, 0xdc, 0xdc))},
    {"plum", RGBColorPtr(new RGBColor(0xdd, 0xa0, 0xdd))},
    {"burlywood", RGBColorPtr(new RGBColor(0xde, 0xb8, 0x87))},
    {"lightcyan", RGBColorPtr(new RGBColor(0xe0, 0xff, 0xff))},
    {"lavender", RGBColorPtr(new RGBColor(0xe6, 0xe6, 0xfa))},
    {"darksalmon", RGBColorPtr(new RGBColor(0xe9, 0x96, 0x7a))},
    {"palegoldenrod", RGBColorPtr(new RGBColor(0xee, 0xe8, 0xaa))},
    {"violet", RGBColorPtr(new RGBColor(0xee, 0x82, 0xee))},
    {"azure", RGBColorPtr(new RGBColor(0xf0, 0xff, 0xff))},
    {"honeydew", RGBColorPtr(new RGBColor(0xf0, 0xff, 0xf0))},
    {"khaki", RGBColorPtr(new RGBColor(0xf0, 0xe6, 0x8c))},
    {"lightcoral", RGBColorPtr(new RGBColor(0xf0, 0x80, 0x80))},
    {"sandybrown", RGBColorPtr(new RGBColor(0xf4, 0xa4, 0x60))},
    {"beige", RGBColorPtr(new RGBColor(0xf5, 0xf5, 0xdc))},
    {"mintcream", RGBColorPtr(new RGBColor(0xf5, 0xff, 0xfa))},
    {"wheat", RGBColorPtr(new RGBColor(0xf5, 0xde, 0xb3))},
    {"whitesmoke", RGBColorPtr(new RGBColor(0xf5, 0xf5, 0xf5))},
    {"ghostwhite", RGBColorPtr(new RGBColor(0xf8, 0xf8, 0xff))},
    {"lightgoldenrodyellow", RGBColorPtr(new RGBColor(0xfa, 0xfa, 0xd2))},
    {"linen", RGBColorPtr(new RGBColor(0xfa, 0xf0, 0xe6))},
    {"salmon", RGBColorPtr(new RGBColor(0xfa, 0x80, 0x72))},
    {"oldlace", RGBColorPtr(new RGBColor(0xfd, 0xf5, 0xe6))},
    {"bisque", RGBColorPtr(new RGBColor(0xff, 0xe4, 0xc4))},
    {"blanchedalmond", RGBColorPtr(new RGBColor(0xff, 0xeb, 0xcd))},
    {"coral", RGBColorPtr(new RGBColor(0xff, 0x7f, 0x50))},
    {"cornsilk", RGBColorPtr(new RGBColor(0xff, 0xf8, 0xdc))},
    {"darkorange", RGBColorPtr(new RGBColor(0xff, 0x8c, 0x00))},
    {"deeppink", RGBColorPtr(new RGBColor(0xff, 0x14, 0x93))},
    {"floralwhite", RGBColorPtr(new RGBColor(0xff, 0xfa, 0xf0))},
    {"fuchsia", RGBColorPtr(new RGBColor(0xff, 0x00, 0xff))},
    {"gold", RGBColorPtr(new RGBColor(0xff, 0xd7, 0x00))},
    {"hotpink", RGBColorPtr(new RGBColor(0xff, 0x69, 0xb4))},
    {"ivory", RGBColorPtr(new RGBColor(0xff, 0xff, 0xf0))},
    {"lavenderblush", RGBColorPtr(new RGBColor(0xff, 0xf0, 0xf5))},
    {"lemonchiffon", RGBColorPtr(new RGBColor(0xff, 0xfa, 0xcd))},
    {"lightpink", RGBColorPtr(new RGBColor(0xff, 0xb6, 0xc1))},
    {"lightsalmon", RGBColorPtr(new RGBColor(0xff, 0xa0, 0x7a))},
    {"lightyellow", RGBColorPtr(new RGBColor(0xff, 0xff, 0xe0))},
    {"magenta", RGBColorPtr(new RGBColor(0xff, 0x00, 0xff))},
    {"mistyrose", RGBColorPtr(new RGBColor(0xff, 0xe4, 0xe1))},
    {"moccasin", RGBColorPtr(new RGBColor(0xff, 0xe4, 0xb5))},
    {"navajowhite", RGBColorPtr(new RGBColor(0xff, 0xde, 0xad))},
    {"orange", RGBColorPtr(new RGBColor(0xff, 0xa5, 0x00))},
    {"orangered", RGBColorPtr(new RGBColor(0xff, 0x45, 0x00))},
    {"papayawhip", RGBColorPtr(new RGBColor(0xff, 0xef, 0xd5))},
    {"peachpuff", RGBColorPtr(new RGBColor(0xff, 0xda, 0xb9))},
    {"pink", RGBColorPtr(new RGBColor(0xff, 0xc0, 0xcb))},
    {"red", RGBColorPtr(new RGBColor(0xff, 0x00, 0x00))},
    {"seashell", RGBColorPtr(new RGBColor(0xff, 0xf5, 0xee))},
    {"snow", RGBColorPtr(new RGBColor(0xff, 0xfa, 0xfa))},
    {"tomato", RGBColorPtr(new RGBColor(0xff, 0x63, 0x47))},
    {"white", RGBColorPtr(new RGBColor(0xff, 0xff, 0xff))},
    {"yellow", RGBColorPtr(new RGBColor(0xff, 0xff, 0x00))},
    {"warmwhite", RGBColorPtr(new RGBColor(0xfd, 0xf5, 0xe6))}};

RGBColor::RGBColor() throw()
    : mRed(0), mGreen(0), mBlue(0)
{
}

RGBColor::RGBColor(uint8_t red, uint8_t green, uint8_t blue) throw()
    : mRed(red), mGreen(green), mBlue(blue)
{
}

RGBColorPtr RGBColor::getFriendlyColor(std::string name)
{
  return sFriendlyColors.at(name);
}

RGBTuple RGBColor::getValues() throw()
{
  return std::make_tuple(mRed, mGreen, mBlue);
}

std::string RGBColor::toString() throw()
{
  char hex[7];
  snprintf(hex, 7, "%02x%02x%02x", mRed, mGreen, mBlue);
  return std::string(std::begin(hex), std::end(hex) - 1);
}
