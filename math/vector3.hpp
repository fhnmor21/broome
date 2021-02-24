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

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "colour_types.hpp"
#include "vector2.hpp"

namespace Broome
{

struct Vector3
{
  enum
  {
    eAxis = 3,
  };
  union {
    struct
    {
      Scalar x;
      Scalar y;
      Scalar z;
    };
    struct
    {
      Scalar width;
      Scalar height;
      Scalar depth;
    };
    struct
    {
      Scalar pitch;
      Scalar roll;
      Scalar yaw;
    };

    struct
    {
      Scalar r;
      Scalar g;
      Scalar b;
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

    ColourRGB rgb;
    ColourHSV hsv;
    ColourHSL hsl;

    Scalar data[eAxis];
    Vector2 xy;
  };

  static const Vector3 Zero;
  static const Vector3 Half;
  static const Vector3 One;

  inline Scalar& operator[](usize index) { return data[index]; }
  inline const Scalar& operator[](usize index) const { return data[index]; }
};

bool operator==(const Vector3& a, const Vector3& b);
bool operator!=(const Vector3& a, const Vector3& b);
Vector3 operator-(const Vector3& a);
Vector3 operator+(const Vector3& a, const Vector3& b);
Vector3 operator-(const Vector3& a, const Vector3& b);
Vector3 operator*(const Vector3& a, const f32 scalar);
Vector3 operator/(const Vector3& a, const f32 scalar);
Vector3 operator*(const Vector3& a, const Vector3& b);
Vector3 operator/(const Vector3& a, const Vector3& b);
Vector3& operator+=(Vector3& a, const Vector3& b);
Vector3& operator-=(Vector3& a, const Vector3& b);
Vector3& operator*=(Vector3& a, const f32 scalar);
Vector3& operator/=(Vector3& a, const f32 scalar);

inline Vector3 operator*(const f32 scalar, Vector3& vector) { return vector * scalar; }
inline Vector3 operator/(const f32 scalar, Vector3& vector) { return vector / scalar; }
inline Vector3& operator*=(const f32 scalar, Vector3& vector) { return vector * scalar; }
inline Vector3& operator/=(const f32 scalar, Vector3& vector) { return vector / scalar; }

using Colour3 = Vector3;
using Dimension3 = Vector3;
using Rotation3 = Vector3;

} // end namespace Broome

#endif // VECTOR3_HPP
