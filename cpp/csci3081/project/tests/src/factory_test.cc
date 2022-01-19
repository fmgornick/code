/**
 * @file factory_test.cc
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "composite_entity_factory.h"
#include "picojson.h"
#include "gtest/gtest.h"

// This is an integration test checks to see if our factory pattern correctly
// takes in picojson objects and converts them to an object's member variables
/*******************************************************************************
 * Class Definition
 ******************************************************************************/
/**
 * @brief Integration tests for our composite factory pattern. These tests
 * checks to see if our factory pattern correctly takes in picojson objects and
 * converts them to an object's member variables
 */
class FactoryTest : public ::testing::Test {
public:
  /**
   * @brief Sets up our strings for the picojson parser to turn into picojson
   * objects.  One for each our our objects, and one string for a fake object to
   * see if our factory can catch this.  Also creates a composite entity factory
   * to actually create our objects.
   */
  void SetUp() {
    drone_json =
        "{\"entityId\": 1, \"name\": \"drone\", \"position\": [1.0, 2.0, 3.0], "
        "\"direction\": [4.0, 5.0, 6.0], \"speed\": 7.0, \"charge\": 8.0}";

    robot_json = "{\"entityId\": 2, \"name\": \"robot\", \"position\": "
                 "[9.0, 10.0, 11.0]}";

    hospital_json = "{\"entityId\": 3, \"name\": \"hospital\", \"position\": "
                    "[12.0, 13.0, 14.0]}";

    rechargeStation_json =
        "{\"entityId\": 4, \"name\": \"recharge station\", \"position\": "
        "[15.0, 16.0, 17.0]}";

    fake_json = "{\"entityId\": 5, \"name\": \"fake\", \"position\": "
                "[69.0, 69.0, 69.0]}";

    c = CompositeEntityFactory();
  }

protected:
  /** @brief strings to be parsed by picojson */
  std::string drone_json, robot_json, hospital_json, rechargeStation_json,
      fake_json;
  /** @brief picojson values representing data in their corresponding strings */
  picojson::value drone, robot, hospital, rechargeStation, fake;
  /** @brief composite factory to actually create the objects used by our
   * program */
  CompositeEntityFactory c;
};

/**
 * @brief test for drone factory.  Makes sure our composite entity factory
 * correctly calls the drone factory, and the drone factory initializes the data
 * correctly
 */
TEST_F(FactoryTest, CreateDrone) {
  picojson::parse(drone, drone_json);
  iEntity *drone1Entity = c.CreateEntity(drone.get<picojson::object>(), NULL);
  Drone *drone1 = dynamic_cast<Drone *>(drone1Entity);
  if (!drone1) {
    EXPECT_TRUE(false) << "NOT A DRONE: " << drone1->GetName() << std::endl;
  } else {
    Vector3 pos = Vector3(1.0, 2.0, 3.0);
    Vector3 dir = Vector3(4.0, 5.0, 6.0);
    EXPECT_EQ(drone1->GetID(), 1) << "drone ID is incorrect";
    EXPECT_EQ(drone1->GetName(), "drone") << "drone name is incorrect";
    EXPECT_EQ(*drone1->GetPosition(), pos) << "drone position is incorrect";
    EXPECT_EQ(*drone1->GetDirection(), dir) << "drone direction is incorrect";
    EXPECT_EQ(drone1->GetSpeed(), 7.0) << "drone speed is incorrect";
    EXPECT_EQ(drone1->GetBattery()->GetRemainingCharge(), 8.0)
        << "drone battery life is incorrect";
  }
}

/**
 * @brief test for robot factory.  Makes sure our composite entity factory
 * correctly calls the robot factory, and the robot factory initializes the data
 * correctly
 */
TEST_F(FactoryTest, CreateRobot) {
  picojson::parse(robot, robot_json);
  iEntity *robot1Entity = c.CreateEntity(robot.get<picojson::object>(), NULL);
  Robot *robot1 = dynamic_cast<Robot *>(robot1Entity);
  if (!robot1) {
    EXPECT_TRUE(false) << "NOT A ROBOT: " << robot1->GetName() << std::endl;
  } else {
    Vector3 pos = Vector3(9.0, 10.0, 11.0);
    EXPECT_EQ(robot1->GetID(), 2) << "robot ID is incorrect";
    EXPECT_EQ(robot1->GetName(), "robot") << "robot name is incorrect";
    EXPECT_EQ(*robot1->GetPosition(), pos) << "robot position is incorrect";
  }
}

/**
 * @brief test for hospital factory.  Makes sure our composite entity factory
 * correctly calls the hospital factory, and the hospital factory initializes
 * the data correctly
 */
TEST_F(FactoryTest, CreateHospital) {
  picojson::parse(hospital, hospital_json);
  iEntity *hospital1Entity =
      c.CreateEntity(hospital.get<picojson::object>(), NULL);
  Hospital *hospital1 = dynamic_cast<Hospital *>(hospital1Entity);
  if (!hospital1) {
    EXPECT_TRUE(false) << "NOT A HOSPITAL: " << hospital1->GetName()
                       << std::endl;
  } else {
    Vector3 pos = Vector3(12.0, 13.0, 14.0);
    EXPECT_EQ(hospital1->GetID(), 3) << "hospital ID is incorrect";
    EXPECT_EQ(hospital1->GetName(), "hospital") << "hospital name is incorrect";
    EXPECT_EQ(*hospital1->GetPosition(), pos)
        << "hospital position is incorrect";
  }
}

/**
 * @brief test for recharge station factory.  Makes sure our composite entity
 * factory correctly calls the recharge station factory, and the recharge
 * station factory initializes the data correctly
 */
TEST_F(FactoryTest, CreateRechargeStation) {
  picojson::parse(rechargeStation, rechargeStation_json);
  iEntity *rechargeStation1Entity =
      c.CreateEntity(rechargeStation.get<picojson::object>(), NULL);
  RechargeStation *rechargeStation1 =
      dynamic_cast<RechargeStation *>(rechargeStation1Entity);
  if (!rechargeStation1) {
    EXPECT_TRUE(false) << "NOT A RECHARGE STATION: "
                       << rechargeStation1->GetName() << std::endl;
  } else {
    Vector3 pos = Vector3(15.0, 16.0, 17.0);
    EXPECT_EQ(rechargeStation1->GetID(), 4)
        << "recharge station ID is incorrect";
    EXPECT_EQ(rechargeStation1->GetName(), "recharge station")
        << "recharge station name is incorrect";
    EXPECT_EQ(*rechargeStation1->GetPosition(), pos)
        << "recharge station position is incorrect";
  }
}

/**
 * @brief test to see that if our picojson object has a name that's not
 * recognized, the composite entity factory will just return a null pointer for
 * the object
 */
TEST_F(FactoryTest, CreateFake) {
  picojson::parse(fake, fake_json);
  iEntity *fake1Entity = c.CreateEntity(fake.get<picojson::object>(), NULL);
  Drone *fake1 = dynamic_cast<Drone *>(fake1Entity);
  if (fake1) {
    EXPECT_TRUE(false) << "NOT A ROBOT: " << fake1->GetName() << std::endl;
  }
}
