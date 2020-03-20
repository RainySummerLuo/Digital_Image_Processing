//
// Created by rainy on 2020/3/20.
//

#include "io.hpp"
#include "lab4.hpp"

int imgSharpen_Laplacian(Mat &srcImg) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    cvtColor(srcImg, srcImg, COLOR_RGB2GRAY);
    Mat outImg = imgCreate(srcImg, 1);
    int kernel_size = 3;
    float kernel[3][3] = {0.f, 1.f, 0.f, 1.f, -4.f, 1.f, 0.f, 1.f, 0.f};
    //float kernel[3][3] = {1.f, 1.f, 1.f, 1.f, -8.f, 1.f, 1.f, 1.f, 1.f};
    //float kernel[3][3] = {0.f, -1.f, 0.f, -1.f, 4.f, -1.f, 0.f, -1.f, 0.f};
    //float kernel[3][3] = {-1.f, 1.f, -1.f, 1.f, 8.f, -1.f, -1.f, 1.f, -1.f};
    for (int i = 0; i < srcRows; ++i) {
        for (int j = 0; j < srcCols; ++j) {
            float sum = 0.f;
            for (int m = i - 1; m <= i + 1; m++) {
                for (int n = j - 1; n <= j + 1; n++) {
                    if (m >= 0 && n >= 0 && m < srcRows && n < srcCols) {
                        auto &srcPixel = srcImg.at<uchar>(m, n);
                        sum += (float) srcPixel * kernel[n - j + 1][m - i + 1];
                    }
                }
            }
            int srcPixel = srcImg.at<uchar>(i, j);
            auto &pixelOut = outImg.at<uchar>(i, j);
            pixelOut = pixelSaturation((float) srcPixel - sum);
        }
    }
    imgShow("Image Sharpen", outImg);
    return 0;
}

int ImgSharpen_Sobel(Mat &srcImg) {
    return 0;
}

int ImgCorrection_GammaCorrection(Mat &srcImg, int gamma) {
    return 0;
}

int imgEnhancement_Histogram_Local(Mat &srcImg) {
    return 0;
}

int imgEnhancement_Histogram_Global(Mat &srcImg) {
    return 0;
}