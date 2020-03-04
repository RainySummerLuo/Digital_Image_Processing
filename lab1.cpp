//
// Created by rainy on 2020/3/4.
//

#include "io.h"

using namespace cv;

int lab1_2_1(char *filename) {
    printf("OpenCV: Hello, world!\n");
    Mat image = imread(filename);
    if (image.empty()) {
        std::cout << "Hey! Can't read the image!" << std::endl;
        system("PAUSE");
        return 1;
    }
    namedWindow("Lena Image");
    imshow("Lena Image", image);
    waitKey(1000);
    return 0;
}

int lab1_2_2(char *filename) {
    IplImage *srcImg;
    srcImg = cvvLoadImage(filename);
    if (!srcImg) {
        return 1;
    }
    IplImage *greyImage = cvCreateImage(cvGetSize(srcImg), srcImg->depth, srcImg->alphaChannel);
    cvCvtColor(srcImg, greyImage, CV_BGR2GRAY);
    cvvShowImage("Lena Image - Grey 2", greyImage);
    waitKey(3000);
    return 0;
}

int lab1_2_3(char *filename) {
    Mat srcImage = cv::imread(filename);
    if (!srcImage.data) {
        return 1;
    }
    Mat greyImage;
    cvtColor(srcImage, greyImage, COLOR_BGR2GRAY);
    namedWindow("Lena Image - Grey 1");
    imshow("Lena Image - Grey 1", greyImage);
    waitKey(1000);
    return 0;
}