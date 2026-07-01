#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <string>

// Default value is set here
cv::Mat readImage(std::string path);
cv::Mat resizeImageForTerminal(const cv::Mat &original, int maxDimension = 350);

#endif
