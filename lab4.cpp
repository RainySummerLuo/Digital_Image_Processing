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
    imgSave("ImageSharpen_Laplacian", outImg);
    return 0;
}

int imgSharpen_Sobel(Mat &srcImg) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    cvtColor(srcImg, srcImg, COLOR_RGB2GRAY);
    Mat outImg = imgCreate(srcImg, 1);
    int kernel_gx[3][3] = {{-1, 0, 1},
                           {-2, 0, 2},
                           {-1, 0, 1}};
    int kernel_gy[3][3] = {{1,  2,  1},
                           {0,  0,  0},
                           {-1, -2, -1}};
    for (int i = 1; i < srcRows; i++) {
        for (int j = 1; j < srcCols; j++) {
            auto &pixelOut = outImg.at<uchar>(i, j);
            int gx = 0;
            int gy = 0;
            for (int l = i - 1; l <= i + 1; l++) {
                for (int k = j - 1; k <= j + 1; k++) {
                    if (l >= 0 && k >= 0 && l < srcRows && k < srcCols) {
                        auto &srcPixel = srcImg.at<uchar>(l, k);
                        gx += srcPixel * kernel_gx[l - i + 1][k - j + 1];
                        gy += srcPixel * kernel_gy[l - i + 1][k - j + 1];
                    }
                }
            }
            //pixelOut = sqrt(pow(gx, 2) + pow(gy, 2));
            pixelOut = pixelSaturation(srcImg.at<uchar>(i, j) - sqrt(pow(gx, 2) + pow(gy, 2)));
        }
    }
    imgShow("Image Sharpen", outImg);
    imgSave("ImageSharpen_Sobel", outImg);
    return 0;
}

int imgCorrection_GammaCorrection(Mat &srcImg, double gamma) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    cvtColor(srcImg, srcImg, COLOR_RGB2GRAY);
    Mat outImg = imgCreate(srcImg, 1);
    for (int i = 1; i < srcRows; i++) {
        for (int j = 1; j < srcCols; j++) {
            auto &pixelOut = outImg.at<uchar>(i, j);
            pixelOut = pixelSaturation(pow((double) (srcImg.at<uchar>(i, j) / 255.0), gamma) * 255.0f);
        }
    }
    imgShow("Image Gamma Correction", outImg);
    imgSave("ImageGammaCorrection", outImg);
    return 0;
}

int imgEnhancement_Histogram_Local(Mat &srcImg, int kSize) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    cvtColor(srcImg, srcImg, COLOR_RGB2GRAY);
    Mat outImg = imgCreate(srcImg);
    int kSize_half = kSize / 2;
    for (int row = kSize_half; row < srcRows - (srcRows % kSize_half); row += kSize_half) {
        for (int col = kSize_half; col < srcCols - (srcCols % kSize_half); col += kSize_half) {
            int n = kSize * kSize;
            int hist[256] = {0};
            double hist_prob[256] = {0};
            double hist_dist[256] = {0};
            for (int i = row - kSize_half; i < row + kSize_half; i++) {
                for (int j = col - kSize_half; j < col + kSize_half; j++) {
                    auto &pixelSrc = srcImg.at<uchar>(i, j);
                    hist[pixelSrc] += 1;
                }
            }
            for (int i = 0; i < 256; i++) {
                hist_prob[i] = (double)hist[i] / n;
            }
            for (int i = 0; i < 256; i++) {
                if (i == 0) {
                    hist_dist[i] = hist_prob[i];
                } else {
                    hist_dist[i] = hist_dist[i - 1] + hist_prob[i];
                }
            }
            for (int i = row - kSize_half; i < row + kSize_half; i++) {
                for (int j = col - kSize_half; j < col + kSize_half; j++) {
                    auto &pixelOut = outImg.at<uchar>(i, j);
                    auto &pixelSrc = srcImg.at<uchar>(i, j);
                    pixelOut = pixelSaturation(hist_dist[pixelSrc] * 256);
                }
            }
        }
    }
    imgShow("Image Histogram Local", outImg);
    imgSave("ImageHistogram_Local", outImg);
    return 0;
}

int imgEnhancement_Histogram_Global(Mat &srcImg) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    int n = srcCols * srcRows;
    cvtColor(srcImg, srcImg, COLOR_RGB2GRAY);
    Mat outImg = imgCreate(srcImg);
    int hist[256] = {0};
    double hist_prob[256] = {0};
    double hist_dist[256] = {0};
    for (int i = 0; i < srcRows; i++) {
        for (int j = 0; j < srcCols; j++) {
            auto &pixelSrc = srcImg.at<uchar>(i, j);
            hist[pixelSrc] += 1;
        }
    }
    for (int i = 0; i < 256; i++) {
        hist_prob[i] = (double)hist[i] / n;
    }
    for (int i = 0; i < 256; i++) {
        if (i == 0) {
            hist_dist[i] = hist_prob[i];
        } else {
            hist_dist[i] = hist_dist[i - 1] + hist_prob[i];
        }
    }
    for (int i = 0; i < srcRows; i++) {
        for (int j = 0; j < srcCols; j++) {
            auto &pixelOut = outImg.at<uchar>(i, j);
            auto &pixelSrc = srcImg.at<uchar>(i, j);
            pixelOut = pixelSaturation(hist_dist[pixelSrc] * 256);
        }
    }
    imgShow("Image Histogram Global", outImg);
    imgSave("ImageHistogram_Global", outImg);
    return 0;
}