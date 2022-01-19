/** @file find_robot.h */
#ifndef FIND_ROBOT_H
#define FIND_ROBOT_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "image_processing_facade.h"
#include "vector3.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @ingroup simulation
 * @brief This class takes in an image and using the image processing facade
 * runs the logic on images to see if the robot is found.
 *
 */
class FindRobot {
public:
  /**
   * @brief Construct a new Find Robot object.
   *
   */
  FindRobot() {
    imageProcessor = new ImageProcessingFacade();
    this->blobImage = new Image();
    this->cannyImage = new Image();
  }

  /**
   * @brief Receives and image from the simulation, and runs the image
   * processing facade on them.
   *
   * @param cameraPosition
   * @param rgb
   * @param depth
   */
  void TakePicture(Vector3 *cameraPosition, Image *rgb, Image *depth) {
    if (foundRobot)
      return;

    cameraPos = *cameraPosition;
    lastImage = rgb;
    depthImage = depth;

    imageProcessor->BlobDetect(rgb, this->blobImage);

    Color data;
    blobImage->GetPixel(0, 0, data);
    if (data.getR() == 1) {
      foundRobot = true;
      std::cout << "[Find Robot] - Robot Found!" << std::endl;
      blobImage->SaveAs("data/images/blob.png");
      rgb->SaveAs("data/images/blob-color.png");
      depth->SaveAs("data/images/blob-depth.png");
    }
  }

  /**
   * @brief This is the function that does all the logic work, it takes the
   * processesd images and returns true of false if the robot is inside the
   * images. It then returns the X and Y coordinates of where the robot is
   * in the image. This information is stored in the top left pixel of the
   * blob image. The format is (<1 or 0, can see>, <robot X>, <robot Y>).
   *
   * @param outX
   * @param outY
   * @return true
   * @return false
   */
  bool CanSeeRobot(int &outX, int &outY) {
    Color data;
    blobImage->GetPixel(0, 0, data);

    outX = data.getG() * blobImage->GetWidth();
    outY = data.getB() * blobImage->GetHeight();
    if (data.getR() == 1)
      std::cout << "[Find Robot] - Robot at (" << outX << ", " << outY << ")"
                << std::endl;
    return data.getR() == 1;
  }

  /**
   * @brief Get the Robot Location object, from the X and Y coordinates from
   * CanSeeRobot. This function requires the depth image be updated
   *
   * @param x
   * @param y
   * @return Vector3
   */
  Vector3 GetRobotLocation(int x, int y) {
    Vector3 location;

    std::cout << "[Find robot] - Camera Pos: (" << cameraPos.GetX() << ", "
              << cameraPos.GetY() << ", " << cameraPos.GetZ() << ")"
              << std::endl;
    Color info;
    depthImage->GetPixel(x, y, info);

    Vector3 rgb(info.getR(), info.getG(), info.getB());
    Vector3 dirVector = (rgb - Vector3(0.5, 0.5, 0.5)) * 2.0;
    float distance = (1.0 - dirVector.GetMagnitude()) * 50.0;

    return cameraPos + (dirVector.Normalize() * distance);
  }

  /** @brief Sets the blob image */
  void SetBlobImage(Image *blob) { blobImage = blob; }
  /** @brief Sets the depth image */
  void SetDepthImage(Image *depth) { depthImage = depth; }

private:
  /** @brief The image processing facade class */
  ImageProcessingFacade *imageProcessor;

  /** @brief The position of the camera when the images were taken */
  Vector3 cameraPos;
  /** @brief The last rgb image taken from the camera */
  Image *lastImage;
  /** @brief The last depth image taken from the camera */
  Image *depthImage;
  /** @brief This is the blob image from OpenCV */
  Image *blobImage;
  /** @brief This is the canny edge detect image from ImageProcessor */
  Image *cannyImage;
  /** @brief Is the robot found */
  bool foundRobot = false;
};

#endif
