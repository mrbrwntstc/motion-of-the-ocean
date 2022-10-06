#ifndef __MOTION_PRECISION_H__
#define __MOTION_PRECISION_H__

#include <float.h>

namespace motion
{
  /**
   * Defines a real number precision.
   * Cyclone can be compiled in single- or double-precision versions.
   * By default, single-precision is provided.
   */
  typedef float real;

  /** defines the precision of the square root operator */
  #define real_sqrt sqrtf

  /** defines the precision of the power operator */
  #define real_pow powf

  /** defines the precision of the absolute value operator */
  #define real_abs fabs

  /** Defines the highest value for the real number */
  #define REAL_MAX FLT_MAX

}

#endif // __MOTION_PRECISION_H__
