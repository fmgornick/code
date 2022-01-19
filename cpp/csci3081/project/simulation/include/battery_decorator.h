// /**
//  * @file battery_decorator.h
//  */
// #ifndef BATTERY_DECORATOR_H_
// #define BATTERY_DECORATOR_H_

// THE DECORATOR IS CURRENTLY SEGFAULTING, WILL BE PATCHED SOON
// #include "i_movable_entity.h"
// /*******************************************************************************
//  * Class Definitions
//  ******************************************************************************/
// /**
//  * @brief battery decorator class. Takes in an entity and adds battery
//  functionality.
//  */
// class BatteryDecorator : public iMovableEntity {
// public:
//   /**
//    * @brief constructor taking entity argument.
//    */
//   BatteryDecorator(iMovableEntity* entity) : ent(entity) {}
//   ~BatteryDecorator() { delete ent;}

//   /** @brief iEntity pointer referencing the passed entity */
//   iMovableEntity* GetEnt(){
//     return ent;
//   }
//   private:

//   iMovableEntity* ent;

// };

// #endif // !BATTERY_H_
