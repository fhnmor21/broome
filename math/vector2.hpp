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

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "scalar.hpp"

namespace Broome
{

struct Vector2
{
  union {
    struct
    {
      Scalar x;
      Scalar y;
    };
    struct
    {
      Scalar u;
      Scalar v;
    };
    struct
    {
      Scalar s;
      Scalar t;
    };
    struct
    {
      Scalar width;
      Scalar height;
    };
    struct
    {
      Scalar roll;
      Scalar pitch;
    };
    Scalar data[2];
  };

  static const Vector2 Zero;
  static const Vector2 Half;
  static const Vector2 One;

  inline Scalar& operator[](usize index) { return data[index]; }
  inline const Scalar& operator[](usize index) const { return data[index]; }
};

} // end namespace Broome

#endif // VECTOR2_HPP
