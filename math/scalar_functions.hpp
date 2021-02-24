/**
The MIT License (MIT)

Copyright (c) 2015 Ginger Bill
Copyright (c) 2016 Flavio Moreira

Original License:
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

* Original file from Dunjun: https://github.com/gingerBill/Dunjun

NOTE: This file was modified to fit the Broome project
*/

#ifndef SCALAR_FUNCTIONS_HPP
#define SCALAR_FUNCTIONS_HPP

#include <cfenv>
#include <cmath>

#include "scalar.hpp"

namespace Broome
{

// Trigonometric
Scalar sin(Radian theta);
Scalar cos(Radian theta);
Scalar tan(Radian theta);

Radian asin(Scalar a);
Radian acos(Scalar a);
Radian atan(Scalar a);
Radian atan2(Scalar y, Scalar x);

// Hyperbolic
Scalar sinh(Scalar x);
Scalar cosh(Scalar x);
Scalar tanh(Scalar x);

Scalar asinh(Scalar x);
Scalar acosh(Scalar x);
Scalar atanh(Scalar x);

// Power
Scalar pow(Scalar x, Scalar y);
Scalar sqrt(Scalar x);
Scalar cbrt(Scalar x);
Scalar hypotenuse(Scalar x, Scalar y);

f32 fastInvSqrt(f32 x);

// Exponential and Logarithm
Scalar exp(Scalar x);  // e^x
Scalar exp2(Scalar x); // 2^x
Scalar ln(Scalar x);
Scalar ln1p(Scalar x); // ln(1 + x)
Scalar log2(Scalar x);
Scalar log10(Scalar x);
Scalar logBase(Scalar x, Scalar base);

// Sign
f32 abs(f32 x);
i8 abs(i8 x);
i16 abs(i16 x);
i32 abs(i32 x);
i64 abs(i64 x);

i32 sign(i32 x);
i64 sign(i64 x);
f32 sign(f32 x);

// Rounding
Scalar ceil(Scalar x);
Scalar floor(Scalar x);
Scalar mod(Scalar x, Scalar y);

// TODO: 64 bit version
f32 truncate(f32 x);
// TODO: 64 bit version
f32 round(f32 x);

// ----------------
// Implementation
// ----------------

// Trigonometric
Scalar sin(Radian theta) { return std::sin(theta); }
Scalar cos(Radian theta) { return std::cos(theta); }
Scalar tan(Radian theta) { return std::tan(theta); }

Radian asin(Scalar a) { return Radian(std::asin(a)); }
Radian acos(Scalar a) { return Radian(std::acos(a)); }
Radian atan(Scalar a) { return Radian(std::atan(a)); }
Radian atan2(Scalar y, Scalar x) { return Radian(std::atan2(y, x)); }

// Hyperbolic
Scalar sinh(Scalar x) { return std::sinh(x); }
Scalar cosh(Scalar x) { return std::cosh(x); }
Scalar tanh(Scalar x) { return std::tanh(x); }

Scalar asinh(Scalar x) { return std::asinh(x); }
Scalar acosh(Scalar x) { return std::acosh(x); }
Scalar atanh(Scalar x) { return std::atanh(x); }

// Power
Scalar pow(Scalar x, Scalar y) { return std::pow(x, y); }

Scalar sqrt(Scalar x) { return std::sqrt(x); }

Scalar cbrt(Scalar x) { return std::cbrt(x); }

Scalar hypotenuse(Scalar x, Scalar y) { return std::hypot(x, y); }

// https://en.wikipedia.org/wiki/Fast_inverse_square_root
f32 fastInvSqrt(f32 number)
{
  const f32 threeHalfs = 1.5f;

  f32 x2 = number * 0.5f;
  f32 y = number;
  u32 i;
  // i = *(u32*)&y; // Evil floating point bit level hacking
  i = *(reinterpret_cast< u32* >(&y)); // using C++ idiom
  // i = 0x5f3759df - (i >> 1);           // What the f*k?
  i = 0x5f375a86 - (i >> 1); // What the fu*k? Improved!
  // y = *(f32*)&i;
  y = *(reinterpret_cast< f32* >(&i)); // using C++ idiom
  y = y * (threeHalfs - (x2 * y * y)); // 1st iteration
  //	y = y * (threeHalfs - (x2 * y * y)); // 2nd iteration, this can be removed

  return y;
}

// Exponential and Logarithm
Scalar exp(Scalar x) // e^x
{
  return std::exp(x);
}
Scalar exp2(Scalar x) // 2^x
{
  return std::exp2(x);
}
Scalar ln(Scalar x) { return std::log(x); }
Scalar ln1p(Scalar x) // ln(1 + x)
{
  return std::log1p(x);
}
Scalar log2(Scalar x) { return std::log2(x); }
Scalar log10(Scalar x) { return std::log10(x); }
Scalar logBase(Scalar x, Scalar base) { return ln(x) * (1.0f / ln(base)); }

// Signal
f32 abs(f32 x)
{
  u32 i = reinterpret_cast< const u32& >(x);
  i &= 0x7FFFFFFFul;
  return reinterpret_cast< const f32& >(i);
}
i8 abs(i8 x)
{
  u8 i = reinterpret_cast< const u8& >(x);
  i &= 0x7Fu;
  return reinterpret_cast< const i8& >(i);
}
i16 abs(i16 x)
{
  u16 i = reinterpret_cast< const u16& >(x);
  i &= 0x7FFFu;
  return reinterpret_cast< const i16& >(i);
}
i32 abs(i32 x)
{
  u32 i = reinterpret_cast< const u32& >(x);
  i &= 0x7FFFFFFFul;
  return reinterpret_cast< const i32& >(i);
}
i64 abs(i64 x)
{
  u64 i = reinterpret_cast< const u64& >(x);
  i &= 0x7FFFFFFFFFFFFFFFull;
  return reinterpret_cast< const i64& >(i);
}

i32 sign(i32 x)
{
  u32 i = reinterpret_cast< const u32& >(x);
  i &= 0x80000000ul;
  if(i)
    return -1;
  return 1;
}

i64 sign(i64 x)
{
  u64 i = reinterpret_cast< const u64& >(x);
  i &= 0x8000000000000000ull;
  if(i)
    return -1;
  return 1;
}

f32 sign(f32 x)
{
  u32 i = reinterpret_cast< const u32& >(x);
  i &= 0x80000000ul;
  if(i)
    return -1.0f;
  return 1.0f;
}

// Rounding
Scalar ceil(Scalar x) { return std::ceil(x); }
Scalar floor(Scalar x) { return std::floor(x); }

Scalar mod(Scalar x, Scalar y)
{
  Scalar result = std::remainder(abs(x), (y = abs(y)));
  if(std::signbit(result))
    result += y;
  return std::copysign(result, x);
}

// TODO: 64 bit version
f32 truncate(f32 x)
{
  u32 i = *(reinterpret_cast< u32* >(&x));
  u32 exponent = (i >> 23) & 0xFF; // extract exponent field
  u32 fractionalBits = 0x7F + 23 - exponent;
  if(fractionalBits > 23) // abs(x) < 1.0f
    return 0.0f;
  if(fractionalBits > 0)
    i &= ~((1u << fractionalBits) - 1);
  return *(reinterpret_cast< f32* >(&i));
}

// TODO: 64 bit version
f32 round(f32 x)
{
  std::fenv_t saveEnv;
  std::feholdexcept(&saveEnv);
  f32 result = std::rint(x);
  if(std::fetestexcept(FE_INEXACT))
  {
    std::fesetround(FE_TOWARDZERO);
    result = std::rint(std::copysign(0.5f + abs(x), x));
  }
  std::feupdateenv(&saveEnv);
  return result;
}

} // end namespace Broome

#endif // SCALAR_FUNCTIONS_HPP
