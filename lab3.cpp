//
// Created by rainy on 2020/3/16.
//

#include "io.hpp"
#include "lab3.hpp"

int imgTranslation(Mat &srcImg, int dx, int dy) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    Mat outImg = imgCreate(srcImg, 1);
    for (int i = 0; i < srcRows; ++i) {
        for (int j = 0; j < srcCols; ++j) {
            auto &pixelOut = outImg.at<Vec3b>(i, j);
            if (j - dx < 0 || i - dy < 0) {
                pixelOut = 0;
            } else {
                pixelOut = srcImg.at<Vec3b>(i - dy, j - dx);
            }
        }
    }
    imgShow("Image Translation", outImg);
    imgSave(outImg, "ImageTranslation");
    return 0;
}

int imgRotation(Mat &srcImg, double angle) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    double anglePi = angle * CV_PI / 180;
    double cosA = cos(anglePi);
    double sinA = sin(anglePi);
    int srcCtrCols = srcCols / 2;
    int srcCtrRows = srcRows / 2;
    int DstX1 = (int) floor(-1 * srcCtrCols * cosA - srcCtrRows * sinA + 0.5);
    int DstY1 = (int) floor(-1 * srcCtrCols * sinA + srcCtrRows * cosA + 0.5);
    int DstX2 = (int) floor(srcCtrCols * cosA - srcCtrRows * sinA + 0.5);
    int DstY2 = (int) floor(srcCtrCols * sinA + srcCtrRows * cosA + 0.5);
    int DstX3 = (int) floor(-1 * srcCtrCols * cosA - -1 * srcCtrRows * sinA + 0.5);
    int DstY3 = (int) floor(-1 * srcCtrCols * sinA + -1 * srcCtrRows * cosA + 0.5);
    int DstX4 = (int) floor(srcCtrCols * cosA - -1 * srcCtrRows * sinA + 0.5);
    int DstY4 = (int) floor(srcCtrCols * sinA + -1 * srcCtrRows * cosA + 0.5);
    int outRows = max(abs(DstX1 - DstX4), abs(DstX2 - DstX3)) + 1;
    int outCols = max(abs(DstY1 - DstY4), abs(DstY2 - DstY3)) + 1;
    Mat outImg = imgCreate(srcImg, outCols, outRows);
    int srcX = 0;
    int srcY = 0;
    for (int i = 0; i < outRows; ++i) {
        for (int j = 0; j < outCols; ++j) {
            srcX = (int) ((i - (double) outRows / 2) * cosA - (j - (double) outCols / 2) * sinA);
            srcY = (int) ((i - (double) outRows / 2) * sinA + (j - (double) outCols / 2) * cosA);
            srcX += srcCtrRows;
            srcY += srcCtrCols;
            auto &pixelOut = outImg.at<Vec3b>(i, j);
            if (srcX > srcRows || srcY > srcCols || srcX < 0 || srcY < 0) {
                pixelOut = 0;
            } else {
                pixelOut = srcImg.at<Vec3b>(srcX, srcY);
            }
        }
    }
    imgShow("Image Rotation", outImg);
    imgSave(outImg, "ImageRotation_45");
    return 0;
}

int imgShear_x(Mat &srcImg, double ratio) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    int outRows = srcRows;
    int outCols = 0;
    double tanA = tan(ratio);
    outCols = (int) round(srcCols + srcRows / tanA);
    Mat outImg = imgCreate(srcImg, outCols, outRows);
    for (int i = 0; i < outRows; i++) {
        for (int j = 0; j < outCols; j++) {
            auto &pixelOut = outImg.at<Vec3b>(i, j);
            int shiftX = (int) round((outRows - i) / tanA);
            if (j < shiftX || j > shiftX + srcCols) {
                pixelOut = 0;
            } else {
                pixelOut = srcImg.at<Vec3b>(i, (int) round(j - shiftX));
            }
        }
    }
    imgShow("Image Shear", outImg);
    imgSave(outImg, "ImageShear_X");
    return 0;
}

int imgShear_y(Mat &srcImg, double ratio) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    int outRows = 0;
    int outCols = srcCols;
    double tanA = tan(ratio);
    outRows = (int) round(srcRows + srcCols / tanA);
    Mat outImg = imgCreate(srcImg, outCols, outRows);
    for (int i = 0; i < outRows; i++) {
        for (int j = 0; j < outCols; j++) {
            auto &pixelOut = outImg.at<Vec3b>(i, j);
            int shiftY = (int) round((outCols - j) / tanA);
            if (i < shiftY || i > shiftY + srcCols) {
                pixelOut = 0;
            } else {
                pixelOut = srcImg.at<Vec3b>((int) round(i - shiftY), j);
            }
        }
    }
    imgShow("Image Shear", outImg);
    imgSave(outImg, "ImageShear_Y");
    return 0;
}

int smoothing_3x3_averaging(Mat &srcImg) {
    return 0;
}

int smoothing_3x3_median(Mat &srcImg) {
    return 0;
}

int smoothing_3x3_binarization(Mat &srcImg) {
    return 0;
}

int smoothing_5x5_averaging(Mat &srcImg) {
    return 0;
}

int smoothing_5x5_median(Mat &srcImg) {
    return 0;
}

int smoothing_5x5_binarization(Mat &srcImg) {
    return 0;
}