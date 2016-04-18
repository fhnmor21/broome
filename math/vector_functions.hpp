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

#ifndef VECTOR_FUNCTIONS_HPP
#define VECTOR_FUNCTIONS_HPP

#include <cmath>

#include "vector4.hpp"

namespace Broome
{

Scalar cross(const Vector2& a, const Vector2& b) { return a.x * b.y - b.x * a.y; }

Vector3 cross(const Vector3& a, const Vector3& b)
{
  return {
      a.y * b.z - b.y * a.z, // x
      a.z * b.x - b.z * a.x, // y
      a.x * b.y - b.x * a.y  // z
  };
}

template < typename VectorType >
Scalar dot(const VectorType a, const VectorType b)
{
  Scalar result(0.0);
  const unsigned short numAxis = VectorType::eAxis;
  for(unsigned short i = 0; i < numAxis; i++)
  {
    result += a.data[i] * b.data[i];
  }
  return result;
}

template < typename VectorType >
Scalar lengthSq(const VectorType& a)
{
  return dot(a, a);
}

template < typename VectorType >
Scalar length(const VectorType& a)
{
  return std::sqrt(lengthSq(a));
}

template < typename VectorType >
VectorType normalize(const VectorType& a)
{
  return a * (1.0f / length(a));
}

template < typename VectorType >
VectorType lerp(const VectorType a, const VectorType b, Scalar t)
{
  const unsigned short numAxis(VectorType::eAxis);

  VectorType result;
  for(unsigned short i = 0; i < numAxis; i++)
  {
    result.data[i] = a.data[i] + t * (b.data[i] - a.data[i]);
  }
  return result;
}

// /**
//  * Rotates the point anticlockwise around a center
//  * by an amount of degrees.
//  *
//  * Code ported from Irrlicht: http://irrlicht.sourceforge.net/
//  */
// kmVec2* kmVec2RotateBy(kmVec2* pOut, const kmVec2* pIn,
//       const kmScalar degrees, const kmVec2* center)
// {
//    kmScalar x, y;
//    const kmScalar radians = kmDegreesToRadians(degrees);
//    const kmScalar cs = cosf(radians), sn = sinf(radians);
//
//    pOut->x = pIn->x - center->x;
//    pOut->y = pIn->y - center->y;
//
//    x = pOut->x * cs - pOut->y * sn;
//    y = pOut->x * sn + pOut->y * cs;
//
//    pOut->x = x + center->x;
//    pOut->y = y + center->y;
//
//    return pOut;
// }
//
// /**
//  * 	Returns the angle in degrees between the two vectors
//  */
// kmScalar kmVec2DegreesBetween(const kmVec2* v1, const kmVec2* v2) {
// 	if(kmVec2AreEqual(v1, v2)) {
// 		return 0.0;
// 	}
//
// 	kmVec2 t1, t2;
// 	kmVec2Normalize(&t1, v1);
// 	kmVec2Normalize(&t2, v2);
//
// 	kmScalar cross = kmVec2Cross(&t1, &t2);
// 	kmScalar dot = kmVec2Dot(&t1, &t2);
//
// 	/*
// 	 * acos is only defined for -1 to 1. Outside the range we
// 	 * get NaN even if that's just because of a floating point error
// 	 * so we clamp to the -1 - 1 range
// 	 */
//
// 	if(dot > 1.0) dot = 1.0;
// 	if(dot < -1.0) dot = -1.0;
//
// 	return kmRadiansToDegrees(atan2(cross, dot));
// }
//
// /**
//  * Returns the distance between the two points
//  */
// kmScalar kmVec2DistanceBetween(const kmVec2* v1, const kmVec2* v2) {
// 	kmVec2 diff;
// 	kmVec2Subtract(&diff, v2, v1);
// 	return fabs(kmVec2Length(&diff));
// }
// /**
//  * Returns the point mid-way between two others
//  */
// kmVec2* kmVec2MidPointBetween(kmVec2* pOut, const kmVec2* v1, const kmVec2* v2) {
// 	kmVec2 sum;
//     kmVec2Add(&sum, v1, v2);
//     pOut->x = sum.x / 2.0f;
//     pOut->y = sum.y / 2.0f;
//
// 	return pOut;
// }
//
// /**
//  * Reflects a vector about a given surface normal. The surface normal is
//  * assumed to be of unit length.
//  */
// kmVec2* kmVec2Reflect(kmVec2* pOut, const kmVec2* pIn, const kmVec2* normal) {
// 	kmVec2 tmp;
// 	kmVec2Scale(&tmp, normal, 2.0f * kmVec2Dot(pIn, normal));
// 	kmVec2Subtract(pOut, pIn, &tmp);
//
// 	return pOut;
// }
//
// /**
//  * Get the rotations that would make a (0,0,1) direction vector point in the same direction as
//  this direction vector.
//  * Useful for orienting vector towards a point.
//  *
//  * Returns a rotation vector containing the X (pitch) and Y (raw) rotations (in degrees) that
//  when applied to a
//  * +Z (e.g. 0, 0, 1) direction vector would make it point in the same direction as this vector.
//  The Z (roll) rotation
//  * is always 0, since two Euler rotations are sufficient to point in any given direction.
//  *
//  * Code ported from Irrlicht: http://irrlicht.sourceforge.net/
//  */
// kmVec3* kmVec3GetHorizontalAngle(kmVec3* pOut, const kmVec3 *pIn) {
//    const kmScalar z1 = sqrt(pIn->x * pIn->x + pIn->z * pIn->z);
//
//    pOut->y = kmRadiansToDegrees(atan2(pIn->x, pIn->z));
//    if (pOut->y < 0)
//       pOut->y += 360;
//    if (pOut->y >= 360)
//       pOut->y -= 360;
//
//    pOut->x = kmRadiansToDegrees(atan2(z1, pIn->y)) - 90.0;
//    if (pOut->x < 0)
//       pOut->x += 360;
//    if (pOut->x >= 360)
//       pOut->x -= 360;
//
//    return pOut;
// }
//
// /**
//  * Builds a direction vector from input vector.
//  * Input vector is assumed to be rotation vector composed from 3 Euler angle rotations, in
//  degrees.
//  * The forwards vector will be rotated by the input vector
//  *
//  * Code ported from Irrlicht: http://irrlicht.sourceforge.net/
//  */
// kmVec3* kmVec3RotationToDirection(kmVec3* pOut, const kmVec3* pIn, const kmVec3* forwards)
// {
//    const kmScalar xr = kmDegreesToRadians(pIn->x);
//    const kmScalar yr = kmDegreesToRadians(pIn->y);
//    const kmScalar zr = kmDegreesToRadians(pIn->z);
//    const kmScalar cr = cos(xr), sr = sin(xr);
//    const kmScalar cp = cos(yr), sp = sin(yr);
//    const kmScalar cy = cos(zr), sy = sin(zr);
//
//    const kmScalar srsp = sr*sp;
//    const kmScalar crsp = cr*sp;
//
//    const kmScalar pseudoMatrix[] = {
//       (cp*cy), (cp*sy), (-sp),
//       (srsp*cy-cr*sy), (srsp*sy+cr*cy), (sr*cp),
//       (crsp*cy+sr*sy), (crsp*sy-sr*cy), (cr*cp)
//    };
//
//    pOut->x = forwards->x * pseudoMatrix[0] +
//              forwards->y * pseudoMatrix[3] +
//              forwards->z * pseudoMatrix[6];
//
//    pOut->y = forwards->x * pseudoMatrix[1] +
//              forwards->y * pseudoMatrix[4] +
//              forwards->z * pseudoMatrix[7];
//
//    pOut->z = forwards->x * pseudoMatrix[2] +
//              forwards->y * pseudoMatrix[5] +
//              forwards->z * pseudoMatrix[8];
//
//    return pOut;
// }
//
// /**
//  * Reflects a vector about a given surface normal. The surface normal is
//  * assumed to be of unit length.
//  */
// kmVec3* kmVec3Reflect(kmVec3* pOut, const kmVec3* pIn, const kmVec3* normal) {
//   kmVec3 tmp;
//   kmVec3Scale(&tmp, normal, 2.0f * kmVec3Dot(pIn, normal));
//   kmVec3Subtract(pOut, pIn, &tmp);
//
//   return pOut;
// }

} // end namespace Broome

#endif // VECTOR_FUNCTIONS_HPP
