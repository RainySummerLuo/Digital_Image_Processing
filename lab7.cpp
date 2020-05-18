//
// Created by rainy on 2020/5/2.
//

#include "io.hpp"
#include "lab7.hpp"

using namespace std;
using namespace cv;

int imgNoiseReduction(Mat &src) {
    int srcCols = src.cols;
    int srcRows = src.rows;
    Mat srcImg = Mat(srcRows, srcCols, CV_8U, Scalar(0));
    convertRGB2GRAY(src, srcImg);
    //int ksize = 3;

    Mat dstImg_ArithMean = Mat(srcRows, srcCols, CV_8U, Scalar(0));
    //blur(srcImg, dstImg_ArithMean, Size(ksize, ksize));
    imgArithmeticMean(srcImg, dstImg_ArithMean);
    imgShow("Image Arithmetic Mean", dstImg_ArithMean);
    imgSave("imgArithmeticMean", dstImg_ArithMean);

    Mat dstImg_GeoMean = Mat(srcRows, srcCols, CV_8U, Scalar(0));
    imgGeometricMean(srcImg, dstImg_GeoMean);
    imgShow("Image Geometry Mean", dstImg_GeoMean);
    imgSave("imgGeometryMean", dstImg_GeoMean);

    Mat dstImg_MedMean = Mat(srcRows, srcCols, CV_8U, Scalar(0));
    //medianBlur(srcImg, dstImg_MedMean, ksize);
    imgMedianFilter(srcImg, dstImg_MedMean);
    imgShow("Image Median Mean", dstImg_MedMean);
    imgSave("imgMedianMean", dstImg_MedMean);

    Mat dstImg_AlpTrmMean = Mat(srcRows, srcCols, CV_8U, Scalar(0));
    imgAlphaTrimmedMeanFilter(srcImg, dstImg_AlpTrmMean, 2);
    imgShow("Image Alpha Trimmed Mean", dstImg_AlpTrmMean);
    imgSave("imgAlphaTrimmedMean", dstImg_AlpTrmMean);

    Mat dstImg_AdpMedian = Mat(srcRows, srcCols, CV_8U, Scalar(0));
    imgAdaptiveMedianFilter(srcImg, dstImg_AdpMedian);
    imgShow("Image Adaptive Median", dstImg_AdpMedian);
    imgSave("imgAdaptiveMedian", dstImg_AdpMedian);

    waitKey(0);
    return 0;
}

int imgArithmeticMean(Mat &srcImg, Mat &dstImg) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    for (int i = 0; i < srcRows; i++) {
        for (int j = 0; j < srcCols; j++) {
            if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1) < srcImg.rows && (j + 1) < srcImg.cols) {
                int mean = (srcImg.at<uchar>(i, j) + srcImg.at<uchar>(i - 1, j - 1) +
                            srcImg.at<uchar>(i - 1, j) + srcImg.at<uchar>(i, j - 1) + srcImg.at<uchar>(i - 1, j + 1) +
                            srcImg.at<uchar>(i + 1, j - 1) + srcImg.at<uchar>(i + 1, j + 1) +
                            srcImg.at<uchar>(i, j + 1) +
                            srcImg.at<uchar>(i + 1, j)) / 9;
                dstImg.at<uchar>(i, j) = pixelSaturation(mean);
            } else {
                dstImg.at<uchar>(i, j) = srcImg.at<uchar>(i, j);
            }
        }
    }
    return 0;
}

int imgGeometricMean(Mat &srcImg, Mat &dstImg) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    double power = 1.0 / 9;
    for (int i = 0; i < srcRows; i++) {
        for (int j = 0; j < srcCols; j++) {
            if (i >= 1 && i <= srcRows - 2 && j >= 1 && j <= srcCols - 2) {
                double pointA = 1, pointB = 1, pointC = 1, pointD = 1, pointE = 1, pointF = 1, pointG = 1, pointH = 1, pointI = 1;
                if (srcImg.at<uchar>(i, j) > 0) {
                    pointA = pow((int) srcImg.at<uchar>(i, j), power);
                }
                if (srcImg.at<uchar>(i, j + 1) > 0) {
                    pointB = pow((int) srcImg.at<uchar>(i, j + 1), power);
                }
                if (srcImg.at<uchar>(i, j - 1) > 0) {
                    pointC = pow((int) srcImg.at<uchar>(i, j - 1), power);
                }
                if (srcImg.at<uchar>(i + 1, j) > 0) {
                    pointD = pow((int) srcImg.at<uchar>(i + 1, j), power);
                }
                if (srcImg.at<uchar>(i + 1, j + 1) > 0) {
                    pointE = pow((int) srcImg.at<uchar>(i + 1, j + 1), power);
                }
                if (srcImg.at<uchar>(i + 1, j - 1) > 0) {
                    pointF = pow((int) srcImg.at<uchar>(i + 1, j - 1), power);
                }
                if (srcImg.at<uchar>(i - 1, j) > 0) {
                    pointG = pow((int) srcImg.at<uchar>(i - 1, j), power);
                }
                if (srcImg.at<uchar>(i - 1, j + 1) > 0) {
                    pointH = pow((int) srcImg.at<uchar>(i - 1, j + 1), power);
                }
                if (srcImg.at<uchar>(i - 1, j - 1) > 0) {
                    pointI = pow((int) srcImg.at<uchar>(i - 1, j - 1), power);
                }
                double times = pointA * pointB * pointC * pointD * pointE * pointF * pointG * pointH * pointI;
                dstImg.at<uchar>(i, j) = pixelSaturation(times);
            } else {
                dstImg.at<uchar>(i, j) = srcImg.at<uchar>(i, j);
            }
        }
    }
    return 0;
}

