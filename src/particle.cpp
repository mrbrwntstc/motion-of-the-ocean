#include <assert.h>
#include "motion/particle.h"

using namespace motion;

void Particle::integrate(real duration)
{
  // we don't integrate with infinite mass
  if(this->inverse_mass <= 0.0f)
    return;

  assert(duration > 0.0);

  // update linear position
  this->position.add_scaled_vector(this->velocity, duration);

  // work out the acceleration from the force
  // (we'll add to this vector when we come to generate forces)
  Vector3 resulting_acceleration = this->acceleration;

  // update linear velocity from the acceleration
  this->velocity.add_scaled_vector(resulting_acceleration, duration);

  // impose drag
  this->velocity *= real_pow(this->damping, duration);

  // clear the forces
  this->clear_accumulator();
}

void Particle::clear_accumulator()
{
  this->force_accumulator.clear();
}

void Particle::set_mass(const real mass)
{
  assert(mass != 0);
  Particle::inverse_mass = ((real)1.0)/mass;
}

real Particle::get_mass() const
{
  if(this->inverse_mass == 0)
    return REAL_MAX;
  else
    return ((real)1.0)/this->inverse_mass;
}

void Particle::set_inverse_mass(const real inverse_mass)
{
  Particle::inverse_mass = inverse_mass;
}

real Particle::get_inverse_mass() const
{
  return inverse_mass;
}

bool Particle::has_finite_mass() const
{
  return inverse_mass >= (real)0;
}

void Particle::set_damping(const real damping)
{
  Particle::damping = damping;
}

real Particle::get_damping() const
{
  return damping;
}

void Particle::set_position(const Vector3 &position)
{
  Particle::position = position;
}

void Particle::set_position(const real x, const real y, const real z)
{
  position.x = x;
  position.y = y;
  position.z = z;
}

void Particle::get_position(Vector3 *position) const
{
  *position = Particle::position;
}

Vector3 Particle::get_position() const
{
  return position;
}

void Particle::set_velocity(const Vector3 &velocity)
{
  Particle::velocity = velocity;
}

void Particle::set_velocity(const real x, const real y, const real z)
{
  velocity.x = x;
  velocity.y = y;
  velocity.z = z;
}

void Particle::get_velocity(Vector3 *velocity) const
{
  *velocity = Particle::velocity;
}

Vector3 Particle::get_velocity() const
{
  return velocity;
}

void Particle::set_acceleration(const Vector3 &acceleration)
{
  Particle::acceleration = acceleration;
}

void Particle::set_acceleration(const real x, const real y, const real z)
{
  acceleration.x = x;
  acceleration.y = y;
  acceleration.z = z;
}

void Particle::get_acceleration(Vector3 *acceleration) const
{
  *acceleration = Particle::acceleration;
}

Vector3 Particle::get_acceleration() const
{
  return acceleration;
}

void Particle::add_force(const Vector3 &force)
{
  force_accumulator += force;
}

real Particle::calculate_kinetic_energy()
{
  return 0.5 * ((real)1/this->inverse_mass) * (this->velocity * this->velocity);
}
