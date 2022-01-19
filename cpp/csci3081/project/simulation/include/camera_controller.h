#ifndef ICAMERA_CONTROLLER_H_
#define ICAMERA_CONTROLLER_H_
#include "picojson.h"
#include <vector>
#include "picojson.h"

/// The result returned from the image processing
class ICameraResult {
public:
    /// destructor
    virtual ~ICameraResult() {}
};

/// A raw camera image stored in jpg format (data) and length is an int
struct RawCameraImage {
    const unsigned char* data;
    int length;
};

/// A Camera Observer monitors results from all cameras.  It will process the pictures returned asynchronously and act on results.
class ICameraObserver {
public:
    /// Destructor
    virtual ~ICameraObserver() {}
    /// Processes images asynchronously after a picture has been taken.  This method will pass in the camera position and the raw images stored in jpg format.
    /// Do all your image processing here so that it does not slow down your simulation.  The result will be passed to the ImageProcessingComplete(...) method.
    virtual ICameraResult* ProcessImages(int cameraId, double xPos, double yPos, double zPos, const std::vector<RawCameraImage>& images, picojson::object& details) const = 0;
    /// After the asynchronous image processing is done, this method is called to synchronize the results with the simulation update loop.
    virtual void ImageProcessingComplete(ICameraResult* result) = 0;
};

/// The Camera Controller class controls and allows for monitoring of all cameras.
class ICameraController {
public:
    /// Destructor
    virtual ~ICameraController() {}
    /// To take a picture with a specific camera, pass in the camera id.
    virtual void TakePicture(int cameraId) = 0;
    /// Adds a camera observer to monitor cameras
    virtual void AddObserver(ICameraObserver& observer) = 0;
    /// Removes a camera observer.
    virtual void RemoveObserver(ICameraObserver& observer) = 0;
};

#endif
