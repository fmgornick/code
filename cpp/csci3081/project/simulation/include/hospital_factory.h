/**
 * @file hospital_factory.h
 */
#ifndef HOSPITAL_FACTORY_H_
#define HOSPITAL_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i_entity_factory.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief Hospital Factory.  When called, it creates a new object of type
 * Hospital. This factory is never called directly, and is really only used
 * through the composite entity factory.
 */
class HospitalFactory : public iEntityFactory {
public:
  /**
   * @brief checks if type specified is hospital.  If so it creates and returns
   * a pointer to our new hospital object.  But if the type doesn't match, then
   * it just returns a null pointer.
   */
  iEntity *CreateEntity(picojson::object &entity, Camera *camera);
};

#endif // !HOSPITAL_FACTORY_H_
