#include "beeline_movement.h"
#include <math.h>

BeelineMovement::BeelineMovement(Vector3 curr, Vector3 tar, double sp)
    : current(curr), target(tar), speed(sp) {}

Vector3 BeelineMovement::GetPosition() { return current; }
Vector3 BeelineMovement::GetVelocity() { return velocity; }

Vector3 BeelineMovement::UpdateVelocity(double dt, Vector3 curr, Vector3 tar, double time) {
  current = curr;
  //target = tar;
  // calculate direction d = target-current
  Vector3 direction = target - current;
  // normalize direction d= d/|d|
  direction = direction.Normalize();
  // calculate velocity v = d*speed
  velocity = direction * speed;
  // distance traveled s= v*dt
  distanceTraveled = velocity.GetMagnitude() * dt;

  return velocity;
}

bool BeelineMovement::isMoving() {
  // calculate displacement vector
  Vector3 displacement = target - current;
  // find magnitude to calculate cartesian displacement
  double distance = displacement.GetMagnitude();
  // arbitrary threshold, if the distance between target and current
  // is less than it then the drone is not moving
  if (distance < 10) {
    return false;
  }
  return true;
}
