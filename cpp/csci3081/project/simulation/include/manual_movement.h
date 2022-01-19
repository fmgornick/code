// /**
//  * @file manual_movement.h
//  */
// #ifndef MANUAL_MOVEMENT_H_
// #define MANUAL_MOVEMENT_H_

// /*******************************************************************************
//  * Includes
//  ******************************************************************************/
// #include "drone.h"
// #include "i_movement_strategy.h"
// #include "web_app.h"
// /*******************************************************************************
//  * Class Definitions
//  ******************************************************************************/
// /**
//  * @ingroup simulation
//  * @brief Manual movement- Takes JSON keypress values to manually move the drone.
//  *  Extends iMovementStrategy so each function overwrites the parent.
//  */
// class ManualMovement : public iMovementStrategy {
// public:
//   /**
//    * @brief Constructor - need to make some kind of getter in webapp; picojson::object* keys similar to web* keys
//    */
//   ManualMovement(web *keys, Vector3 current, double direction, double dt, double speed);
//   /**
//    * @brief Current position getter
//    *
//    * @return Vector3 position
//    */
//   Vector3 GetPosition();
//   /**
//    * @brief Current velocity getter
//    *
//    * @return Vector3 velocity
//    */
//   Vector3 GetVelocity();
//   /**
//    * @brief Function to update velocity, takes in a double for time and Vector3
//    * objects for current and target positions
//    *
//    * @return Vector3 velocity
//    */
//   Vector3 UpdateVelocity(double dt, Vector3 current, Vector3 target, double time);
//   bool isMoving();
//   /**
//    * @brief Function to move drone
//    */
//   void move();
//   /**
//    * @brief Function to set joystick to get keyboard presses
//    */
//   void setJoystick(double x, double y, double z, double p);
// private:
//   /**
//    * @brief Vector3 current- current position
//    */
//   Vector3 current;
//   /**
//    * @brief Vector3 target- target position
//    */
//   Vector3 target;
//   /**
//    * @brief Vector3 velocity- current velocity
//    */
//   Vector3 velocity;
//   /**
//    * @brief double speed- current speed
//    */
//   double speed;
//   double direction;
// };

// #endif
