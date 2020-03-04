#include "io.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

Mat imgRead(char *filename) {
    Mat image = imread(filename);
    return image;
}
