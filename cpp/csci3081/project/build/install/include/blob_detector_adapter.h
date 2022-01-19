/**
 * @file blob_detector_adapter.h
 * @author Jason Woitalla
 * @brief An adapter class for OpenCV. This class extends Filter.
 * It uses OpenCV's blob detection algorithm, but hides the complexity
 * of converting an 'Image' object into a cv::Mat object. It is then
 * able to run the blob detection algorithm.
 *
 */
#ifndef BLOB_DETECTOR_ADAPTER_H_
#define BLOB_DETECTOR_ADAPTER_H_

#include "filter.h"
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>

/**
 * @ingroup image
 * @brief The BlobDetectorAdapter class that interfaces the Filter and OpenCV. This class scans an image
 * for the orange drone using contours and morphing. If found, the drone data is stored in the pixel
 * in the top left corner.
 * 
 */
class BlobDetectorAdapater : public Filter {
public:
  /**
   * @brief Construct a new Blob Detector Adapater object
   *
   */
  BlobDetectorAdapater();

  /**
   * @brief The overwritten apply function from Filter.
   * Converts the original imges to cv::Mat and then runs
   * OpenCV blob detection.
   *
   * @param original
   * @param filtered
   */
  void Apply(std::vector<Image *> original, std::vector<Image *> filtered);

  cv::Mat *GetHsvThresholdOutput();
  std::vector<std::vector<cv::Point>> *GetFindContoursOutput();
  std::vector<std::vector<cv::Point>> *GetFilterContoursOutput();

private:
  cv::Mat getMat(Image *image);
  void setImage(cv::Mat mat, Image *image);

  cv::Mat hsvThresholdOutput;
  std::vector<std::vector<cv::Point>> findContoursOutput;
  std::vector<std::vector<cv::Point>> filterContoursOutput;

  void hsvThreshold(cv::Mat &, double[], double[], double[], cv::Mat &);
  void findContours(cv::Mat &, bool, std::vector<std::vector<cv::Point>> &);
  void filterContours(cv::Mat &, std::vector<std::vector<cv::Point>> &, double,
                      double, double, double, double, double, double[], double,
                      double, double, double,
                      std::vector<std::vector<cv::Point>> &);
};

#endif
