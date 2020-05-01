//
// Created by rainy on 2020/3/28.
//

#include "io.hpp"
#include "lab5.hpp"

int img2D_DFT(Mat &srcImg) {
    cvtColor(srcImg, srcImg, CV_RGB2GRAY);

    Mat padded;
    int m = getOptimalDFTSize(srcImg.rows);
    int n = getOptimalDFTSize(srcImg.cols);

    copyMakeBorder(srcImg, padded, 0, m - srcImg.rows, 0, n - srcImg.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;

    auto size1 = planes[1].size;
    auto size2 = complexI.size;

    merge(planes, 2, complexI);

    dft(complexI, complexI);

    split(complexI, planes);

    magnitude(planes[0], planes[1], planes[0]);

    Mat magI = planes[0];

    magI += Scalar::all(1);
    log(magI, magI);

    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));
    Mat q1(magI, Rect(cx, 0, cx, cy));
    Mat q2(magI, Rect(0, cy, cx, cy));
    Mat q3(magI, Rect(cx, cy, cx, cy));

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX);

    imgShow("Image DFT", magI);
    magI = magI * 255;
    imgSave("ImageDFT", magI);
    return 0;
}

int imgReconstruct(Mat &srcImg) {
    return 0;
}

int imgFilter_IDLPF(Mat &srcImg) {
    return 0;
}

int imgFilter_BLPF(Mat &srcImg) {
    return 0;
}

int imgFilter_GLPF(Mat &srcImg) {
    return 0;
}