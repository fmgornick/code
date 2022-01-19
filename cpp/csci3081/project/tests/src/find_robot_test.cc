#include "find_robot.h"
#include "image_processing_facade.h"
#include "math.h"
#include "gtest/gtest.h"

class FindRobotTest : public ::testing::Test {
public:
  void SetUp() {
    findRobot = FindRobot();
    robot =
        new Image("/home/user/repo/project/tests/data/images/robot-test.png");
    depth = new Image(
        "/home/user/repo/project/tests/data/images/robot-test-depth.png");
    blob = new Image(
        "/home/user/repo/project/tests/data/images/robot-test-blob.png");
    cameraPos = Vector3(0, 0, 0);
  }

protected:
  Image *robot, *depth, *blob;
  Vector3 cameraPos;
  ImageProcessingFacade facade;
  FindRobot findRobot;
};

// UNIT TEST
TEST_F(FindRobotTest, CanSeeRobotTest) {
  findRobot.SetBlobImage(blob);

  int x, y;
  testing::internal::CaptureStdout();
  EXPECT_EQ(findRobot.CanSeeRobot(x, y), true)
      << "Find Robot did not return true when a robot is seen";
  testing::internal::GetCapturedStdout();

  int xRange = abs(x - 252);
  int yRange = abs(y - 254);

  EXPECT_TRUE(xRange <= 5)
      << "X result did not get within range, wrong robot found";
  EXPECT_TRUE(yRange <= 5)
      << "Y result did not get within range, wrong robot found";
}

// UNIT TEST
TEST_F(FindRobotTest, TakePictureTest) {
  // Take photo of a robot, the function should print this to the console:
  //[Find Robot] - Robot Found!
  testing::internal::CaptureStdout();
  findRobot.TakePicture(&cameraPos, robot, depth);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(output.find("[Find Robot] - Robot Found!"))
      << "TakePicture, fails to print when a robot is found. Finding a robot "
         "might not be working";
}

// UNIT TEST
TEST_F(FindRobotTest, GetRobotLocationTest) {
  int robotX = 252;
  int robotY = 254;
  testing::internal::CaptureStdout();
  Vector3 output = findRobot.GetRobotLocation(robotX, robotY);
  testing::internal::GetCapturedStdout();
  Vector3 location(-9.75, -11.65, -0.69);

  float distance = sqrt(pow(abs(output.GetX() - location.GetX()), 2) +
                        pow(abs(output.GetY() - location.GetY()), 2) +
                        pow(abs(output.GetZ() - location.GetZ()), 2));

  EXPECT_TRUE(distance <= 1)
      << "The robot's location was not close enough to expected location.";
}
