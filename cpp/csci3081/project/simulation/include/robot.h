/**
 * @file robot.h
 */
#ifndef ROBOT_H_
#define ROBOT_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i_entity.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief robot is a movable entity.  This robot will be placed randomly in
 * minneapolis, and our goal is to use our drone to find this robot entity
 * within a given time limit.
 */
class Robot : public iEntity {
public:
  /**
   * @brief default constructor
   */
  Robot()
      : id(0), name("robot"), position(new Vector3) {}
  /**
   * @brief constructor that takes arguments
   */
  Robot(int id, std::string name, Vector3 *pos)
      : id(id), name(name), position(pos) {}
  /**
   * @brief getter: returns entity identification number
   */
  int GetID() { return id; }
  /**
   * @brief getter: returns entity name
   */
  const std::string &GetName() const { return name; }
  /**
   * @brief getter: returns entity position
   */
  Vector3 *GetPosition() { return position; }
  /**
   * @brief setter: updates or initializes position
   */
  void SetPosition(Vector3 &pos) { *position = pos; }

private:
  /** @brief integer ID of our robot (may not be neccessary) */
  int id;
  /** @brief robot name */
  std::string name;
  /** @brief 3D vector representing robot's position */
  Vector3 *position;
};

#endif // !ROBOT_H_
