#ifndef LAB_IO_H
#define LAB_IO_H

#endif //LAB_IO_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>

#include <cmath>

using namespace std;
using namespace cv;

extern string srcFilename;

Mat imgRead(char *filename);

Mat imgCreate(Mat &srcImg);

Mat imgCreate(Mat &srcImg, double factorN);

Mat imgCreate(Mat &srcImg, int width, int height);

int imgSave(const string &filename, const Mat &image);

int imgShow(const string &winname, Mat &img);

int pixelSaturation(double value);

int pixelSaturation(int value);

double bicubic_sw(double x);

int TestReadImage(char *, char *);

void convertRGB2GRAY(const Mat &, Mat &);

int findMedian(vector<int>& nums);

int findMin(vector<int>& nums);

int findMax(vector<int>& nums);

int meanVector(vector<int>&, int);