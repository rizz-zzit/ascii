#ifndef ASCII_CONVERTER_H
#define ASCII_CONVERTER_H
#include <opencv2/opencv.hpp>

float luminosity(int red, int green, int blue);
void printImage(const cv::Mat &img);
#endif