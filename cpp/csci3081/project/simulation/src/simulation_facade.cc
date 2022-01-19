#include "simulation_facade.h"
#include "composite_entity_factory.h"

#include <iostream>
#include <memory>

SimulationFacade::SimulationFacade() { camera = nullptr; }

void SimulationFacade::CreateEntityCmd(picojson::object &entityData,
                                       ICameraController &cameraController) {
  camera = nullptr;
  if (entityData["name"].get<std::string>() == "drone") {
    camera = new Camera(0, &cameraController);
  }
  /*
  std::cout << "create a " << entityData["name"].get<std::string>() << std::endl;
  for (picojson::value::object::const_iterator i = entityData.begin();
     i != entityData.end();
     ++i) {
  std::cout << i->first << ": " << i->second.to_str() << std::endl;
  }*/
  
  CompositeEntityFactory *cf = new CompositeEntityFactory;
  iEntity *entity = cf->CreateEntity(entityData, camera);

  /*if(entityData["name"].get<std::string>() == "rescue drone") {
    for (iMovableEntity *movable : movableEntities) {
      Drone* drone = dynamic_cast<Drone*>(movable);
      if(drone) {
        Drone* rescueDrone = dynamic_cast<Drone*>(entity);
        drone->SetRescueDrone(rescueDrone);
      }
    }
  }*/

  iMovableEntity* movable = dynamic_cast<iMovableEntity *>(entity);
  if(movable)
    movableEntities.push_back(movable);
  else
    entities.push_back(entity);
}

void SimulationFacade::AddEntity(iEntity *entity) {
  entities.push_back(entity);
}

void SimulationFacade::UpdateEntities(double dt) {
  elapsedTime += dt;
  for (iMovableEntity *x : movableEntities) {
    x->Update(dt);

    if (std::fmod(elapsedTime, 1.0) < 0.01)
        LoggerManager::GetInstance()->Log(x->GetPosition(),
                                          x->GetDirection(), elapsedTime);

    //iMovableEntity *movable = dynamic_cast<iMovableEntity *>(x);
    //Drone *movable = dynamic_cast<Drone *>(x);
    //if (movable) {
      //movable->Update(dt);
      //**************************************************************************
      //TODO DELETE
      /*movable->SetKeyboard(
        IsKeyDown("ArrowRight") ? 1 : (IsKeyDown("ArrowLeft") ? -1 : 0),
        IsKeyDown("w") ? 1 : (IsKeyDown("s") ? -1 : 0),
        IsKeyDown("ArrowUp") ? -1 : (IsKeyDown("ArrowDown") ? 1 : 0),
        IsKeyDown("a") ? 1 : (IsKeyDown("d") ? -1 : 0)
      );*/
      //**************************************************************************

    //}
  }
}

void SimulationFacade::UpdateSimulation(picojson::object &returnValue) {
  for (iMovableEntity *movable : movableEntities) {
     picojson::object entity;

      entity["entityId"] = picojson::value((double)movable->GetID());
      entity["name"] = picojson::value(movable->GetName());

      Vector3 *pos = movable->GetPosition();
      Vector3 *dir = movable->GetDirection();

      picojson::array posArr;

      posArr.push_back(picojson::value((double)pos->GetX()));
      posArr.push_back(picojson::value((double)pos->GetY()));
      posArr.push_back(picojson::value((double)pos->GetZ()));

      entity["pos"] = picojson::value(posArr);

      picojson::array dirArr;
      dirArr.push_back(picojson::value((double)dir->GetX()));
      dirArr.push_back(picojson::value((double)dir->GetY()));
      dirArr.push_back(picojson::value((double)dir->GetZ()));

      entity["dir"] = picojson::value(dirArr);

      returnValue["entity" + std::to_string(movable->GetID())] =
          picojson::value(entity);
  }
}

void SimulationFacade::SetKey(const std::string& key, int keyCode) {
  keyValue[key] = keyCode;
}

bool SimulationFacade::IsKeyDown(const std::string& key) {
  std::map<std::string,int>::iterator it = keyValue.find(key);
    if (it != keyValue.end()) {
        return it->second;
    }
  
  return false;
}

bool SimulationFacade::jsonHasName(picojson::object &data, std::string name) {
  return data["name"].get<std::string>() == name;
}
