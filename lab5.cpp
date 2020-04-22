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

    Mat img_angle;
    Mat temp[] = {Mat::zeros(planes[0].size(), CV_32F), Mat::zeros(planes[0].size(), CV_32F)};
    float realv = 0.0, imaginv = 0.0;
    for (int i = 0; i < planes[0].cols; i++) {
        for (int j = 0; j < planes[0].rows; j++) {
            realv = planes[0].at<float>(i, j);
            imaginv = planes[1].at<float>(i, j);
            float distance = sqrt(realv * realv + imaginv * imaginv);
            temp[0].at<float>(i, j) = realv / distance;
            temp[1].at<float>(i, j) = imaginv / distance;
        }
    }
    merge(temp, 2, img_angle);

    Mat result;
    Mat temp2[] = {Mat::zeros(planes[0].size(), CV_32F), Mat::zeros(planes[0].size(), CV_32F)};
    float realv1 = 0.0, imaginv1 = 0.0, realv2 = 0.0, imaginv2 = 0.0;
    for (int i = 0; i < planes[0].cols; i++) {
        for (int j = 0; j < planes[0].rows; j++) {
            realv1 = planes[0].at<float>(i, j);
            float distance1 = sqrt(realv1 * realv1 + imaginv1 * imaginv1);
            float distance2 = sqrt(realv2 * realv2 + imaginv2 * imaginv2);
            temp2[0].at<float>(i, j) = (realv1 * distance2) / distance1;
            temp2[1].at<float>(i, j) = (imaginv1 * distance2) / distance1;
        }
    }
    merge(temp2, 2, result);

    Mat amplitude, angle, amplitude_src;
    magnitude(planes[0], planes[1], amplitude); //计算原图像幅值
    phase(planes[0], planes[1], angle); //计算原图像相位

    centering(amplitude);

    divide(amplitude, amplitude.cols * amplitude.rows, amplitude_src);
    imshow("amplitude_src", amplitude_src);

    amplitude += Scalar::all(1);
    log(amplitude, amplitude);
    normalize(amplitude, amplitude, 0, 255, NORM_MINMAX); //归一化 方便显示，和实际数据没有关系
    amplitude.convertTo(amplitude, CV_32F);
    imshow("amplitude", amplitude);

    normalize(angle, angle, 0, 255, NORM_MINMAX); //归一化 方便显示，和实际数据没有关系
    angle.convertTo(angle, CV_32F);
    imshow("angle", angle);

    Mat inverse_amp = fourior_inverser(img_angle); //傅里叶逆变换
    Mat inverse_angle = fourior_inverser(img_angle);
    Mat inverse_dst = fourior_inverser(result);
    centering(inverse_angle);
    imshow("inverse_angle", inverse_amp);
    imshow("inverse_amp", inverse_angle);
    imshow("woman_amp2sqrt_angle", inverse_dst);
    //imwrite("phase.jpg", angle);
    return 0;
}

void centering(Mat &center_img) {
    int cx = center_img.cols / 2;
    int cy = center_img.rows / 2;

    Mat q0(center_img, Rect(0, 0, cx, cy));  // Top-Left - Create a ROI per quadrant
    Mat q1(center_img, Rect(cx, 0, cx, cy)); // Top-Right
    Mat q2(center_img, Rect(0, cy, cx, cy)); // Bottom-Left
    Mat q3(center_img, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

Mat fourior_inverser(Mat &_complexim) {
    Mat dst;
      Mat iDft[]={Mat::zeros(_complexim.size(),CV_32F),Mat::zeros(_complexim.size(),CV_32F)};
      idft(_complexim,_complexim);
      split(_complexim,iDft);
      magnitude(iDft[0],iDft[1],dst);
      normalize(dst, dst, 0, 255, NORM_MINMAX);
      dst.convertTo(dst, CV_32F);
      return dst;
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