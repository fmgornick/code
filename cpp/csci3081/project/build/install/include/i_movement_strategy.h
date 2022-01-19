/**
 * @file movement_strategy.h
 */

#ifndef I_MOVEMENT_STRATEGY_H_
#define I_MOVEMENT_STRATEGY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "vector3.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @ingroup simulation
 * @brief This is the base class for all movement. Movement startegies can
 * inherit this interface and when it's active the Update method will be called
 * the strategy then must correctly update the position and velocity so that
 * the entity can move accordinaly.
 * 
 */
class iMovementStrategy {
    public:
        /**
        * @brief Destroy the i Movement Strategy object
        * 
        */
        ~iMovementStrategy() {}
        /**
         * @brief Get the Position object
         * 
         * @return Vector3 
         */
        virtual Vector3 GetPosition() = 0;
        /**
         * @brief Get the Velocity object
         * 
         * @return Vector3 
         */
        virtual Vector3 GetVelocity() = 0;
        /**
         * @brief Updates the velocity of the movement strategy
         * 
         * @param dt, delta time, drone current position, drone target position
         */
        virtual Vector3 UpdateVelocity(double dt, Vector3 current, Vector3 target, double time) = 0;

        virtual bool isMoving() {};
};

#endif