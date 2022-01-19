#include "blob_detector_adapter.h"

BlobDetectorAdapater::BlobDetectorAdapater() {}

void BlobDetectorAdapater::Apply(std::vector<Image *> original, std::vector<Image *> filtered) {
    for(int i = 0; i < original.size(); i++) {
        cv::Mat im = getMat(original[i]);
        
        /**
         * The following code was generated using the GRIP pipeline generator. This generator
         * easily creates OpenCV pipeline code to quickley view what the output of an OpenCV
         * pipeline will be. 
         * More information on GRIP: https://github.com/WPIRoboticsProjects/GRIP/releases/tag/v1.5.2 
         * 
         */

        //Step RGB_THRESHOLD:
        cv::Mat hsvThresholdInput = im;
	    //double hsvThresholdHue[] = {94.0, 180.0};
	    //double hsvThresholdSaturation[] = {150.0, 255.0};
	    //double hsvThresholdValue[] = {140.0, 255.0};

        double hsvThresholdHue[] = {5.0, 25.0};
	    double hsvThresholdSaturation[] = {180.0, 255.0};
	    double hsvThresholdValue[] = {130.0, 255.0};
        hsvThreshold(hsvThresholdInput, hsvThresholdHue, hsvThresholdSaturation, hsvThresholdValue, this->hsvThresholdOutput);

        //Step DIALATE
        cv::Mat dialateInput = hsvThresholdOutput;
        cv::Mat dialateOutput;
        cv::dilate(dialateInput, dialateOutput, cv::Mat(), cv::Point(-1,-1), 2);

        //Step FIND_CONTOURS
        cv::Mat findContoursInput = dialateOutput;
	    bool findContoursExternalOnly = true;  // default Boolean
	    findContours(findContoursInput, findContoursExternalOnly, this->findContoursOutput);

        //std::cout << "Found Contours: " << findContoursOutput.size() << std::endl;

        //Step FILTER_CONTOURS
        std::vector<std::vector<cv::Point> > filterContoursContours = findContoursOutput;
        double filterContoursMinArea = 30.0;  // default Double
        double filterContoursMinPerimeter = 0;  // default Double
        double filterContoursMinWidth = 0;  // default Double
        double filterContoursMaxWidth = 1000;  // default Double
        double filterContoursMinHeight = 0;  // default Double
        double filterContoursMaxHeight = 1000;  // default Double
        double filterContoursSolidity[] = {0.0, 100.0};
        double filterContoursMaxVertices = 1000000;  // default Double
        double filterContoursMinVertices = 0;  // default Double
        double filterContoursMinRatio = 0.0;  // default Double
        double filterContoursMaxRatio = 1000;  // default Double
        filterContours(findContoursInput, filterContoursContours, filterContoursMinArea, filterContoursMinPerimeter, filterContoursMinWidth, filterContoursMaxWidth, filterContoursMinHeight, filterContoursMaxHeight, filterContoursSolidity, filterContoursMaxVertices, filterContoursMinVertices, filterContoursMinRatio, filterContoursMaxRatio, this->filterContoursOutput);

        /**
         * This is the end of the GRIP generatored code
         * 
         */

        //std::cout << "Filtered Contours: " << filterContoursOutput.size() << std::endl;
        
        cv::Mat morph;
        cv::morphologyEx(findContoursInput, morph, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(51,51)));

        //std::cout << "Morphed Polygon" << std::endl;
        std::vector<std::vector<cv::Point> > morphContoursOutput;
        findContours(morph, true, morphContoursOutput);

        //std::cout << "Second batch of contours: " << morphContoursOutput.size() << std::endl;
        cv::Mat contourImage;
        cv::cvtColor(dialateOutput, contourImage, cv::COLOR_GRAY2BGR);
        
        std::vector<cv::Rect> contourRects;
        for(std::vector<cv::Point> contour : morphContoursOutput) {
            cv::Rect rect;
            rect = cv::boundingRect(contour);
            contourRects.push_back(rect);
            //std::cout << "Rect Area: " << rect.area()  << ", aspect ratio " << aspectRatio << std::endl;
            cv::rectangle(contourImage, rect.tl(), rect.br(), cv::Scalar(0,255,0),1);
        }

        cv::Mat output;
        cv::cvtColor(contourImage, output, cv::COLOR_BGR2RGBA);
        setImage(output, filtered[0]);

        int foundRobot = 0;
        float x = 0, y = 0;
        for(int i = 0; i < contourRects.size(); i++) {
            float pixelCount = 0;
            for(int x = contourRects[i].x; x < contourRects[i].br().x; x++) {
                for(int y = contourRects[i].y; y < contourRects[i].br().y; y++) {
                    Color white;
                    filtered[0]->GetPixel(x, y, white);
                    //std::cout << "Got White Pixel: (" << white.getR() << "," << white.getG() << "," << white.getB() << ")" << std::endl;
                    if(white.getR() == 1 && white.getG() == 1 && white.getB() == 1)
                        pixelCount += 1;
                }
            }
            float ratio = pixelCount/contourRects[i].area();
            float aspectRatio = (float)contourRects[i].width/(float)contourRects[i].height;
            if(ratio >= 0.5f && aspectRatio >= 0.75 && aspectRatio < 0.9) {
                foundRobot = 1;
                x = contourRects[i].x + (contourRects[i].width/2);
                y = contourRects[i].y + (contourRects[i].height/2);
                std::cout << "[Blob Detect] - Rect: (" << contourRects[i].x << ", " << contourRects[i].y << ", " << contourRects[i].width << ", " << contourRects[i].height << ")" << std::endl;
            }
        }
        Color info(foundRobot, x/filtered[0]->GetWidth(), y/filtered[0]->GetHeight());
        filtered[0]->SetPixel(0, 0, info);
    }
}

