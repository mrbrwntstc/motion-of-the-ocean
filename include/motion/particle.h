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
     * Sets the mass of the particle.
     * 
     * @param mass The new mass of the body.
     * This may not be zero.
     * Small masses can produce unstable rigid bodies under simulation.
     * 
     * @warning This invalidates internal data for the particle.
     * Either an integration function, or the calculate_internals function should be called before trying to get any settings from the particle
     */
    void set_mass(const real mass);

    /**
     * @brief Get the mass of the particle
     * 
     * @return The current mass of the particle
     */
    real get_mass() const;

    /**
     * @brief Set the inverse mass of the particle
     * 
     * @param inverse_mass The new inverse mass of the body.
     * This may be zero for a body with infinite mass
     * 
     * @warning This invalidates internal data for the particle.
     * Either an integration function, or the calculate_internals function should be called before trying to get any settings from the particle
     */
    void set_inverse_mass(const real inverse_mass);

    /**
     * @brief Get the inverse mass of the particle
     * 
     * @return The current inverse mass of the particle
     */
    real get_inverse_mass() const;

    /**
     * @return true  the particle has finite mass
     * @return false the particle has infinite mass
     */
    bool has_finite_mass() const;

    /** sets the damping of the particle */
    void set_damping(const real damping);

    /**
     * @return the current damping value 
     */
    real get_damping() const;

    /**
     * @brief Set the position of the particle
     * 
     * @param position the new position of the particle
     */
    void set_position(const Vector3 &position);

    /**
     * @brief Set the position of the particle by component
     * 
     * @param x The x-coordinate of the new position of the rigid body
     * @param y The y-coordinate of the new position of the rigid body
     * @param z The z-coordinate of the new position of the rigid body
     */
    void set_position(const real x, const real y, const real z);
    
    /**
     * @brief Fills the given vector with the position of the particle
     * 
     * @param position A pointer to a vector to write the current position into
     */
    void get_position(Vector3 *position) const;

    /**
     * @brief Get the position of the particle
     * 
     * @return The position of the particle
     */
    Vector3 get_position() const;

    /**
     * @brief Set the velocity of the particle
     * 
     * @param velocity The new velocity of the particle
     */
    void set_velocity(const Vector3 &velocity);

    /**
     * @brief Set the velocity of the particle by component
     * 
     * @param x The x-coordinate of the new position of the rigid body
     * @param y The y-coordinate of the new position of the rigid body
     * @param z The z-coordinate of the new position of the rigid body
     */
    void set_velocity(const real x, const real y, const real z);

    /**
     * Fills the given vector with the velocity of the particle
     * 
     * @param velocity A pointer to a vector to write the velocity.
     * The velocity is given in world local space
     */
    void get_velocity(Vector3 *velocity) const;

    /**
     * Gets the velocity of the particle
     * 
     * @return The velocity of the particle.
     * The velocity is given in world space.
     */
    Vector3 get_velocity() const;

    /**
     * Sets the constant acceleration of the particle.
     * 
     * @param acceleration The new acceleration of the particle
     */
    void set_acceleration(const Vector3 &acceleration);

    /**
     * Sets the constant acceleration of the particle by component
     * 
     * @param x The x-coordinate of the particle of the rigid body
     * @param y The y-coordinate of the particle of the rigid body
     * @param z The z-coordinate of the particle of the rigid body
     */
    void set_acceleration(const real x, const real y, const real z);

    /**
     * Gets the acceleration of the particle.
     * 
     * @param acceleration A pointer to a vector to write the acceleration.
     * The acceleration is given in world local space.
     */
    void get_acceleration(Vector3 *acceleration) const;

    /**
     * Gets the acceleration of the particle.
     * 
     * @return The acceleration of the particle.
     * The acceleration is given in world local space.
     */
    Vector3 get_acceleration() const;

    /**
     * Clears the forces applied to the particle
     * This will be called automatically after each integration step.
     */
    void clear_accumulator();

    /**
     * Adds the given force to the particle. This will only apply at the next iteration.
     * 
     * @param force The force to apply.
     */
    void add_force(const Vector3 &force);

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