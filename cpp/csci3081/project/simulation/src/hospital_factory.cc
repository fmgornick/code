#include "hospital_factory.h"

iEntity *HospitalFactory::CreateEntity(picojson::object &entity,
                                       Camera *camera) {
  if (entity["name"].get<std::string>() == "hospital") {
    int id = (int)entity["entityId"].get<double>();
    std::string name = entity["name"].get<std::string>();

    picojson::array &pos_arr = entity["position"].get<picojson::array>();
    Vector3 *pos =
        new Vector3(pos_arr[0].get<double>(), pos_arr[1].get<double>(),
                    pos_arr[2].get<double>());

    return new Hospital(id, name, pos);
  }
  return NULL;
}
