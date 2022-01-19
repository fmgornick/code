/**
 * @file entity.h
 */
#ifndef I_ENTITY_H_
#define I_ENTITY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "vector3.h"
#include <string>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief The base class for all entities. Drones, Robots, Hospitals, and
 * Recharge Stations are all entities.  This class is abstract, so it's not
 * meant to be instantiated.
 */
class iEntity {
public:
  /**
   * @brief Destructor.
   */
  virtual ~iEntity() {}
  /**
   * @brief Getter: returns entity identification number
   */
  virtual int GetID() = 0;
  /**
   * @brief Getter: returns entity name
   */
  virtual const std::string &GetName() const = 0;
  /**
   * @brief Getter: returns entity position
   */
  virtual Vector3 *GetPosition() = 0;
  /**
   * @brief Setter: updates or initializes position
   */
  virtual void SetPosition(Vector3 &pos) = 0;
  /**
   * @brief The copy constructor for iEntity
   */
  // virtual iEntity* clone() const = 0;
};

#endif // !I_ENTITY_H_