cv::Mat BlobDetectorAdapater::getMat(Image* image) {
    cv::Mat temp(image->GetHeight(), image->GetWidth(), CV_8UC4, image->GetData());
    cv::Mat output;
    cv::cvtColor(temp, output, cv::COLOR_RGBA2BGR);
    return output;
}

void BlobDetectorAdapater::setImage(cv::Mat mat, Image* image) {
    *image = Image(mat.data, mat.cols, mat.rows);
}

/**
 * The following is GRIP generatored helper functions
 * 
 */

/**
 * @brief This method is a generated getter for the output of a RGB_Threshold.
 * @return Mat output from RGB_Threshold.
 */
cv::Mat* BlobDetectorAdapater::GetHsvThresholdOutput(){
	return &(this->hsvThresholdOutput);
}
/**
 * @brief This method is a generated getter for the output of a Find_Contours.
 * @return ContoursReport output from Find_Contours.
 */
std::vector<std::vector<cv::Point> >* BlobDetectorAdapater::GetFindContoursOutput(){
	return &(this->findContoursOutput);
}
/**
 * @brief This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* BlobDetectorAdapater::GetFilterContoursOutput(){
	return &(this->filterContoursOutput);
}

/**
 * @brief Segment an image based on color ranges.
 *
 * @param input The image on which to perform the RGB threshold.
 * @param red The min and max red.
 * @param green The min and max green.
 * @param blue The min and max blue.
 * @param output The image in which to store the output.
 */
void BlobDetectorAdapater::hsvThreshold(cv::Mat &input, double hue[], double saturation[], double value[], cv::Mat &output) {
    cv::Mat hsvImage;
    cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);
    //cv::Vec3b pixel = hsvImage.at<cv::Vec3b>(hsvImage.size().width/2,hsvImage.size().height/2);
    //int h = hsvImage.at<cv::Vec3b>(hsvImage.size().width/2,hsvImage.size().height/2)[0];
    //int s = hsvImage.at<cv::Vec3b>(hsvImage.size().width/2,hsvImage.size().height/2)[1];
    //int v = hsvImage.at<cv::Vec3b>(hsvImage.size().width/2,hsvImage.size().height/2)[2];
    //cv::Vec3b pixel = hsvImage.at<cv::Vec3b>(0, 0);
    //std::cout << "Center pixel: " << h << ", " << s << ", " << v << std::endl;
    cv::inRange(hsvImage, cv::Scalar(hue[0], saturation[0], value[0]), cv::Scalar(hue[1], saturation[1], value[1]), output);
}

/**
 * @brief Finds contours in an image.
 *
 * @param input The image to find contours in.
 * @param externalOnly if only external contours are to be found.
 * @param contours vector of contours to put contours in.
 */
void BlobDetectorAdapater::findContours(cv::Mat &input, bool externalOnly, std::vector<std::vector<cv::Point> > &contours) {
    std::vector<cv::Vec4i> hierarchy;
    contours.clear();
    int mode = externalOnly ? cv::RETR_TREE : cv::RETR_LIST;
    int method = cv::CHAIN_APPROX_SIMPLE;
    cv::findContours(input, contours, hierarchy, mode, method);
}


/**
 * @brief Filters through contours.
 * @param inputContours is the input vector of contours.
 * @param minArea is the minimum area of a contour that will be kept.
 * @param minPerimeter is the minimum perimeter of a contour that will be kept.
 * @param minWidth minimum width of a contour.
 * @param maxWidth maximum width.
 * @param minHeight minimum height.
 * @param maxHeight  maximum height.
 * @param solidity the minimum and maximum solidity of a contour.
 * @param minVertexCount minimum vertex Count of the contours.
 * @param maxVertexCount maximum vertex Count.
 * @param minRatio minimum ratio of width to height.
 * @param maxRatio maximum ratio of width to height.
 * @param output vector of filtered contours.
 */
void BlobDetectorAdapater::filterContours(cv::Mat &thresh, std::vector<std::vector<cv::Point> > &inputContours, double minArea, double minPerimeter, double minWidth, double maxWidth, double minHeight, double maxHeight, double solidity[], double maxVertexCount, double minVertexCount, double minRatio, double maxRatio, std::vector<std::vector<cv::Point> > &output) {
    std::vector<cv::Point> hull;
    output.clear();
    for (std::vector<cv::Point> contour: inputContours) {
        //cv::Rect bb = boundingRect(contour);
        //if (bb.width < minWidth || bb.width > maxWidth) continue;
        //if (bb.height < minHeight || bb.height > maxHeight) continue;
        double area = cv::contourArea(contour);
        //std::cout << "Contour Points:" << contour.size() << ", Contour Area: " << area << std::endl;
        if (area < minArea) {
            std::vector<std::vector<cv::Point> > cntPoints;
            cntPoints.push_back(contour);
            cv::fillPoly(thresh, cntPoints, cv::Scalar(0,0,0));
            continue;
        }
        //if (arcLength(contour, true) < minPerimeter) continue;
        //cv::convexHull(cv::Mat(contour, true), hull);
        //double solid = 100 * area / cv::contourArea(hull);
        //if (solid < solidity[0] || solid > solidity[1]) continue;
        //if (contour.size() < minVertexCount || contour.size() > maxVertexCount)	continue;
        //double ratio = (double) bb.width / (double) bb.height;
        //if (ratio < minRatio || ratio > maxRatio) continue;
        output.push_back(contour);
    }
}
