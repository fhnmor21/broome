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

#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include "vector3.hpp"

namespace Broome
{

struct Vector4
{
  enum
  {
    eAxis = 4,
  };
  union {

    struct
    {
      Scalar x;
      Scalar y;
      Scalar z;
      Scalar w;
    };
    struct
    {
      Scalar pitch;
      Scalar roll;
      Scalar yaw;
      Scalar mag;
    };

    struct
    {
      Scalar r;
      Scalar g;
      Scalar b;
      Scalar a;
    };
    struct
    {
      Scalar C;
      Scalar M;
      Scalar Y;
      Scalar K;
    };
    struct
    {
      Scalar h;
      Scalar s;
      Scalar v;
    };
    struct
    {
      Vector2 hs;
      Scalar l;
    };

    ColourRGBA rgba;
    ColourHSVA hsva;
    ColourHSLA hsla;
    ColourCMYK CMYK;

    Scalar data[eAxis];

    struct
    {
      Vector2 xy;
      Vector2 zw;
    };

    Vector3 xyz;
    ColourRGB rgb;
    ColourHSV hsv;
    ColourHSL hsl;
  };

  static const Vector4 Zero;
  static const Vector4 Half;
  static const Vector4 One;

  inline Scalar& operator[](usize index) { return data[index]; }
  inline const Scalar& operator[](usize index) const { return data[index]; }
};

bool operator==(const Vector4& a, const Vector4& b);
bool operator!=(const Vector4& a, const Vector4& b);
Vector4 operator-(const Vector4& a);
Vector4 operator+(const Vector4& a, const Vector4& b);
Vector4 operator-(const Vector4& a, const Vector4& b);
Vector4 operator*(const Vector4& a, const f32 scalar);
Vector4 operator*(const Vector4& a, const Vector4& b);
Vector4 operator/(const Vector4& a, const Vector4& b);
Vector4 operator/(const Vector4& a, const f32 scalar);
Vector4& operator+=(Vector4& a, const Vector4& b);
Vector4& operator-=(Vector4& a, const Vector4& b);
Vector4& operator*=(Vector4& a, const f32 scalar);
Vector4& operator/=(Vector4& a, const f32 scalar);

inline Vector4 operator*(const f32 scalar, const Vector4& vector) { return vector * scalar; }
inline Vector4 operator/(const f32 scalar, const Vector4& vector) { return vector / scalar; }
inline Vector4& operator*=(const f32 scalar, const Vector4& vector) { return vector * scalar; }
inline Vector4& operator/=(const f32 scalar, const Vector4& vector) { return vector / scalar; }

using Colour4 = Vector4;

} // end namespace Broome

#endif // VECTOR4_HPP
