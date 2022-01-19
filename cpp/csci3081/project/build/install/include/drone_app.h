#ifndef DRONE_APP_H_
#define DRONE_APP_H_

#include "WebServer.h"
#include "drone.h"
#include <chrono>
#include <map>

// Web application for displaying a drone
class DroneApp : public JSONSession {
public:
  // Default constructor
  DroneApp() : start(std::chrono::system_clock::now()), time(0.0) {}
  // Destructor
  ~DroneApp() {}

  // Receives JSON from the web server
  void receiveJSON(picojson::value &val);
  // Handles specific commands from the web server
  void ReceiveCommand(const std::string &cmd, picojson::object &data,
                      picojson::object &returnValue);
  // Handles the update command
  void Update(double dt, picojson::object &returnValue);
  // Handles the key up command
  void KeyUp(const std::string &key, int keyCode);
  // Handles the key down command
  void KeyDown(const std::string &key, int keyCode);
  // Returns whether or not a key is pressed at any time
  bool IsKeyDown(const std::string &key);

private:
  std::chrono::time_point<std::chrono::system_clock> start;
  double time;
  Drone drone;
  std::map<std::string, int> keyValue;
};

#endif // !DRONE_APP_H_
