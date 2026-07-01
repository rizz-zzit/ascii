#include "image.h"
#include <opencv2/opencv.hpp>
#include <algorithm>

cv::Mat readImage(std::string path) {
    cv::Mat image = cv::imread(path);
    return image;
}

cv::Mat resizeImageForTerminal(const cv::Mat &original, int maxDimension) {
    if (original.empty()) return original;

    cv::Mat stepped;
    cv::resize(original, stepped, cv::Size(0, 0), 1.0, 0.5, cv::INTER_LINEAR);

    int width  = stepped.cols;
    int height = stepped.rows;

    if (height <= maxDimension && width <= maxDimension) {
        return stepped;
    }

    double scale = static_cast<double>(maxDimension) / std::max(height, width);

    cv::Mat output;
    cv::resize(stepped, output, cv::Size(0, 0), scale, scale, cv::INTER_AREA);

    return output;
}
