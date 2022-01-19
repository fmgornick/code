/**
 * @file battery.h
 */
#ifndef BATTERY_H_
#define BATTERY_H_
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief battery class. Drone and Robot objects have batteries that deplete
 * over time.  This class is used to represent the life of our drone and robot
 * movable entities.
 */
class Battery {
public:
  /**
   * @brief default constructor
   */
  Battery() : maxCharge(10.0), remainingCharge(10.0), noCharge(false) {}
  /**
   * @brief constructor that takes arguments
   */
  Battery(double max, double remaining, bool isEmpty)
      : maxCharge(max), remainingCharge(remaining), noCharge(isEmpty) {}
  /**
   * @brief getter: returns battery's capacity
   */
  double GetMaxCharge() { return maxCharge; }
  /**
   * @brief getter: returns charge left on battery
   */
  double GetRemainingCharge() { return remainingCharge; }
  /**
   * @brief acts as a getter of our noCharge member variable. Just returns true
   * or false on whether or not the battery is depleted.
   */
  bool IsEmpty() { return noCharge; }
  /**
   * @brief this method changes the actual battery level.  This operation would
   * usually be called by a drone in it's update method.
   */
  void Drain(double percentage) {
    if (percentage >= remainingCharge) {
      remainingCharge = 0.0;
      noCharge = true;
    } else
      remainingCharge -= percentage;
  }

private:
  /** @brief float depicting max charge of battery */
  double maxCharge;
  /** @brief float depicting remaining charge of battery */
  double remainingCharge;
  /** @brief boolean telling us whether or not bettery is depleted */
  bool noCharge;
};

#endif // !BATTERY_H_
