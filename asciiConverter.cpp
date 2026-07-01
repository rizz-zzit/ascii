#include "asciiConverter.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>

float luminosity(int red, int green, int blue){
    float mod = std::sqrt(red*red+green*green+blue*blue);
    float magicNum = 441.67295655; //sqrt(3)*255
    return mod/magicNum;
}
void printImage(const cv::Mat &img){
    int width = img.cols, height =  img.rows;
    std::string asciiChars = " .-=+*x#$&X@";
    for(int i = 0; i<height; i++){
        for(int j = 0; j<width; j++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
            int blue  = pixel[0];
            int green = pixel[1];
            int red   = pixel[2];
            //float between 0.0 and 1.0
            float cd = luminosity(red,green,blue);
            //convert to an int between 0 and len(asciiChars)-1
            int length = asciiChars.size();
            int index = static_cast<int>(length*cd);
            index = std::min(index,length-1);
            std::cout << "\033[38;2;" << red << ";" << green << ";" << blue << "m";
            std::cout << asciiChars[index];
        }
        std::cout << "\033[0m" << std::endl;
    }
}