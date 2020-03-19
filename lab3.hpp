//
// Created by rainy on 2020/3/16.
//

#ifndef LAB_LAB3_HPP
#define LAB_LAB3_HPP

#endif //LAB_LAB3_HPP

int imgTranslation(Mat &srcImg, int dx, int dy);

int imgRotation(Mat &srcImg, double degree);

int imgShear_x(Mat &srcImg, double ratio);

int imgShear_y(Mat &srcImg, double ratio);

int smoothing_3x3_averaging(Mat &srcImg);

int smoothing_3x3_median(Mat &srcImg);

int smoothing_3x3_binarization(Mat &srcImg);

int smoothing_5x5_averaging(Mat &srcImg);

int smoothing_5x5_median(Mat &srcImg);

int smoothing_5x5_binarization(Mat &srcImg);