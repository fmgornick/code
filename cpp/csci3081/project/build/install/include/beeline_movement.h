/**
 * @file beeline_movement.h
 */
#ifndef BEELINE_MOVEMENT_H_
#define BEELINE_MOVEMENT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "drone.h"
#include "i_movement_strategy.h"
#include "vector3.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief Beeline movement- will move directly towards a robot given a vector3
 * position. extends iMovementStrategy so each function overwrites the parent
 */
class BeelineMovement : public iMovementStrategy {
public:
  /**
   * @brief Constructor taking in Vector3 objects for current position, target
   * position, and a double speed at which the drone is traveling at
   */
  BeelineMovement(Vector3 current, Vector3 target, double speed);
  /**
   * @brief Current position getter
   *
   * @return Vector3 position
   */
  Vector3 GetPosition();
  /**
   * @brief Current velocity getter
   *
   * @return Vector3 velocity
   */
  Vector3 GetVelocity();
  /**
   * @brief Function to update velocity, takes in a double for time and Vector3
   * objects for current and target positions
   *
   * @return Vector3 velocity
   */
  Vector3 UpdateVelocity(double dt, Vector3 current, Vector3 target, double time);
  bool isMoving();

private:
  /**
   * @brief Vector3 current- current position
   */
  Vector3 current;
  /**
   * @brief Vector3 target- target position
   */
  Vector3 target;
  /**
   * @brief Vector3 velocity- current velocity
   */
  Vector3 velocity;
  /**
   * @brief double speed- current speed
   */
  double speed;
  /**
   * @brief double distanceTraveled- distace traveled using beeline
   */
  double distanceTraveled;
};

#endif
