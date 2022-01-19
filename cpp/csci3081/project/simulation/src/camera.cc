#include "camera.h"
#include "stb_image.h"
#include "stb_image_write.h"

void Camera::TakePicture() {
  if (controller)
    controller->TakePicture(id);
}

ICameraResult *Camera::ProcessImages(int cameraId, double xPos, double yPos,
                                     double zPos,
                                     const std::vector<RawCameraImage> &images,
                                     picojson::object &details) const {
  if (cameraId == id || cameraId < 0) {
    // These will output the image to files.  Ultimately this is just for
    // debugging:
    std::ofstream colorFile("data/images/color.jpg",
                            std::ios::out | std::ios::binary);
    colorFile.write(reinterpret_cast<const char *>(images[0].data),
                    images[0].length);
    std::ofstream depthFile("data/images/depth.jpg",
                            std::ios::out | std::ios::binary);
    depthFile.write(reinterpret_cast<const char *>(images[1].data),
                    images[1].length);

    // Use the following to convert color and depth images to RGBA image from
    // memory (inside your image class / perhaps with a new constructor):
    // std::cout << "Creating new images" << std::endl;
    int width, height, components;
    unsigned char *rgbBuffer = stbi_load_from_memory(
        (const unsigned char *)images[0].data, images[0].length, &width,
        &height, &components, 4);
    unsigned char *depthBuffer = stbi_load_from_memory(
        (const unsigned char *)images[1].data, images[1].length, &width,
        &height, &components, 4);
    components = 4;

    Image *rgb = new Image(rgbBuffer, width, height);
    Image *depth = new Image(depthBuffer, width, height);
    Vector3 *pos = new Vector3(xPos, yPos, zPos);

    // std::cout << "Calling find robot take picture" << std::endl;
    findRobot->TakePicture(pos, rgb, depth);

    // Generate the result of image processing.  This could include images using
    // the Result class.
    CameraResult *result = new CameraResult();
    int x, y;
    if (result->found = findRobot->CanSeeRobot(x, y)) {
      Vector3 pos = findRobot->GetRobotLocation(x, y);
      std::cout << "[Camera] - We found the robot (" << pos.GetX() << ","
                << pos.GetY() << "," << pos.GetZ() << ")" << std::endl;
      result->pos[0] = pos.GetX();
      result->pos[1] = pos.GetY();
      result->pos[2] = pos.GetZ();
    }

    // std::cout << "Image Processed" << std::endl;
    // delete rgb;
    // delete depth;
    delete pos;
    return result;
  } else {
    return NULL;
  }
}

void Camera::ImageProcessingComplete(ICameraResult *result) {
  CameraResult &res = *static_cast<CameraResult *>(result);
  robot = res.found;
  robotLocation = Vector3(res.pos[0], res.pos[1], res.pos[2]);
  if (res.found)
    std::cout << "[Camera] - We found the robot (" << robotLocation.GetX()
              << "," << robotLocation.GetY() << "," << robotLocation.GetZ()
              << ")" << std::endl;
  delete result;
}

bool Camera::isFound() { return robot; }
Vector3 Camera::getRobotLocation() { return robotLocation; }
