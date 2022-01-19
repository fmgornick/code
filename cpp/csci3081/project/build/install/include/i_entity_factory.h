/**
 * @file i_entity_factory.h
 */
#ifndef I_ENTITY_FACTORY_H_
#define I_ENTITY_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "camera.h"
#include "drone.h"
#include "hospital.h"
#include "i_entity.h"
#include "i_movable_entity.h"
#include "picojson.h"
#include "recharge_station.h"
#include "robot.h"
/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief entity factory interface.  Used for our abstract factory method for
 * makine new entity objects at run time.  Implementation is done carried out by
 * DroneFactory, RobotFactory, hospitalFactory, and RechargeStationFactory.
 */
class iEntityFactory {
public:
  virtual iEntity *CreateEntity(picojson::object &entity, Camera *camera) = 0;
};

#endif // !I_ENTITY_FACTORY_H_