int imgMedianFilter(Mat &srcImg, Mat &dstImg) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    for (int i = 0; i < srcRows; i++) {
        for (int j = 0; j < srcCols; j++) {
            if (i >= 1 && i <= srcRows - 2 && j >= 1 && j <= srcCols - 2) {
                vector<int> nums = vector<int>();
                int median;
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        nums.push_back((int) srcImg.at<uchar>(i + k, j + l));
                    }
                }
                median = findMedian(nums);
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        dstImg.at<uchar>(i + k, j + l) = pixelSaturation(median);
                    }
                }
            } else {
                dstImg.at<uchar>(i, j) = srcImg.at<uchar>(i, j);
            }
        }
    }
    return 0;
}

int imgAlphaTrimmedMeanFilter(Mat &srcImg, Mat &dstImg, int trimSize) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    int tSize = trimSize / 2;
    for (int i = 0; i < srcRows; i++) {
        for (int j = 0; j < srcCols; j++) {
            if (i >= 1 && i <= srcRows - 2 && j >= 1 && j <= srcCols - 2) {
                vector<int> nums = vector<int>();
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        nums.push_back((int) srcImg.at<uchar>(i + k, j + l));
                    }
                }
                int mean = meanVector(nums, tSize);
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        dstImg.at<uchar>(i + k, j + l) = mean;
                    }
                }
            } else {
                dstImg.at<uchar>(i, j) = srcImg.at<uchar>(i, j);
            }
        }
    }
    return 0;
}

int imgAdaptiveMedianFilter(Mat &srcImg, Mat &dstImg) {
    int srcCols = srcImg.cols;
    int srcRows = srcImg.rows;
    int sSize = 3, sMax = 7;
    int hsSize = sSize / 2;
    int result = -1, status = -1;
    while (result == -1) {
        for (int i = 0; i < srcRows; i++) {
            for (int j = 0; j < srcCols; j++) {
                if (i >= hsSize && i < srcRows - hsSize && j >= hsSize && j < srcCols - hsSize) {
                    int srcPixel = (int) srcImg.at<uchar>(i, j);
                    vector<int> nums = vector<int>();
                    for (int k = -hsSize; k <= hsSize; ++k) {
                        for (int l = -hsSize; l <= hsSize; ++l) {
                            nums.push_back((int) srcImg.at<uchar>(i + k, j + l));
                        }
                    }
                    if (status == -1) {
                        result = adfStages(nums, srcPixel);
                    } else {
                        result = findMedian(nums);
                    }
                    for (int k = -hsSize; k <= hsSize; ++k) {
                        for (int l = -hsSize; l <= hsSize; ++l) {
                            dstImg.at<uchar>(i + k, j + l) = result;
                        }
                    }
                } else {
                    dstImg.at<uchar>(i, j) = srcImg.at<uchar>(i, j);
                }
            }
        }
        if (sSize < sMax) {
            sSize += 2;
        } else {
            status = 0;
        }
    }
    return 0;
}

int adfStages(vector<int> &nums, int srcPixel) {
    int median, min, max, a1, a2;
    median = findMedian(nums);
    min = findMin(nums);
    max = findMax(nums);
    a1 = median - min;
    a2 = median - max;
    if (a1 > 0 && a2 < 0) {
        int b1, b2;
        b1 = srcPixel - min;
        b2 = srcPixel - max;
        if (b1 > 0 && b2 < 0) {
            return srcPixel;
        } else {
            return pixelSaturation(median);
        }
    } else {
        return -1;
    }
}
