#include "drone_factory.h"

iEntity *DroneFactory::CreateEntity(picojson::object &entity, Camera *camera) {
  if (entity["name"].get<std::string>() == "drone") {
    int id = (int)entity["entityId"].get<double>();
    std::string name = entity["name"].get<std::string>();

    picojson::array &pos_arr = entity["position"].get<picojson::array>();
    Vector3 *pos =
        new Vector3(pos_arr[0].get<double>(), pos_arr[1].get<double>(),
                    pos_arr[2].get<double>());

    picojson::array &dir_arr = entity["direction"].get<picojson::array>();
    Vector3 *dir =
        new Vector3(dir_arr[0].get<double>(), dir_arr[1].get<double>(),
                    dir_arr[2].get<double>());

    double speed = entity["speed"].get<double>();

    Vector3 *vel = new Vector3(speed, 0, speed);

    double charge = entity["charge"].get<double>();
    bool isEmpty = (charge == 0);
    Battery *b = new Battery(10, charge, isEmpty);

    Drone *drone;
    if(entity["name"].get<std::string>() != "rescue drone") {
      drone = new Drone(id, name, pos, vel, dir, speed, b, camera);
      drone->SetMovementStartegy(
        new BeelineMovement(*pos, Vector3(-110, 2, 63), speed));

      drone->SetSearchStrategy(
          // Only have one of these three uncommented to change the search
          // strategy, iff nullptr is uncommented then patrol strategy takes over
          // new BreadthFirstSearch()
          // new DeapthFirstSearch()
          nullptr);

    } else {
      drone = new Drone(id, name, pos, vel, dir, speed, b, NULL);
    }

    return drone;
  }
  return NULL;
}
