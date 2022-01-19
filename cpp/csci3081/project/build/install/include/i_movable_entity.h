/**
 * @file i_movable_entity.h
 */
#ifndef I_MOVABLE_ENTITY_H_
#define I_MOVABLE_ENTITY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "battery.h"
#include "i_entity.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief derived class of entity.  This is an abstract class that represents
 * entities that move.  This class gets implemented by the Drone and Robot
 * entities.
 */
class iMovableEntity : public iEntity {
public:
  /**
   * @brief Destructor.
   */
  virtual ~iMovableEntity() {}
  /**
   * @brief getter: returns entity identification number
   */
  virtual int GetID() = 0;
  /**
   * @brief getter: returns entity name
   */
  virtual const std::string &GetName() const = 0;
  /**
   * @brief getter: returns entity position
   */
  virtual Vector3 *GetPosition() = 0;
  /**
   * @brief setter: updates or initializes position
   */
  virtual void SetPosition(Vector3 &pos) = 0;
  /**
   * @brief getter: returns entity's velocity
   */
  virtual Vector3 *GetVelocity() = 0;
  /**
   * @brief setter: updates or initializes velocity
   */
  virtual void SetVelocity(Vector3 &vel) = 0;
  /**
   * @brief Get the Direction vector
   *
   * @return Vector3
   */
  virtual Vector3 *GetDirection() = 0;
  /**
   * @brief Set the Direction vector
   *
   * @param dir
   */
  virtual void SetDirection(Vector3 &dir) = 0;
  /**
   * @brief returns current battery life of entity
   */
  virtual Battery *GetBattery() = 0;
  /**
   * @brief updates the entity's position and other dynamic properties
   */
  virtual void Update(double dt) = 0;
  /**
   * @brief The copy constructor for iMovableEntity
   */
  // virtual iMovableEntity * clone() = 0;
};

#endif // !I_MOVABLE_ENTITY_H_
