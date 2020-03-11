#include "io.hpp"

#ifndef LAB_LAB2_HPP
#define LAB_LAB2_HPP

int imgReduce_alternative_line(Mat &srcImg, double reduceN);

int imgReduce_fractional_linear_reduction(Mat &srcImg, double reduceN);

int imgEnlarge_pixel_replication(Mat &srcImg, double enlargeN);

int imgEnlarge_nearest_neighbor_interpolation(Mat &srcImg, double enlargeN);

int imgEnlarge_bilinear_interpolation(Mat &srcImg, double enlargeN);

int imgEnlarge_bicubic_interpolation(Mat &srcImg, double enlargeN);

int imgEnlarge_fractional_linear_expansion(Mat &srcImg, double enlargeN);

int imgNegative(Mat &srcImg);

#endif //LAB_LAB2_HPP
