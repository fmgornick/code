#include "gtest/gtest.h"
#include "composite_entity_factory.h"
#include "picojson.h"
#include "simulation_facade.h"
#include "camera_controller.h"

class RegressionTest : public ::testing::Test {
public: 
    void SetUp() {
        drone_json =
        "{\"entityId\": 1, \"name\": \"drone\", \"position\": [1.0, 2.0, 3.0], "
        "\"direction\": [4.0, 5.0, 6.0], \"speed\": 7.0, \"charge\": 8.0}";
        facade = SimulationFacade();
        pos = new Vector3;
        vel = new Vector3;
        dir = new Vector3;
        drone = new Drone(1, "Drone", pos, vel, dir, 7, nullptr, nullptr);
        drone->SetMovementStartegy(
          new BeelineMovement(*drone->GetPosition(), Vector3(-110, 2, 63), drone->GetSpeed()));
    }   
protected:
    std::string drone_json;
    picojson::value droneValue;
    SimulationFacade facade;

    Drone *drone;
    Vector3 *pos, *vel, *dir;
};

//Regression Test
TEST_F(RegressionTest, EntityCreationTest) {
    picojson::parse(droneValue, drone_json);
    ICameraController* temp = nullptr;
    facade.CreateEntityCmd(droneValue.get<picojson::object>(), *temp);

    EXPECT_EQ(facade.getEntitiesCount(), 1) << "The drone entity did not get added to the entities list.";

    Drone *drone1 = dynamic_cast<Drone *>(facade.getEntity(0));
    EXPECT_TRUE(drone1) << "No drone was setup, the entity is not a drone.";
}

//Regression Test
TEST_F(RegressionTest, SimulationUpdateTest) {
    facade.UpdateEntities(0.1);
    EXPECT_EQ(facade.getElapsedTime(), 0.1) << "Update did not happend correclty";
}


