/**
 * @file drone.h
 */
#ifndef DRONE_H_
#define DRONE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "i_movable_entity.h"
#include "i_movement_strategy.h"
#include "search_strategy.h"
#include "patrol_strategy.h"
#include "beeline_movement.h"
#include "camera.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup simulation
 * @brief Our actual drone that will be searching for the robot.  Contains tons
 * methods to update postion and velocity. Also has many search patterns to find
 * the target robot.
 */
class Drone : public iMovableEntity{
public:
  /**
   * @brief default constructor
   */
  Drone()
      : id(0), name("drone"), position(new Vector3), velocity(new Vector3),
        direction(new Vector3), speed(0), battery(new Battery), camera(NULL), elapsedTime(0), cameraTime(0) ,
        patroling(false), robotFound(false)
        { 
          startingLocation = Vector3();
        }
  /**
   * @brief drone constructor that takes in variable arguments
   */
  Drone(int id, std::string name, Vector3 *pos, Vector3 *vel, Vector3 *dir,
        double speed, Battery *b, Camera* camera)
      : id(id), name(name), position(pos), velocity(vel), direction(dir),
        speed(speed), battery(b), camera(camera), elapsedTime(0), cameraTime(0),
        patroling(false), robotFound(false)
        { 
          if(camera == NULL)
            hasCamera = false;
          startingLocation = *pos;
        }
  /**
   * @brief getter: returns entity identification number
   */
  int GetID() { return id; }
  /**
   * @brief getter: returns drone name
   */
  const std::string &GetName() const { return name; }
  /**
   * @brief getter: returns drone position
   */
  Vector3 *GetPosition() { return position; }
  /**
   * @brief setter: updates or initializes position
   */
  void SetPosition(Vector3 &pos) { *position = pos; }
  /**
   * @brief Get the Speed value
   *
   * @return float
   */
  double GetSpeed() { return speed; }
  /**
   * @brief Set the Speed value
   *
   * @param speed
   */
  void SetSpeed(double speed) { this->speed = speed; }
  /**
   * @brief getter: returns drone velocity
   */
  Vector3 *GetVelocity() { return velocity; }
  /**
   * @brief setter: updates or initializes velocity
   */
  void SetVelocity(Vector3 &vel) { *velocity = vel; }
  /**
   * @brief Get the Direction vector
   *
   * @return Vector3
   */
  Vector3 *GetDirection() { return direction; }
  /**
   * @brief Set the Direction vector
   *
   * @param dir
   */
  void SetDirection(Vector3 &dir) { *direction = dir; }
  /**
   * @brief returns current battery life of drone
   */
  Battery *GetBattery() { return battery; }
  /**
   * @brief updates the drone position and other dynamic properties
   */
  void Update(double dt);
  /**
   * @brief updates the camera
   */
  void CameraUpdate(double dt);
  /**
   * @brief Set the Robot Found object
   * 
   * @param robotLocation 
   * @param hospitalLocation 
   */
  void SetRobotFound(Vector3 robotLocation, Vector3 hospitalLocation);
  /**
   * @brief Destroy the Drone object
   */
  ~Drone() {}
  /**
   * @brief Copy Constructor for drone
   */
  Drone(const Drone &drone) {}
  /**
   * @brief The = operator for the drone
   */
  void operator=(const Drone &) {}
  /**
   * @brief Set the Movement Startegy object
   * 
   * @param strategy 
   */
  void SetMovementStartegy(iMovementStrategy *strategy) { movement = strategy; }
  /**
   * @brief Sets the Search Strategy
   */
  void SetSearchStrategy(SearchStrategy *searchStrategy) {
    search = searchStrategy;
    if(search == nullptr){
      return;
    }
    search->ParseJson();
  };
  /**
   * @brief Set the Rescue Drone object
   * 
   * @param rescueDrone 
   */
  void SetRescueDrone(Drone* rescueDrone) {
    this->rescueDrone = rescueDrone;
  }

  //************************************************
  // TEMPORARY PLEASE DELETE
  //************************************************
  //void SetKeyboard(float x, float y, float z, float a) { *direction = Vector3(x, y, z); }

private:
  
  /** @brief integer ID of our drone */
  int id;
  /** @brief drone name */
  std::string name;
  /** @brief 3D vector representing drone's position */
  Vector3 *position;
  /** @brief 3D vector representing drone's velocity */
  Vector3 *velocity;
  /** @brief 3D vector representing drone's direction */
  Vector3 *direction;
  /** @brief the speed the drone can move*/
  double speed;
  /** @brief battery object representing life remaining in drone */
  Battery *battery;
  /** @brief the movement strategy object for the drone*/
  iMovementStrategy *movement;
  /** @brief Camera object for the drone*/
  Camera *camera; 
  /** @brief keeps track of elapsed time*/
  double elapsedTime ;
  /** @brief The search strategy for the drone*/
  double cameraTime ;
  /** @brief The search strategy for the drone*/
  SearchStrategy *search;
  /** @brief Has the robot been found for navigation */
  bool robotFound = false;
  /** @brief Should the drone start patroling, this happens if the drone starts in the bottom left corner */
  bool patroling = false;
  /** @brief The found robot's location */
  Vector3 robotLocation;
  /** @brief The starting location of the drone */
  Vector3 startingLocation;
  /** @brief should this drone be taking pictures to search for the drone? */
  bool hasCamera = true;
  /** @brief The drone that will rescue the robot */
  Drone* rescueDrone;
};

#endif // !DRONE_H_
