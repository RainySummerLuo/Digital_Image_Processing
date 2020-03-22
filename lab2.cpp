#include "io.hpp"

int imgReduce_alternative_line(Mat &srcImg, double reduceN) {
    Mat outImg = imgCreate(srcImg, reduceN);
    for (size_t imgOutRow = 0; imgOutRow < outImg.rows; ++imgOutRow) {
        for (size_t imgOutCol = 0; imgOutCol < outImg.cols; ++imgOutCol) {
            int imgSrcRow = (int) cvRound(imgOutRow / reduceN);
            int imgSrcCol = (int) cvRound(imgOutCol / reduceN);
            auto &srcPixel = srcImg.at<Vec3b>(imgSrcRow, imgSrcCol);
            auto &outPixel = outImg.at<Vec3b>(imgOutRow, imgOutCol);
            outPixel = srcPixel;
        }
    }
    imgShow("Lena Image - Reduce", outImg);
    imgSave("ImageReduce_alternative_line", outImg);
    return 0;
}

int imgReduce_fractional_linear_reduction(Mat &srcImg, double reduceN) {
    Mat outImg = imgCreate(srcImg, reduceN);
    for (size_t imgOutRow = 0; imgOutRow < outImg.rows; ++imgOutRow) {
        for (size_t imgOutCol = 0; imgOutCol < outImg.cols; ++imgOutCol) {
            int x = imgOutCol;
            int y = imgOutRow;
            double xp = (double) x / reduceN;
            double yp = (double) y / reduceN;
            int xp_r = (int) floor(xp);
            int yp_r = (int) floor(yp);
            int x1 = xp_r;
            int x2 = xp_r + 1;
            int y1 = yp_r;
            int y2 = yp_r + 1;
            auto &q11 = srcImg.at<Vec3b>(x1, y1);
            auto &q22 = srcImg.at<Vec3b>(x2, y2);
            double q11_pixel = sqrt(pow(xp - x1, 2) + pow(yp - y1, 2));
            double q22_pixel = sqrt(pow(xp - x2, 2) + pow(yp - y2, 2));
            double linearRatio_q11 = q11_pixel / sqrt(2);
            double linearRatio_q22 = q22_pixel / sqrt(2);
            auto &outPixel = outImg.at<Vec3b>(x, y);
            for (int i = 0; i < 3; ++i) {
                outPixel[i] = pixelSaturation(q11[i] * linearRatio_q11 + q22[i] * linearRatio_q22);
            }
        }
    }
    imgShow("Lena Image - Reduce", outImg);
    imgSave("ImageReduce_fractional_linear_reduction", outImg);
    return 0;
}

int imgEnlarge_pixel_replication(Mat &srcImg, double enlargeN) {
    Mat outImg = imgCreate(srcImg, enlargeN);
    for (size_t imgOutRow = 0; imgOutRow < outImg.rows; ++imgOutRow) {
        for (size_t imgOutCol = 0; imgOutCol < outImg.cols; ++imgOutCol) {
            int imgSrcRow = (int) (imgOutRow / enlargeN);
            int imgSrcCol = (int) (imgOutCol / enlargeN);
            auto &srcPixel = srcImg.at<Vec3b>(imgSrcRow, imgSrcCol);
            auto &outPixel = outImg.at<Vec3b>(imgOutRow, imgOutCol);
            outPixel = srcPixel;
        }
    }
    imgShow("Lena Image - Enlargement", outImg);
    imgSave("ImageEnlarge_pixel_replication", outImg);
    return 0;
}

