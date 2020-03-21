//
// Created by rainy on 2020/3/20.
//

#ifndef LAB_LAB4_HPP
#define LAB_LAB4_HPP

#endif //LAB_LAB4_HPP

int imgSharpen_Laplacian(Mat &srcImg);

int imgSharpen_Sobel(Mat &srcImg);

int imgCorrection_GammaCorrection(Mat &srcImg, double gamma);

int imgEnhancement_Histogram_Local(Mat &srcImg, int kSize);

int imgEnhancement_Histogram_Global(Mat &srcImg);