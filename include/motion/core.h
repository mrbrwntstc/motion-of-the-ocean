#ifndef __MOTION_CORE_H__
#define __MOTION_CORE_H__

#include <math.h>

#include "precision.h"

namespace motion
{
  /**
   * Holds a 3-dimensional vector.
   * Four data members are allocated to ensure alignment in array.
   */
  class Vector3
  {
  public: // methods
    /** zero-vector */
    Vector3() : x(0), y(0), z(0) {}

    /** Creates a vector with the given components */
    Vector3(const real x, const real y, const real z)
      : x(x), y(y), z(z) {}

    /** Flips all the components in the vector */
    void invert()
    {
      x = -x;
      y = -y;
      z = -z;
    }

    /** Gets the magnitude (length) of this vector */
    real magnitude() const
    {
      return real_sqrt(x*x + y*y + z*z);
    }

    /** Gets the squared magnitude of this vector */
    real squared_magnitude() const
    {
      return (x*x) + (y*y) + (z*z);
    }

    /** turns a non-zero vector into a unit vector */
    void normalize()
    {
      real length = magnitude();
      if(length > 0)
      {
        (*this) *= ((real)length) / length;
      }
    }

    /** multiply this vector by the given scalar */
    void operator*=(const real value)
    {
      x *= value;
      y *= value;
      z *= value;
    }

    /** returns a copy of this vector scaled to the given value */
    Vector3 operator*(const real value) const
    {
      return Vector3(x*value, y*value, z*value);
    }

    /** Adds the given vector to this */
    void operator+=(const Vector3& v)
    {
      x += v.x;
      y += v.y;
      z += v.z;
    }

    /** Returns the value of the given vector added to this */
    Vector3 operator+(const Vector3& v) const
    {
      return Vector3(x+v.x, y+v.y, z+v.z);
    }

    /** Subtracts the given vector from this */
    void operator-=(const Vector3& v)
    {
      x -= v.x;
      y -= v.y;
      z -= v.z;
    }

    /** Returns the value of the given vector subtracted from this */
    Vector3 operator-(const Vector3& v) const
    {
      return Vector3(x-v.x, y-v.y, z-v.z);
    }

    /** Adds the given vector to this, scaled by the given amount */
    void add_scaled_vector(const Vector3& vector, real scale)
    {
      x += vector.x * scale;
      y += vector.y * scale;
      z += vector.z * scale;
    }

    /** calculates and returns a component-wise product of this vector and the given vector */
    Vector3 component_product(const Vector3& vector) const
    {
      return Vector3(x*vector.x, y*vector.y, z*vector.z);
    }

    /** Performs a component-wise product with this given vector and sets this vector to its result */
    void component_product_update(const Vector3& vector)
    {
      x *= vector.x;
      y *= vector.y;
      z *= vector.z;
    }

    /** calculates and returns the scalar product of this vector with the given vector */
    real scalar_product(const Vector3 &vector) const
    {
      return x*vector.x + y*vector.y + z*vector.z;
    }

    /** calculates and returns the scalar product of this vector with the given vector */
    real operator*(const Vector3 &vector) const
    {
      return x*vector.x + y*vector.y + z*vector.z;
    }

    /** Calculates and returns the vector product of this vector with the given vector */
    Vector3 vector_product(const Vector3 &vector) const
    {
      return Vector3(y*vector.z - z*vector.y,
                     z*vector.x - x*vector.z,
                     x*vector.y - y*vector.x);
    }

    /** updates this vector to be the vector product of its current value and the given vector */
    void operator%=(const Vector3 &vector)
    {
      *this = vector_product(vector);
    }

    /** Calculates and returns the vector product of this vector with the given vector */
    Vector3 operator%(const Vector3 &vector) const
    {
      return Vector3(y*vector.z - z*vector.y,
                     z*vector.x - x*vector.z,
                     x*vector.y - y*vector.x);
    }

  public: // fields
    /** Holds the value along the x-axis */
    real x;

    /** Holds the value along the y-axis */
    real y;

    /** Holds the value along the z-axis */
    real z;
  
  private: // fields
    /** padding to ensure 4 word alignment */
    real pad;
  };
}

#endif // __MOTION_CORE_H__