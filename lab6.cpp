//
// Created by rainy on 2020/4/21.
//

#include "io.hpp"
#include "lab6.hpp"

int imgHPF_fingerprint(Mat &srcImg) {
    resize(srcImg, srcImg, Size(), 0.25, 0.25);
    srcImg.convertTo(srcImg, CV_32F);
    cvtColor(srcImg, srcImg, CV_RGB2GRAY);

    Mat padded;
    int m = getOptimalDFTSize(srcImg.rows);
    int n = getOptimalDFTSize(srcImg.cols);

    copyMakeBorder(srcImg, padded, 0, m - srcImg.rows, 0, n - srcImg.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);

    split(complexI, planes);

    zero_to_center(planes[0]);
    zero_to_center(planes[1]);

    magnitude(planes[0], planes[1], planes[0]);

    divide(planes[0], n * m, planes[0]);

    Mat butter_sharpen(padded.size(), CV_32F);
    float D0 = 50.;
    int nn = 4;
    for (int i = 0; i < butter_sharpen.rows; i++) {
        auto *q = butter_sharpen.ptr<float>(i);
        for (int j = 0; j < butter_sharpen.cols; j++) {
            auto d = (float) sqrt(pow(i - n / 2, 2) + pow(j - m / 2, 2));
            q[2 * j] = 1.0 / (1 + pow(D0 / d, 2 * nn));
            q[2 * j + 1] = 1.0 / (1 + pow(D0 / d, 2 * nn));
        }
    }

    merge(planes, 2, complexI);

    multiply(complexI, butter_sharpen, complexI);

    idft(complexI, complexI);

    Mat dstSharpen[2];
    split(complexI, dstSharpen);

    for (int i = 0; i < n; i++) {
        auto *q = dstSharpen[0].ptr<float>(i);
        for (int j = 0; j < m; j++) {
            q[j] = q[j] * pow(-1, i + j);
        }
    }
    Mat show;

    normalize(dstSharpen[0], show, 1, 0, CV_MINMAX);

    show = show(Rect(0, 0, srcImg.cols, srcImg.rows));

    threshold(dstSharpen[0], dstSharpen[0], 0, 255, THRESH_BINARY);
    normalize(dstSharpen[0], dstSharpen[0], 0, 1, CV_MINMAX);
    dstSharpen[0] = dstSharpen[0](Rect(0, 0, srcImg.cols, srcImg.rows));
    imgShow("dstSharpen", dstSharpen[0]);
    waitKey(2000);
    return 0;
}

void zero_to_center(Mat &freq_plane) {
    int cx = freq_plane.cols / 2;
    int cy = freq_plane.rows / 2;

    Mat part1_r(freq_plane, Rect(0, 0, cx, cy)); //元素坐标表示为(cx,cy)
    Mat part2_r(freq_plane, Rect(cx, 0, cx, cy));
    Mat part3_r(freq_plane, Rect(0, cy, cx, cy));
    Mat part4_r(freq_plane, Rect(cx, cy, cx, cy));

    Mat tmp;
    part1_r.copyTo(tmp); //左上与右下交换位置(实部)
    part4_r.copyTo(part1_r);
    tmp.copyTo(part4_r);

    part2_r.copyTo(tmp); //右上与左下交换位置(实部)
    part3_r.copyTo(part2_r);
    tmp.copyTo(part3_r);
}