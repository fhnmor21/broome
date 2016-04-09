/**
The MIT License (MIT)

Copyright (c) 2015 Ginger Bill
Copyright (c) 2016 Flavio Moreira

Original License:
"""
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files ("Dunjun"), to deal in Dunjun without restriction, including without
limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of Dunjun, and to permit persons to whom Dunjun is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of Dunjun.

Dunjun is provided "as is", without warranty of any kind, express or implied, including but not
limited to the warranties of merchantability, fitness for a particular purpose and noninfringement.
In no event shall the authors or copyright holders be liable for any claim, damages or other
liability, whether in an action of contract, tort or otherwise, arising from, out of or in
connection with Dunjun or the use or other dealings in Dunjun.
"""

* Original file from Dunjun: https://github.com/gingerBill/Dunjun

NOTE: This file was modified to fit the Broome project
*/

#include "vector4.hpp"
#include "functions.hpp"

namespace Broome
{
const Vector4 Vector4::Zero = {0.0, 0.0, 0.0, 0.0};
const Vector4 Vector4::Half = {0.5, 0.5, 0.5, 0.5};
const Vector4 Vector4::One = {1.0, 1.0, 1.0, 1.0};

bool operator==(const Vector4& a, const Vector4& b)
{
  for(usize i = 0; i < 4; i++)
  {
    if(a[i] != b[i])
      return false;
  }

  return true;
}

bool operator!=(const Vector4& a, const Vector4& b) { return !operator==(a, b); }

Vector4 operator-(const Vector4& a) { return {-a.x, -a.y, -a.z, -a.w}; }

Vector4 operator+(const Vector4& a, const Vector4& b)
{
  return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

Vector4 operator-(const Vector4& a, const Vector4& b)
{
  return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

Vector4 operator*(const Vector4& a, Scalar scalar)
{
  return {scalar * a.x, scalar * a.y, scalar * a.z, scalar * a.w};
}

// Hadamard Product
Vector4 operator*(const Vector4& a, const Vector4& b)
{
  Vector4 result;
  for(usize i = 0; i < 4; i++)
    result[i] = a[i] * b[i];
  return result;
}

// Hadamard Product
Vector4 operator/(const Vector4& a, const Vector4& b)
{
  Vector4 result;
  for(usize i = 0; i < 4; i++)
    result[i] = a[i] / b[i];
  return result;
}

Vector4 operator/(const Vector4& a, Scalar scalar)
{
  return {a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar};
}

Vector4& operator+=(Vector4& a, const Vector4& b)
{
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;

  return a;
}

Vector4& operator-=(Vector4& a, const Vector4& b)
{
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;

  return a;
}

Vector4& operator*=(Vector4& a, Scalar scalar)
{
  a.x *= scalar;
  a.y *= scalar;
  a.z *= scalar;
  a.w *= scalar;

  return a;
}

Vector4& operator/=(Vector4& a, Scalar scalar)
{
  a.x /= scalar;
  a.y /= scalar;
  a.z /= scalar;
  a.w /= scalar;

  return a;
}

Scalar dot(const Vector4& a, const Vector4& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Scalar lengthSq(const Vector4& a) { return dot(a, a); }

Scalar length(const Vector4& a) { return std::sqrt(lengthSq(a)); }

Vector4 normalize(const Vector4& a) { return a * (1.0f / length(a)); }

} // namespace Broome
