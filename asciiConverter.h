#ifndef ASCII_CONVERTER_H
#define ASCII_CONVERTER_H
#include <opencv2/opencv.hpp>

float luminosity(int red, int green, int blue);
char getSobelEdge(const cv::Mat &img, int i, int j, float threshold);
void printImage(const cv::Mat &img);
#endif