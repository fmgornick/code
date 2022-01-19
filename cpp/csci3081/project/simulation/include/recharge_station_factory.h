/**
 * @file recharge_station_factory.h
 */
#ifndef RECHARGE_STATION_FACTORY_H_
#define RECHARGE_STATION_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i_entity_factory.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief Recharge Station Factory.  When called, it creates a new object of
 * type RechargeStation. This factory is never called directly, and is really
 * only used through the composite entity factory.
 */
class RechargeStationFactory : public iEntityFactory {
public:
  /**
   * @brief checks if type specified is recharge station.  If so it creates and
   * returns a pointer to our new recharge station object.  But if the type
   * doesn't match, then it just returns a null pointer.
   */
  iEntity *CreateEntity(picojson::object &entity, Camera *camera);
};

#endif // !RECHARGE_STATION_FACTORY_H_
