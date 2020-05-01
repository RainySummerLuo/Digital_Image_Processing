//
// Created by rainy on 2020/4/21.
//

#include "io.hpp"
#include "lab6.hpp"

void dftt(Mat &src, Mat &dst) {
    Mat padded;
    int m = getOptimalDFTSize(src.rows);
    int n = getOptimalDFTSize(src.cols);
    copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);
    dst = complexI;
    dst = dst(Rect(0, 0, complexI.cols & -2, complexI.rows & -2));
}

int imgHPF_fingerprint(Mat &srcImg) {
    srcImg.convertTo(srcImg, CV_32F);
    cvtColor(srcImg, srcImg, CV_RGB2GRAY);

    int n = 4;

    Mat mag;
    dftt(srcImg, mag);
    int cx = mag.cols / 2;
    int cy = mag.rows / 2;
    Mat tmp;
    Mat q0(mag, Rect(0, 0, cx, cy));
    Mat q1(mag, Rect(cx, 0, cx, cy));
    Mat q2(mag, Rect(0, cy, cx, cy));
    Mat q3(mag, Rect(cx, cy, cx, cy));
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    double D0 = 50.0;
    double h;

    for (int y = 0; y < mag.rows; y++) {
        auto *data = mag.ptr<float>(y);
        int j = 0;
        for (int x = 0; x < mag.cols; x++) {
            double d = sqrt(pow((y - cy), 2) + pow((x - cx), 2));
            if (d == 0) { h = 0.0; }
            else { h = 1.0 / (1.0 + pow((D0 / d), 2 * n)); }
            data[x + j] = data[x] * h;
            data[x + j + 1] = data[x + j + 1] * h;
            j += 1;
        }
    }

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    Mat invDFT, invDFTcvt;
    idft(mag, invDFT, DFT_SCALE | DFT_REAL_OUTPUT);
    Mat dst;
    threshold(invDFT, dst, 0, 255, 0);
    dst.convertTo(invDFTcvt, CV_8U);
    Mat dstImg(invDFTcvt, Rect(0, 0, srcImg.cols, srcImg.rows));
    imgShow("HPF-Fingerprint", dstImg);
    imgSave("imgHPF_Fingerprint", dstImg);\
    return 0;
}

double pixelDistance(double u, double v) {
    return std::sqrt(u * u + v * v);
}

double gaussianCoeff(double u, double v, double d0) {
    double d = pixelDistance(u, v);
    return 1.0 - std::exp((-d * d) / (2 * d0 * d0));
}

int imgHomomorphic(Mat &srcImg) {
    srcImg.convertTo(srcImg, CV_32F);
    cvtColor(srcImg, srcImg, CV_RGB2GRAY);

    log(srcImg + 1, srcImg);

    Mat padded;
    int m = getOptimalDFTSize(srcImg.rows);
    int n = getOptimalDFTSize(srcImg.cols);
    copyMakeBorder(srcImg, padded, 0, m - srcImg.rows, 0, n - srcImg.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat fourierImage;

    dct(padded, fourierImage);

    int sigma = 3;
    Point2f center;
    center.x = (float) fourierImage.rows / 2;
    center.y = (float) fourierImage.cols / 2;

    Mat gaussFilter = Mat::zeros(fourierImage.rows, fourierImage.cols, CV_32F);
    for (int row = 0; row < fourierImage.rows; row++) {
        for (int col = 0; col < fourierImage.cols; col++) {
            gaussFilter.at<float>(row, col) = gaussianCoeff(row, col, sigma);
        }
    }

    fourierImage = fourierImage.mul(gaussFilter);

    Mat dstImg;
    idct(fourierImage, dstImg, DFT_INVERSE);

    exp(dstImg - 1, dstImg);

    imgShow("Img Homomorphic", dstImg);

    imgSave("imgHomomorphic", dstImg * 255);
    return 0;
}

int imgCorrelation(Mat &srcImg, Mat &temImg) {
    Mat img_display;
    srcImg.copyTo(img_display);

    int result_cols = srcImg.cols - temImg.cols + 1;
    int result_rows = srcImg.rows - temImg.rows + 1;

    Mat dstImg;

    dstImg.create(result_rows, result_cols, CV_32F);

    int method = 5;
    matchTemplate(srcImg, temImg, dstImg, method);
    normalize(dstImg, dstImg, 0, 1, NORM_MINMAX, -1, Mat());

    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;

    minMaxLoc(dstImg, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    if (method == CV_TM_SQDIFF || method == CV_TM_SQDIFF_NORMED) {
        matchLoc = minLoc;
    } else {
        matchLoc = maxLoc;
    }

    cout << "Similarity: " << maxVal  * 100 << "%" << endl;

    rectangle(img_display, matchLoc, Point(matchLoc.x + temImg.cols, matchLoc.y + temImg.rows), Scalar::all(0), 2, 8, 0);

    imgShow("dis", img_display);
    imgSave("imgCorrelation", img_display);
    return 0;
}