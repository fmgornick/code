/**
 * @file patrol_strategy.h
*/
#ifndef PATROL_STRATEGY_H_
#define PATROL_STRATEGY_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include "i_movement_strategy.h"
#include "vector3.h"
#include "drone.h"
/*******************************************************************************
* Class Definitions
******************************************************************************/
/**
 * @ingroup simulation
 * @brief Patrol movement- Uses a sinusoidal strategy to move in a wave pattern across the map.
 */
class PatrolStrategy : public iMovementStrategy {
   public:
/**
 * @brief Constructor taking in Vector3 objects for current position and a double speed at which the 
 * drone is traveling at
 */
    PatrolStrategy(Vector3 curr, double speed);
/**
 * @brief Current position getter
 * 
 * @return Vector3 position
 */
    Vector3 GetPosition();

    Vector3 GetNextPosition();

  /**
 * @brief Current velocity getter
 * 
 * @return Vector3 velocity
 */
    Vector3 GetVelocity();
/**
 * @brief Function to update velocity, takes in a double for time and Vector3 objects for current and target positions 
 * 
 * @return Vector3 velocity
 */
    Vector3 UpdateVelocity(double dt, Vector3 current, Vector3 target, double time);
    bool isMoving();
    bool seesRobot();

private:
/**
 * @brief Vector3 current- current position
 */
Vector3 current;
/**
 * @brief Vector3 velocity- current velocity
 */
Vector3 velocity;
/**
 * @brief double speed- current speed
 */
double speed;

/**
* @brief double period - period of the sinusoidal function
*/
double period;

/**
* @brief double amplitude - amplitutde of the sinusoidal function
*/
double amplitude;
/**
 * @brief double distanceTraveled- distace traveled using beeline
 */
double distanceTraveled;
};

#endif