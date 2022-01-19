// /**
//  * @file concrete_dec.h
//  */

// #ifndef CONCRETE_DEC_H_
// #define CONCRETE_DEC_H_

// #include "battery_decorator.h"

// /*******************************************************************************
//  * Class Definitions
//  ******************************************************************************/
// /**
//  * @brief Concrete instance of decorator class. Drone and Robot objects have
//  batteries that deplete
//  * over time.  This class is used to represent the life of our drone and
//  robot
//  * movable entities.
//  */

// class ConcreteDec : public BatteryDecorator {
// public:
//   /**
//    * @brief default constructor
//    */
//   ConcreteDec(iMovableEntity* ent) : BatteryDecorator(ent), maxCharge(10.0),
//   remainingCharge(10.0), noCharge(false) {}
//   /**
//    * @brief constructor that takes arguments
//    */
//   ConcreteDec(iMovableEntity* ent, double max, double remaining, bool
//   isEmpty)
//       : BatteryDecorator(ent), maxCharge(max), remainingCharge(remaining),
//       noCharge(isEmpty) {}
//   /**
//    * @brief getter: returns battery's capacity
//    */
//   double GetMaxCharge() { return maxCharge; }
//   /**
//    * @brief getter: returns charge left on battery
//    */
//   double GetRemainingCharge() { return remainingCharge; }
//   /**
//    * @brief acts as a getter of our noCharge member variable. Just returns
//    true
//    * or false on whether or not the battery is depleted.
//    */
//   bool IsEmpty() { return noCharge; }
//   /**
//    * @brief this method changes the actual battery level.  This operation
//    would
//    * usually be called by a drone in it's update method.
//    */
//   void Drain(double percentage) {
//     if (percentage >= remainingCharge) {
//       remainingCharge = 0.0;
//       noCharge = true;
//     } else
//       remainingCharge -= percentage;
//   }

//    /**
//    * @brief getter: returns battery id
//    */
//   int GetID() { return GetEnt()->GetID(); }
//   /**
//    * @brief getter: returns battery name
//    */
//   const std::string &GetName() const{ return GetEnt()->GetName(); }
//   /**
//    * @brief getter: returns drone position
//    */
//   Vector3 *GetPosition() { return GetEnt()->GetPosition(); }
//   /**
//    * @brief setter: updates or initializes position
//    */
//   void SetPosition(Vector3 &pos) { GetEnt()->SetPosition(pos); }

//   void Update(double dt){
//     std::cout << GetMaxCharge() << std::endl;
//     GetEnt()->Update(dt);
//   }

//   Vector3 *GetVelocity(){ return GetEnt()->GetVelocity();}
//   void SetVelocity(Vector3 &vel) {GetEnt()->SetVelocity(vel);}
//   Vector3 *GetDirection() {return GetEnt()->GetDirection();}
//   void SetDirection(Vector3 &dir) {GetEnt()->SetDirection(dir);}
//   /*
//    * @brief Get the Speed value
//    *
//    * @return float
//    */

// private:
//   /** @brief float depicting max charge of battery */
//   double maxCharge;
//   /** @brief float depicting remaining charge of battery */
//   double remainingCharge;
//   /** @brief boolean telling us whether or not bettery is depleted */
//   bool noCharge;
// };

// #endif // !BATTERY_H_
