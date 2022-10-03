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

real Particle::calculate_kinetic_energy()
{
  return 0.5 * ((real)1/this->inverse_mass) * (this->velocity * this->velocity);
}