int imgEnlarge_nearest_neighbor_interpolation(Mat &srcImg, double enlargeN) {
    Mat outImg = imgCreate(srcImg, enlargeN);
    for (size_t imgOutRow = 0; imgOutRow < outImg.rows; ++imgOutRow) {
        for (size_t imgOutCol = 0; imgOutCol < outImg.cols; ++imgOutCol) {
            double xp = imgOutRow / enlargeN;
            double yp = imgOutCol / enlargeN;
            int x1 = (int) cvRound(xp);
            int y1 = (int) cvRound(yp);
            int x = 0;
            int y = 0;
            if (abs(x1 - xp) > 0.5) {
                x = (int) ceil(xp);
            } else {
                x = (int) floor(xp);
            }
            if (abs(y1 - yp) > 0.5) {
                y = (int) ceil(yp);
            } else {
                y = (int) floor(yp);
            }
            auto &srcPixel = srcImg.at<Vec3b>(x, y);
            auto &outPixel = outImg.at<Vec3b>(imgOutRow, imgOutCol);
            outPixel = srcPixel;
        }
    }
    imgShow("Lena Image - Enlargement", outImg);
    imgSave("ImageEnlarge_nearest_neighbor_interpolation", outImg);
    return 0;
}

int imgEnlarge_bilinear_interpolation(Mat &srcImg, double enlargeN) {
    Mat outImg = imgCreate(srcImg, enlargeN);
    for (size_t imgOutRow = 0; imgOutRow < outImg.rows; ++imgOutRow) {
        for (size_t imgOutCol = 0; imgOutCol < outImg.cols; ++imgOutCol) {
            int x = imgOutCol;
            int y = imgOutRow;
            double xp = (double) x / enlargeN;
            double yp = (double) y / enlargeN;
            int xp_r = (int) floor(xp);
            int yp_r = (int) floor(yp);
            int x1 = xp_r;
            int x2 = xp_r + 1;
            int y1 = yp_r;
            int y2 = yp_r + 1;
            auto &q11 = srcImg.at<Vec3b>(x1, y1);
            auto &q21 = srcImg.at<Vec3b>(x2, y1);
            auto &q12 = srcImg.at<Vec3b>(x1, y2);
            auto &q22 = srcImg.at<Vec3b>(x2, y2);
            double p_0 =
                    q11[0] * (x2 - xp) * (y2 - yp) + q12[0] * (x2 - xp) * (yp - y1) + q21[0] * (xp - x1) * (y2 - yp) +
                    q22[0] * (xp - x1) * (yp - y1);
            double p_1 =
                    q11[1] * (x2 - xp) * (y2 - yp) + q12[1] * (x2 - xp) * (yp - y1) + q21[1] * (xp - x1) * (y2 - yp) +
                    q22[1] * (xp - x1) * (yp - y1);
            double p_2 =
                    q11[2] * (x2 - xp) * (y2 - yp) + q12[2] * (x2 - xp) * (yp - y1) + q21[2] * (xp - x1) * (y2 - yp) +
                    q22[2] * (xp - x1) * (yp - y1);
            auto &outPixel = outImg.at<Vec3b>(x, y);
            outPixel[0] = pixelSaturation(p_0);
            outPixel[1] = pixelSaturation(p_1);
            outPixel[2] = pixelSaturation(p_2);
        }
    }
    imgShow("Lena Image - Enlargement", outImg);
    imgSave("ImageEnlarge_bilinear_interpolation", outImg);
    return 0;
}

