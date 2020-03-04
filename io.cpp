//
// Created by rainy on 2020/3/4.
//

#include "io.h"

#include <opencv2/opencv.hpp>

using namespace cv;

Mat imgRead(char *filename) {
    Mat image = imread(filename);
    return image;
}
