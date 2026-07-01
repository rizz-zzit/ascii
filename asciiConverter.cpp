#include "asciiConverter.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

float luminosity(int red, int green, int blue){
    float mod = std::sqrt(red*red + green*green + blue*blue);
    float magicNum = 441.67295655f; // sqrt(3)*255
    return mod / magicNum;
}

// Sobel Edge Detection Function
// Returns the ASCII character representing the edge direction, or ' ' if no edge is detected.
char getSobelEdge(const cv::Mat &img, int i, int j, float threshold) {
    // 1. Define Sobel kernels
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    float sumX = 0.0f;
    float sumY = 0.0f;

    // 2. Perform 3x3 convolution
    for(int k = -1; k <= 1; k++) {
        for(int l = -1; l <= 1; l++) {
            cv::Vec3b neighbor = img.at<cv::Vec3b>(i + k, j + l);
            float intensity = luminosity(neighbor[2], neighbor[1], neighbor[0]) * 255.0f;

            sumX += intensity * Gx[k + 1][l + 1];
            sumY += intensity * Gy[k + 1][l + 1];
        }
    }

    // 3. Calculate magnitude
    float magnitude = std::sqrt(sumX * sumX + sumY * sumY);

    // 4. Determine edge character based on direction
    if (magnitude > threshold) {
        float angle = std::atan2(sumY, sumX); 
        float angleDeg = angle * 180.0f / M_PI;
        if (angleDeg < 0) angleDeg += 180.0f;

        if ((angleDeg >= 0 && angleDeg < 22.5) || (angleDeg >= 157.5 && angleDeg <= 180)) {
            return '|';  // Vertical edge
        } else if (angleDeg >= 22.5 && angleDeg < 67.5) {
            return '/';  // Diagonal edge
        } else if (angleDeg >= 67.5 && angleDeg < 112.5) {
            return '-';  // Horizontal edge
        } else if (angleDeg >= 112.5 && angleDeg < 157.5) {
            return '\\'; // Diagonal edge
        }
    }

    return ' '; // No edge found
}

void printImage(const cv::Mat &img){
    int width = img.cols, height = img.rows;
    std::string asciiChars = " .-=+*x#$&X@";
    float edgeThreshold = 350.0f; 

    // Skip the 1-pixel border to prevent out-of-bounds sampling in Sobel
    for(int i = 1; i < height - 1; i++){
        for(int j = 1; j < width - 1; j++){
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
            int blue  = pixel[0];
            int green = pixel[1];
            int red   = pixel[2];

            // Check if this pixel is a structural edge
            char asciiToPrint = getSobelEdge(img, i, j, edgeThreshold);

            // Fallback: If not an edge, use your original luminosity shading logic
            if (asciiToPrint == ' ') {
                float cd = luminosity(red, green, blue);
                int length = asciiChars.size();
                int index = static_cast<int>(length * cd);
                index = std::min(index, length - 1);
                asciiToPrint = asciiChars[index];
            }

            std::cout << "\033[38;2;" << red << ";" << green << ";" << blue << "m" << asciiToPrint;
        }
        std::cout << "\033[0m" << std::endl;
    }
}