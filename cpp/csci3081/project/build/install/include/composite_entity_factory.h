/**
 * @file composite_entity_factory.h
 */
#ifndef COMPOSITE_ENTITY_FACTORY_H_
#define COMPOSITE_ENTITY_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "drone_factory.h"
#include "hospital_factory.h"
#include "i_entity_factory.h"
#include "recharge_station_factory.h"
#include "robot_factory.h"

#include <list>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief Composite Entity Factory.  This is the class that get's called when
 * creating new entities.  Has an entity factory vector member variable to keep
 * track of all the factories.  Then when we want to create a new factory, it's
 * added to the vector to be referenced for entity creation.
 */
class CompositeEntityFactory : public iEntityFactory {
public:
  CompositeEntityFactory();
  /**
   * @brief adds factory to vector. This vector is used to create entities of a
   * specific type in the CreateEntity function.
   */
  void AddFactory(iEntityFactory *factory);
  /**
   * @brief loops through vector of entity factories creating new entities until
   * a null pointer isn't returned.  If the object doesn't match the factory
   * called, then they return null pointers.
   */
  iEntity *CreateEntity(picojson::object &entity, Camera *camera);

private:
  /** @brief vector of iEntityFactory pointers */
  std::list<iEntityFactory *> factories;
};
#endif // !COMPOSITE_ENTITY_FACTORY_H_
