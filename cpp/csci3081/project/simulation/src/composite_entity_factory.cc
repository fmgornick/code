#include "composite_entity_factory.h"

CompositeEntityFactory::CompositeEntityFactory() {
  factories.push_back(new DroneFactory);
  factories.push_back(new RobotFactory);
  factories.push_back(new HospitalFactory);
  factories.push_back(new RechargeStationFactory);
}

void CompositeEntityFactory::AddFactory(iEntityFactory *factory) {
  factories.push_back(factory);
}

iEntity *CompositeEntityFactory::CreateEntity(picojson::object &entity,
                                              Camera *camera) {
  for (auto &&x : factories) {
    iEntity *newEntity = x->CreateEntity(entity, camera);
    if (newEntity)
      return newEntity;
  }
  return NULL;
}
