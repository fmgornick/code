/**
 * @file camera.h
 */
#ifndef CAMERA_H_
#define CAMERA_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <fstream>
#include "camera_controller.h"
#include "find_robot.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @ingroup simulation
 * @brief The camera class. This class can be attached to any entity and act as
 * a camera. When attached to the web app observer, it can receive pictures from
 * the simulation and process the contents of them and return CameraResults.
 *  
 */
class Camera : public ICameraObserver {
public:
    /**
     * @brief The struct that holds all the information for the camera results once,
     * image processing is completed.
     * 
     */
    struct CameraResult : public ICameraResult {
        bool found;
        double pos[3];
    };

    /**
     * @brief Construct a new Camera object. Sets the observer, and initializes
     * the find robot class.
     * 
     * @param cameraId 
     * @param controller 
     */
    Camera(int cameraId, ICameraController* controller) : id(id), controller(controller) {
        if(controller)
            controller->AddObserver(*this);
        findRobot = new FindRobot();
        robot = false;
        robotLocation = Vector3();
    }

    /**
     * @brief This is the function that tell the simulation that this camera would like a new
     * picture for image processing.
     * 
     */
    void TakePicture();

    /**
     * @brief After the simulation takes a photo, it adds to a thread safe queue that this function
     * reads from and can run image processing functionality on the given image.
     * 
     * @param cameraId 
     * @param xPos 
     * @param yPos 
     * @param zPos 
     * @param images 
     * @param details 
     * @return ICameraResult* 
     */
    ICameraResult* ProcessImages(int cameraId, double xPos, double yPos, double zPos, 
    const std::vector<RawCameraImage>& images, picojson::object& details) const;

    /**
     * @brief This allows other threads to view the results of the last processed
     * image.
     * 
     * @param result 
     */
    void ImageProcessingComplete(ICameraResult* result);
    /**
     * @brief Returns if the camera sees the robot
     * 
     * @return true 
     * @return false 
     */
    bool isFound();
    /**
     * @brief Get the Robot Location object
     * 
     * @return Vector3 
     */
    Vector3 getRobotLocation();

private:
    /** @brief The camera controller that takes photos, usually the web app. */
    ICameraController* controller;
    /** @brief The find robot class that can actually run image processing on the images. */
    FindRobot* findRobot;
    /** @brief The id of the camera, corresponds to the id of the entity it's attached to. */
    int id;
    /**@brief Has the camera seen the robot yet */
    bool robot;
    /**@brief Gets the robot location */
    Vector3 robotLocation;
};

#endif