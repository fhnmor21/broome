/**
The MIT License (MIT)

Copyright (c) 2016 Flavio Moreira

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "colour_functions.hpp"
#include <algorithm>

namespace Broome
{

using namespace std;

inline u8 hexChar2Val(const char* ch)
{
  u8 val = 0;
  u8 in = *ch;
  if((in >= 48) && (in <= 57)) // 0-9
  {
    val = in - 48;
  }
  else if((in >= 65) && (in <= 70)) // A-F
  {
    val = in - 55;
  }
  else if((in >= 97) && (in <= 102)) // a-f
  {
    val = in - 87;
  }
  return val;
}

void Html2Rgb(const ColourHtml& in, Colour3& out)
{
  u32 rgb = 0;
  for(u8 i = 0; i < 6; i++)
  {
    rgb += hexChar2Val(&in.hexVal[i]);
    rgb <<= 4;
  }
  out.b = static_cast< Scalar >(0xff & rgb);
  out.g = static_cast< Scalar >(0xff & (rgb >> 8));
  out.r = static_cast< Scalar >(0xff & (rgb >> 16));
}

void Rgb2Html(const Colour3& in, ColourHtml& out)
{
  const char hex[16] = {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

  u8 r = (static_cast< u8 >(in.r * 255) % 256);
  u8 g = (static_cast< u8 >(in.g * 255) % 256);
  u8 b = (static_cast< u8 >(in.b * 255) % 256);

  u8 r_Lo = r & 0x0f;
  u8 r_Hi = (r >> 4) & 0x0f;
  u8 g_Lo = g & 0x0f;
  u8 g_Hi = (g >> 4) & 0x0f;
  u8 b_Lo = b & 0x0f;
  u8 b_Hi = (b >> 4) & 0x0f;

  out.hexVal[7] = '\0';
  out.hexVal[6] = hex[r_Hi];
  out.hexVal[5] = hex[r_Lo];
  out.hexVal[4] = hex[g_Hi];
  out.hexVal[3] = hex[g_Lo];
  out.hexVal[2] = hex[b_Hi];
  out.hexVal[1] = hex[b_Lo];
  out.hexVal[0] = '#';
}

void C8bit2Rgba(const Colour8bit& in, Colour4& out)
{
  out.r = static_cast< Scalar >(in.r / 255);
  out.g = static_cast< Scalar >(in.g / 255);
  out.b = static_cast< Scalar >(in.b / 255);
  out.a = static_cast< Scalar >(in.a / 255);
}

void Rgba2C8bit(const Colour4& in, Colour8bit& out)
{
  out.r = (static_cast< u8 >(in.r * 255) % 256);
  out.g = (static_cast< u8 >(in.g * 255) % 256);
  out.b = (static_cast< u8 >(in.b * 255) % 256);
  out.a = (static_cast< u8 >(in.a * 255) % 256);
}

Scalar calcHueFromRgb(const Colour3& in, const Scalar& cMax, const Scalar& cMin)
{
  Scalar delta = cMax - cMin;
  Scalar h = 0.0f;

  // calculating Hue
  if(in.r == cMax)
  {
    // between yellow & magenta
    h = (in.g - in.b) / delta;
  }
  else if(in.g == cMax)
  {
    // between cyan & yellow
    h = 2.0f + (in.b - in.r) / delta;
  }
  else
  {
    // between magenta & cyan
    h = 4.0f + (in.r - in.g) / delta;
  }

  // normalize h value
  h = fmod(h + 6.0f, 6.0f); // 0.0 <= h < 6.0
  h /= 6.0f;                // circle (0.0-1.0)

  return h;
}

void Rgb2Hsv(const Colour3& in, Colour3& out)
{
  Scalar cMax = std::max(in.r, std::max(in.g, in.b));
  Scalar cMin = std::min(in.r, std::min(in.g, in.b));
  Scalar delta = cMax - cMin;

  // calculating saturation
  if(cMax > 0)
  {
    out.s = delta / cMax; // s
  }
  else
  {
    // r = g = b = 0		// s = 0, v is undefined
    out.s = 0;
    out.h = 0;
    out.v = 0;
    return;
  }

  // calculating hue
  out.h = calcHueFromRgb(in, cMax, cMin);

  // calculating value
  out.v = cMax;
}

void Rgb2Hsl(const Colour3& in, Colour3& out)
{
  Scalar cMax = std::max(in.r, std::max(in.g, in.b));
  Scalar cMin = std::min(in.r, std::min(in.g, in.b));
  Scalar delta = cMax - cMin;

  // calculating lightness
  out.l = 0.5 * (cMax + cMin);

  // calculating saturation
  if(delta > 0)
  {
    out.s = delta / (1 - abs((2 * out.l) - 1)); // s
  }
  else
  {
    // r = g = b = 0		// s = 0, v is undefined
    out.s = 0;
    out.h = 0;
    out.l = 0;
    return;
  }

  // calculating Hue
  out.h = calcHueFromRgb(in, cMax, cMin);
}

void Rgb2Cmyk(const Colour3& in, Colour4& out)
{
  out.K = 1 - max(in.r, max(in.g, in.b));
  out.C = (1 - in.r - out.K) / (1 - out.K);
  out.M = (1 - in.g - out.K) / (1 - out.K);
  out.Y = (1 - in.b - out.K) / (1 - out.K);
}

inline void
calcRgbFromHue(const Scalar& h, const Scalar& c, const Scalar& x, const Scalar& m, Colour3& out)
{
  out.r = 0.0f;
  out.g = 0.0f;
  out.b = 0.0f;

  if((h >= 0) && (h < 1))
  {
    out.r = m + c;
    out.g = m + x;
    out.b = m + 0.0f;
  }
  else if((h >= 1) && (h < 2))
  {
    out.r = m + x;
    out.g = m + c;
    out.b = m + 0.0f;
  }
  else if((h >= 2) && (h < 3))
  {
    out.r = m + 0.0f;
    out.g = m + c;
    out.b = m + x;
  }
  else if((h >= 3) && (h < 4))
  {
    out.r = m + 0.0f;
    out.g = m + x;
    out.b = m + c;
  }
  else if((h >= 4) && (h < 5))
  {
    out.r = m + x;
    out.g = m + 0.0f;
    out.b = m + c;
  }
  else if((h >= 5) && (h < 6))
  {
    out.r = m + c;
    out.g = m + 0.0f;
    out.b = m + x;
  }
}

void Hsl2Rgb(const Colour3& in, Colour3& out)
{
  Scalar h = fmod(6.0f + in.h * 6.0f, 6.0f);
  Scalar c = in.s * (1 - abs(2 * in.l - 1));
  Scalar x = c * (1 - abs(fmod(h, 2.0f) - 1));
  Scalar m = in.l - (c / 2.0f);

  calcRgbFromHue(h, c, x, m, out);
}

void Hsv2Rgb(const Colour3& in, Colour3& out)
{
  Scalar h = fmod(6.0f + in.h * 6.0f, 6.0f);
  Scalar c = in.v * in.s;
  Scalar x = c * (1 - abs(fmod(h, 2.0f) - 1));
  Scalar m = in.v - c;

  calcRgbFromHue(h, c, x, m, out);
}

void Cmyk2Rgb(const Colour4& in, Colour3& out)
{
  out.r = (1 - in.C) * (1 - in.K);
  out.g = (1 - in.M) * (1 - in.K);
  out.b = (1 - in.Y) * (1 - in.K);
}

void Hsl2Hsv(const Colour3& in, Colour3& out)
{
  // Saturation is very different between the two color spaces
  // If (2-sat)*val < 1 set it to sat*val/((2-sat)*val)
  // Otherwise sat*val/(2-(2-sat)*val)

  // repeat the hue without change
  out.h = in.h;

  Scalar l2 = 2 * in.l;
  Scalar s2 = 0.0f;

  if(l2 <= 1)
  {
    s2 = in.s * l2;
  }
  else
  {
    s2 = in.s * (2 - l2);
  }

  out.v = (l2 + s2) / 2;
  out.s = (2 * s2) / (l2 + s2);
}

void Hsv2Hsl(const Colour3& in, Colour3& out)
{
  Scalar cMax = in.v;
  Scalar cMin = in.v - in.s * in.v;
  Scalar delta = cMax - cMin;

  // repeat the hue without change
  out.h = in.h;

  // calculating lightness
  out.l = 0.5 * (cMax + cMin);

  // calculating saturation
  if(delta > 0)
  {
    out.s = delta / (1 - abs((2 * out.l) - 1)); // s
  }
  else
  {
    // r = g = b = 0		// s = 0, v is undefined
    out.s = 0;
    out.h = 0;
    out.l = 0;
    return;
  }
}

void Hsl2Cmyk(const Colour3& in, Colour4& out)
{
  Colour3 tmp;
  Hsl2Rgb(in, tmp);
  Rgb2Cmyk(tmp, out);
}

void Hsv2Cmyk(const Colour3& in, Colour4& out)
{
  Colour3 tmp;
  Hsv2Rgb(in, tmp);
  Rgb2Cmyk(tmp, out);
}

void Cmyk2Hsl(const Colour4& in, Colour3& out)
{
  Colour3 tmp;
  Cmyk2Rgb(in, tmp);
  Rgb2Hsl(tmp, out);
}

void Cmyk2Hsv(const Colour4& in, Colour3& out)
{
  Colour3 tmp;
  Cmyk2Rgb(in, tmp);
  Rgb2Hsv(tmp, out);
}

} // end namespace Broome
