#pragma once
#include <opencv2/opencv.hpp>

/**
 * Entry point
 * Gets from command line [input file path] [output file path] [width] [height] [number of images]
 */
int main(int argc, char** argv);

/**
 * Creates 3 channel Mat object from values array
 */
cv::Mat createImageMat(char* values);