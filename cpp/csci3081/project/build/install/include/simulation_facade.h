/**
 * @file simulation_facade.h
 */
#ifndef SIMULATION_FACADE_H_
#define SIMULATION_FACADE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "WebServer.h"
#include "camera_controller.h"
#include "drone.h"
#include "i_entity.h"
#include "i_movable_entity.h"

#include "camera.h"

#include "logger_manager.h"

#include <memory>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class SimulationFacade {
public:
  /**
   * @ingroup simulation
   * @brief Construct a new Simulation Facade object.
   *
   */
  SimulationFacade();
  /**
   * @brief Get a CreateEntity command from the JSON scene
   * and populate the entities and movableEntities array with the JSON object.
   *
   * @param entityData
   */
  void CreateEntityCmd(picojson::object &entityData,
                       ICameraController &cameraController);
  /**
   * @brief Adds an iEntity object to the entities vector
   *
   * @param entity
   */
  void AddEntity(iEntity *entity);
  /**
   * @brief Adds an iMovableEntity object to the movableEntities vector
   *
   * @param entity
   */
  void UpdateEntities(double dt);
  /**
   * @brief Sends all the staged changes in the simulation back to the UI
   *
   * @param returnValue
   */
  void UpdateSimulation(picojson::object &returnValue);

  void SetKey(const std::string& key, int keyCode);

  bool IsKeyDown(const std::string& key);

  iEntity* getEntity(int index) { return entities[0]; }

  int getEntitiesCount() { return entities.size(); }

  double getElapsedTime() { return elapsedTime; }

private:
  /** @brief Helper function that checks if the JSON data has a field 'name'
   * that matchs the input name */
  bool jsonHasName(picojson::object &data, std::string name);
  /** @brief an array to keep track of all the entities in the scene */
  std::vector<iEntity *> entities;
  std::vector<iMovableEntity *> movableEntities;
  double elapsedTime = 0; 
  Camera* camera;
  // Stores current state of key presses
  std::map<std::string,int> keyValue;
};

#endif
