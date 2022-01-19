/**
 * @file drone_factory.h
 */
#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "beeline_movement.h"
#include "breadth_first_search.h"
#include "deapth_first_search.h"
#include "i_entity_factory.h"
#include "patrol_strategy.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief Drone Factory.  When called, it creates a new object of type Drone.
 * This factory is never called directly, and is really only used through the
 * composite entity factory.
 */
class DroneFactory : public iEntityFactory {
public:
  /**
   * @brief checks if type specified is drone.  If so it creates and returns a
   * pointer to our new drone object.  But if the type doesn't match, then it
   * just returns a null pointer.
   */
  iEntity *CreateEntity(picojson::object &entity, Camera *camera);
};

#endif // !DRONE_FACTORY_H_
