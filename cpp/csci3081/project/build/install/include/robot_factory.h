/**
 * @file robot_factory.h
 */
#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i_entity_factory.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief Robot Factory.  When called, it creates a new object of type Robot.
 * This factory is never called directly, and is really only used through the
 * composite entity factory.
 */
class RobotFactory : public iEntityFactory {
public:
  /**
   * @brief checks if type specified is robot.  If so it creates and returns
   * a pointer to our new robot object.  But if the type doesn't match, then
   * it just returns a null pointer.
   */
  iEntity *CreateEntity(picojson::object &entity, Camera *camera);
};

#endif // !ROBOT_FACTORY_H_
