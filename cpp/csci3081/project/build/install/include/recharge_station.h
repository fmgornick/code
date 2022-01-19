/**
 * @file recharge_station.h
 */
#ifndef RECHARGE_STATION_H_
#define RECHARGE_STATION_H_
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
 * @brief if our drone runs low on battery and must recharge, then it visits one
 * of these stations to replenish the battery
 */
class RechargeStation : public iEntity {
public:
  /**
   * @brief default constructor
   */
  RechargeStation() : id(0), name("recharge station"), position(new Vector3) {}
  /**
   * @brief constructor that takes position argument
   */
  RechargeStation(int id, std::string name, Vector3 *pos)
      : id(id), name(name), position(pos) {}
  /**
   * @brief Getter: returns recharge station identification number
   */
  int GetID() { return id; }
  /**
   * @brief Getter: returns recharge station name
   */
  const std::string &GetName() const { return name; }
  /**
   * @brief Getter: returns recharge station position
   */
  Vector3 *GetPosition() { return position; }
  /**
   * @brief Setter: updates or initializes position
   */
  void SetPosition(Vector3 &pos) { *position = pos; }

private:
  /** @brief integer ID of our recharge station */
  int id;
  /** @brief recharge station name */
  std::string name;
  /** @brief 3D vector representing position of recharge station */
  Vector3 *position;
};

#endif // !RECHARGE_STATION_H_
