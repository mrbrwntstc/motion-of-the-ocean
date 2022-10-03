#ifndef __MOTION_PARTICLE_H__
#define __MOTION_PARTICLE_H__

#include "core.h"

namespace motion
{
  /**
   * The simplest object that can be simulated in the physics system
   */
  class Particle
  {
  public:
    /**
     * Integrates the particle forward in time by the given amount.
     * This function uses a Newton-Euler integration method, which is a linear approximation to the correct integral.
     * For this reason, it may be inaccurate in some cases.
     * 
     * @param duration the time interval in seconds
     */
    void integrate(real duration);

    /**
     * Clears the forces applied to the particle
     * This will be called automatically after each integration step.
     */
    void clear_accumulator();

    /** Return the value of the energy the particle possess due to its motion */
    real calculate_kinetic_energy();

  protected:
    /** linear position of the particle in world space */
    Vector3 position;

    /** linear velocity of the particle in world space */
    Vector3 velocity;

    /** 
     * linear acceleration of the particle in world space 
     * this value can be used to set acceleration due to gravity (primary use), or any other constant acceleration
    */
    Vector3 acceleration;

    /**
     * Holds the amount of damping applied to linear motion.
     * Damping is required to remove energy added through numerical instability in the integrator.
     */
    real damping;

    /**
     * Holds the inverse of the mass of the particle.
     * It is more useful to hold the inverse mass for a number of reasons
     * Integration is simpler
     * Infinite mass is more useful than 0 mass (0 acceleration more useful than infinite acceleration)
     */
    real inverse_mass;

    /**
     * Holds the accumulated force to be applied at the next simulation iteration only.
     * This value is zeroed at each integration step.
     */
    Vector3 force_accumulator;
  };
}

#endif // __MOTION_PARTICLE_H__