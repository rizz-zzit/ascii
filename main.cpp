#include "image.h"
#include "asciiConverter.h"
#include <iostream>
#include <string>
int main() {
    std::string pathToImage = "./test_images/spiderman_test.PNG";
    cv::Mat srcImg = readImage(pathToImage);
    cv::Mat normalisedImg = resizeImageForTerminal(srcImg);
    printImage(normalisedImg);
    return 0;
}
