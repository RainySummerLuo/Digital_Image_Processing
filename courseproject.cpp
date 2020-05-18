#include "io.hpp"
#include "courseproject.hpp"

using namespace std;
using namespace cv;

int imgCannyEdge(Mat &srcImg) {
    float threshold1 = 70;
    float threshold2 = 140;
    int apertureSize = 3;

    TickMeter tm;

    Mat dstImg_origin_opencv = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    tm.start();
    cannyEdge_origin_opencv(srcImg, dstImg_origin_opencv, threshold1, threshold2, apertureSize);
    tm.stop();
    cout << "Timing: " << tm.getTimeMilli() << "ms" << endl;

    tm.reset();

    Mat dstImg_origin_custom = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    tm.start();
    cannyEdge_origin_custom(srcImg, dstImg_origin_custom, threshold1, threshold2, apertureSize);
    tm.stop();
    cout << "Timing: " << tm.getTimeMilli() << "ms" << endl;

    imshow("srcImg", srcImg);
    imshow("Result Img Origin OpenCV", dstImg_origin_opencv);
    imshow("Result Img Origin Custom", dstImg_origin_custom);
    waitKey(0);
    return 0;
}

void cannyEdge_origin_opencv(Mat &srcImg, Mat &dstImg, double threshold1, double threshold2, int apertureSize) {
    cvtColor(srcImg, srcImg, CV_RGB2GRAY);
    Canny(srcImg, dstImg, threshold1, threshold2, apertureSize, false);
}

void cannyEdge_origin_custom(Mat &srcImg, Mat &dstImg, double threshold1, double threshold2, int apertureSize) {
    Mat gryImg = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    convertRGB2GRAY(srcImg, gryImg);

    Mat gasImg = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    gaussianBlur(srcImg, gasImg);

    Mat xygImg = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    Mat xyGrad = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    Mat thGrad = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    xyGradient(gasImg, xygImg);

    Mat nmsImg = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    nonMaximumSuppression(xygImg, nmsImg);

    Mat trsImg = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    threshold(nmsImg, trsImg, threshold1, threshold2);

    imshow("", trsImg);
    waitKey(0);

    Mat lnkImg = Mat(srcImg.rows, srcImg.cols, CV_8U, Scalar(0));
    linkage(trsImg, lnkImg);
    dstImg = lnkImg.clone();
}

void cannyEdge_origin2(Mat &dstImg, Mat &srcImg, int k, float lambda) {
}

void gaussianBlur(Mat &srcImg, Mat &dstImg) {
    int cols = srcImg.cols;
    int rows = srcImg.rows;
    Mat gasImg(rows, cols, CV_8U, Scalar(0));
    float **kernel = gaussKernel(3, 0.01);

    Mat padImg = Mat(rows + 2, cols + 2, CV_8U, Scalar(0));
    srcImg.copyTo(padImg(Rect(1, 1, cols, rows)));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            gasImg.at<uchar>(i, j) =
                    kernel[0][0] * (float) padImg.at<uchar>(i - 1, j - 1) +
                    kernel[0][1] * (float) padImg.at<uchar>(i - 1, j) +
                    kernel[0][2] * (float) padImg.at<uchar>(i - 1, j + 1) +
                    kernel[1][0] * (float) padImg.at<uchar>(i, j - 1) +
                    kernel[1][1] * (float) padImg.at<uchar>(i, j) +
                    kernel[1][2] * (float) padImg.at<uchar>(i, j + 1) +
                    kernel[2][0] * (float) padImg.at<uchar>(i + 1, j + 1) +
                    kernel[2][1] * (float) padImg.at<uchar>(i + 1, j) +
                    kernel[2][2] * (float) padImg.at<uchar>(i + 1, j + 1);
        }
    }
    deleteKernel(kernel, 3);
    dstImg = gasImg.clone();
}

float **gaussKernel(int k, float sigma) {
    float **M;
    float sum = 0;
    M = new float *[k];
    for (int i = 0; i < k; i++) {
        M[i] = new float[k];
    }
    for (int i = -(k - 1) / 2; i < (k - 1) / 2 + 1; i++) {
        for (int j = -(k - 1) / 2; j < (k - 1) / 2 + 1; j++) {
            auto f1 = (float) (1.0 / (2 * CV_PI * pow(sigma, 2)));
            auto f2 = (float) (-1 * (pow(i, 2) + pow(j, 2)));
            auto f3 = (float) (f2 / (2 * pow(sigma, 2)));
            M[i + (k - 1) / 2][j + (k - 1) / 2] = f1 * exp(f3);
            sum = sum + M[i + (k - 1) / 2][j + (k - 1) / 2];
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            M[i][j] = M[i][j] / sum;
        }
    }
    return M;
}

