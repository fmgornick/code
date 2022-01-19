/**
 * @file hospital.h
 */
#ifndef HOSPITAL_H_
#define HOSPITAL_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i_entity.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief once our robot is found, we're gonna want to rescue it by taking it to
 the hospital.  Thus we need a hospital entity
 */
class Hospital : public iEntity {
public:
  /**
   * @brief default constructor
   */
  Hospital() : id(0), name("hospital"), position(new Vector3) {}
  /**
   * @brief constructor that takes position argument
   */
  Hospital(int id, std::string name, Vector3 *pos)
      : id(id), name(name), position(pos) {}
  /**
   * @brief Getter: returns hospital identification number
   */
  int GetID() { return id; }
  /**
   * @brief Getter: returns hospital name
   */
  const std::string &GetName() const { return name; }
  /**
   * @brief Getter: returns hospital position
   */
  Vector3 *GetPosition() { return position; }
  /**
   * @brief Setter: updates or initializes position
   */
  void SetPosition(Vector3 &pos) { *position = pos; }

private:
  /** @brief integer ID of our hospital */
  int id;
  /** @brief hospital name */
  std::string name;
  /** @brief 3D vector representing position of hospital */
  Vector3 *position;
};

#endif // !HOSPITAL_H_
