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

#ifndef COLOUR_FUNCTIONS_HPP
#define COLOUR_FUNCTIONS_HPP

#include "vector4.hpp"

namespace Broome
{

// conversion from and to different colour formats
void Html2Rgb(const ColourHtml& in, Colour3& out);
void Rgb2Html(const Colour3& in, ColourHtml& out);

void C8bit2Rgba(const Colour8bit& in, Colour4& out);
void Rgba2C8bit(const Colour4& in, Colour8bit& out);

void Rgb2Hsv(const Colour3& in, Colour3& out);
void Rgb2Hsl(const Colour3& in, Colour3& out);
void Rgb2Cmyk(const Colour3& in, Colour4& out);

void Hsl2Rgb(const Colour3& in, Colour3& out);
void Hsl2Hsv(const Colour3& in, Colour3& out);
void Hsl2Cmyk(const Colour3& in, Colour4& out);

void Hsv2Rgb(const Colour3& in, Colour3& out);
void Hsv2Hsl(const Colour3& in, Colour3& out);
void Hsv2Cmyk(const Colour3& in, Colour4& out);

void Cmyk2Rgb(const Colour4& in, Colour3& out);
void Cmyk2Hsl(const Colour4& in, Colour3& out);
void Cmyk2Hsv(const Colour4& in, Colour3& out);

} // end namespace Broome

#endif // COLOUR_FUNCTIONS_HPP