void deleteKernel(float **M, int k) {
    for (int i = 0; i < k; i++) {
        delete[] M[i];
        M[i] = nullptr;
    }
    delete[] M;
}

void xyGradient(Mat &srcImg, Mat &dstImg) {
    int cols = srcImg.cols;
    int rows = srcImg.rows;

    Mat x_gra = x_gradient(srcImg);
    Mat y_gra = y_gradient(srcImg);
    dstImg = Mat(rows, cols, CV_8U, Scalar(0));
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) {
            dstImg.at<uchar>(i, j) = sqrt(
                    (x_gra.at<uchar>(i, j) * x_gra.at<uchar>(i, j)) + (y_gra.at<uchar>(i, j) * y_gra.at<uchar>(i, j)));
            if (dstImg.at<uchar>(i, j) > 255) {
                dstImg.at<uchar>(i, j) = 255;
            }
        }
    }
}

Mat x_gradient(const Mat &img) {
    Mat img_src = img.clone();
    int cols = img_src.cols;
    int rows = img_src.rows;
    Mat x_gra = Mat(rows, cols, CV_8U, Scalar(0));
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) {
            x_gra.at<uchar>(i, j) =
                    abs(img_src.at<uchar>(i, j) - img_src.at<uchar>(i + 1, j) + img_src.at<uchar>(i, j + 1) -
                        img_src.at<uchar>(i + 1, j + 1)) / 2;
        }
    }
    return x_gra;
}

Mat y_gradient(const Mat &img) {
    Mat img_src = img.clone();
    int cols = img_src.cols;
    int rows = img_src.rows;
    Mat y_gra = Mat(rows, cols, CV_8U, Scalar(0));
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) {
            y_gra.at<uchar>(i, j) = abs(
                    img_src.at<uchar>(i, j) - img_src.at<uchar>(i, j + 1) + img_src.at<uchar>(i + 1, j) -
                    img_src.at<uchar>(i + 1, j + 1));
        }
    }
    return y_gra;
}

void nonMaximumSuppression(Mat &srcImg, Mat &dstImg) {
    int cols = srcImg.cols;
    int rows = srcImg.rows;
    Mat gra_nms = Mat(rows, cols, CV_8U, Scalar(0));
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            int val00 = srcImg.at<uchar>(i - 1, j - 1);
            int val01 = srcImg.at<uchar>(i - 1, j);
            int val02 = srcImg.at<uchar>(i - 1, j + 1);
            int val10 = srcImg.at<uchar>(i, j - 1);
            int val11 = srcImg.at<uchar>(i, j);
            int val12 = srcImg.at<uchar>(i, j + 1);
            int val20 = srcImg.at<uchar>(i + 1, j - 1);
            int val21 = srcImg.at<uchar>(i + 1, j);
            int val22 = srcImg.at<uchar>(i + 1, j + 1);
            if (val11 < val00 | val11 < val01 | val11 < val02 |
                val11 < val10 | val11 < val12 | val11 < val21 |
                val11 < val22 | val11 < val20) {
                srcImg.at<uchar>(i, j) = 0;
            }
        }
    }
    dstImg = srcImg.clone();
}

void threshold(Mat &srcImg, Mat &dstImg, double min_thresh, double max_thresh) {
    int cols = srcImg.cols;
    int rows = srcImg.rows;
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (srcImg.at<uchar>(i, j) > max_thresh) {
                srcImg.at<uchar>(i, j) = 255;
            }
            if (srcImg.at<uchar>(i, j) < min_thresh) {
                srcImg.at<uchar>(i, j) = 0;
            }
        }
    }
    dstImg = srcImg.clone();
}

void linkage(Mat srcImg, Mat dstImg) {
    int cols = srcImg.cols;
    int rows = srcImg.rows;
    Mat img_l = Mat(rows, cols, CV_8U, Scalar(0));
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            if ((srcImg.at<uchar>(i - 1, j - 1) == 255) |
                (srcImg.at<uchar>(i - 1, j) == 255) |
                (srcImg.at<uchar>(i - 1, j + 1) == 255) |
                (srcImg.at<uchar>(i, j - 1) == 255) |
                (srcImg.at<uchar>(i, j + 1) == 255) |
                (srcImg.at<uchar>(i + 1, j - 1) == 255) |
                (srcImg.at<uchar>(i + 1, j) == 255) |
                (srcImg.at<uchar>(i + 1, j + 1) == 255)) {
                img_l.at<uchar>(i, j) = 255;
            } else {
                img_l.at<uchar>(i, j) = srcImg.at<uchar>(i, j);
            }
        }
    }
    dstImg = img_l.clone();
}