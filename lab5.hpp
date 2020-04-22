//
// Created by rainy on 2020/3/28.
//

#ifndef LAB_LAB5_HPP
#define LAB_LAB5_HPP

#endif //LAB_LAB5_HPP

typedef struct {
    float real;
    float image;
} CNum;

CNum CNumAdd(CNum, CNum);

CNum CNumSub(CNum, CNum);

CNum CNumMul(CNum, CNum);

Mat DFT_trans(Mat img, Mat out);

int calculate_M(int);

void reverse(int, int);

void fft(int, int);

int img2D_DFT(Mat &srcImg);

int img2D_DFT(Mat &srcImg);

void centering(Mat &center_img);

Mat fourior_inverser(Mat &_complexim);

int imgReconstruct(Mat &srcImg);

int imgFilter_IDLPF(Mat &srcImg);

int imgFilter_BLPF(Mat &srcImg);

int imgFilter_GLPF(Mat &srcImg);