int imgEnlarge_bicubic_interpolation(Mat &srcImg, double enlargeN) {
    Mat outImg = imgCreate(srcImg, enlargeN);
    for (size_t imgOutRow = 0; imgOutRow < outImg.rows; ++imgOutRow) {
        for (size_t imgOutCol = 0; imgOutCol < outImg.cols; ++imgOutCol) {
            int x = imgOutCol;
            int y = imgOutRow;
            double xp = (double) x / enlargeN;
            double yp = (double) y / enlargeN;
            int xp_r = (int) floor(xp);
            int yp_r = (int) floor(yp);
            double matA[4];
            double sw_x[4];
            sw_x[0] = 1 + (xp - xp_r);
            sw_x[1] = xp - xp_r;
            sw_x[2] = 1 - (xp - xp_r);
            sw_x[3] = 2 - (xp - xp_r);
            matA[0] = bicubic_sw(sw_x[0]);
            matA[1] = bicubic_sw(sw_x[1]);
            matA[2] = bicubic_sw(sw_x[2]);
            matA[3] = bicubic_sw(sw_x[3]);
            double matC[4];
            double sw_y[4];
            sw_y[0] = 1 + (yp - yp_r);
            sw_y[1] = yp - yp_r;
            sw_y[2] = 1 - (yp - yp_r);
            sw_y[3] = 2 - (yp - yp_r);
            matC[0] = bicubic_sw(sw_y[0]);
            matC[1] = bicubic_sw(sw_y[1]);
            matC[2] = bicubic_sw(sw_y[2]);
            matC[3] = bicubic_sw(sw_y[3]);
            auto &outPixel = outImg.at<Vec3b>(x, y);
            for (int k = 0; k < 3; ++k) {
                double result = 0;
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        auto &srcPixel = srcImg.at<Vec3b>(xp_r + i - 1, yp_r + j - 1);
                        double wx = matA[i];
                        double wy = matC[j];
                        result += wx * wy * srcPixel[k];
                    }
                }
                outPixel[k] = pixelSaturation(result);
            }
        }
    }
    imgShow("Lena Image - Enlargement", outImg);
    imgSave("ImageEnlarge_bicubic_interpolation", outImg);
    return 0;
}

int imgEnlarge_fractional_linear_expansion(Mat &srcImg, double enlargeN) {
    Mat outImg = imgCreate(srcImg, enlargeN);
    for (size_t imgOutRow = 0; imgOutRow < outImg.rows; ++imgOutRow) {
        for (size_t imgOutCol = 0; imgOutCol < outImg.cols; ++imgOutCol) {
            int x = imgOutCol;
            int y = imgOutRow;
            double xp = (double) x / enlargeN;
            double yp = (double) y / enlargeN;
            int xp_r = (int) floor(xp);
            int yp_r = (int) floor(yp);
            int x1 = xp_r;
            int x2 = xp_r + 1;
            int y1 = yp_r;
            int y2 = yp_r + 1;
            if (x2 == outImg.rows - 1) {
                x2 = xp_r;
            }
            if (y2 == outImg.cols - 1) {
                y2 = yp_r;
            }
            auto &q11 = srcImg.at<Vec3b>(x1, y1);
            auto &q22 = srcImg.at<Vec3b>(x2, y2);
            double q11_pixel = sqrt(pow(xp - x1, 2) + pow(yp - y1, 2));
            double q22_pixel = sqrt(pow(xp - x2, 2) + pow(yp - y2, 2));
            double linearRatio_q11 = q11_pixel / sqrt(2);
            double linearRatio_q22 = q22_pixel / sqrt(2);
            auto &outPixel = outImg.at<Vec3b>(x, y);
            for (int i = 0; i < 3; ++i) {
                outPixel[i] = pixelSaturation(q11[i] * linearRatio_q11 + q22[i] * linearRatio_q22);
            }
        }
    }
    imgShow("Lena Image - Enlargement", outImg);
    imgSave("ImageEnlarge_fractional_linear_expansion", outImg);
    return 0;
}

int imgNegative(Mat &srcImg) {
    Mat outImg = srcImg.clone();
    if (outImg.channels() == 3) {
        // if it's color image
        for (size_t row = 0; row < outImg.rows; ++row) {
            for (size_t col = 0; col < outImg.cols; ++col) {
                auto &pixel = outImg.at<Vec3b>(row, col);
                for (int i = 0; i < 3; ++i) {
                    pixel[i] = pixelSaturation(255 - (int) pixel[i]);
                }
            }
        }
    } else if (outImg.channels() == 1) {
        // if it's gray image
        for (size_t row = 0; row < outImg.rows; ++row) {
            for (size_t col = 0; col < outImg.cols; ++col) {
                auto &pixel = outImg.at<Vec3b>(row, col);
                pixel[0] = 255 - (int) pixel[0];
            }
        }
    }
    imgShow("Lena Image - Negative", outImg);
    imgSave("ImageNegative", outImg);
    return 0;
}