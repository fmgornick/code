#ifndef WEB_APP_H_
#define WEB_APP_H_

#include <map>
#include "WebServer.h"
#include "camera_controller.h"
#include "simulation_facade.h"
#include "camera.h"
#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

/// A Web Application Sever that communicates with a web page through web sockets.
class WebApp : public JSONSession, ICameraController{
public:
    /// Initializes server
    WebApp();
    /// Destructor
    virtual ~WebApp();

    // *******************************************
    // Methods used for simulation (edit these):
    // *******************************************

    /// Creates an entity based on JSON data stored as an object.
    void CreateEntity(picojson::object& entityData, ICameraController& cameraController);
    /// Updates the simulation.  This may be called multiple times per frame.
    void Update(double dt);
    /// Called after all updating is done.  Entity should be returned to the UI.
    void FinishUpdate(picojson::object& returnValue);

    // *******************************************
    // Methods used for web page communication:
    // (You shouldn't need to touch these)
    // *******************************************

    /// Receives JSON from the web server
    void receiveJSON(picojson::value& val);
    /// Handles specific commands from the web server
    void ReceiveCommand(const std::string& cmd, picojson::object& data, picojson::object& returnValue);
    /// Handles the key up command
    void KeyUp(const std::string& key, int keyCode);
    /// Handles the key down command
    void KeyDown(const std::string& key, int keyCode);
    /// Returns whether or not a key is pressed at any time
    bool IsKeyDown(const std::string& key);
    /// Takes picture for a specific camera
    void TakePicture(int cameraId);
    /// Adds camera observers to the application
    void AddObserver(ICameraObserver& observer);
    /// Removes camera observers from the application
    void RemoveObserver(ICameraObserver& observer);
    /// Method that handles asynchronous image processing that runs on a separate thread
    void ProcessImageQueue();


    

private:
    
    /** @brief The simulation facade variable */
    SimulationFacade simulation;
    // Used for tracking time since last update
    std::chrono::time_point<std::chrono::system_clock> start;
    // The total time the server has been running.
    double time;
    // Camera observers
    std::vector<ICameraObserver*> cameraObservers;
    // Image processing queue used for processing pictures that were taken
    std::queue<picojson::object> imageQueue;
    // Thread that handles asynchronous processing
    std::thread *imageProcessThread;
    // For synchronizing with the image queue
    std::mutex imageProcessMutex;
    // For synchronizing with the commands and update
    std::mutex updateMutex;
    // Condition variable that is used to notify thread of new images
    std::condition_variable imageProcessCond;
    // Stores whether the application is running or not.
    bool running;
};


#endif
