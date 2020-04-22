#include "io.hpp"

#include <opencv2/opencv.hpp>
#include <direct.h>

using namespace std;
using namespace cv;

string srcFilename;

Mat imgRead(char *filename) {
    Mat image = imread(filename);
    if (!image.data) {
        return Mat();
    }
    return image;
}

Mat imgCreate(Mat &srcImg) {
    int imgRow = srcImg.rows;
    int imgCol = srcImg.cols;
    Mat outImg = Mat();
    outImg.create((int) imgRow, (int) imgCol, srcImg.type());
    return outImg;
}

Mat imgCreate(Mat &srcImg, double factorN) {
    int imgRow = srcImg.rows;
    int imgCol = srcImg.cols;
    Mat outImg = Mat();
    outImg.create((int) (imgRow * factorN), (int) (imgCol * factorN), srcImg.type());
    return outImg;
}

Mat imgCreate(Mat &srcImg, int cols, int rows) {
    Mat outImg = Mat();
    outImg.create(rows, cols, srcImg.type());
    return outImg;
}

int imgSave(const string &filename, const Mat &image) {
    int i = srcFilename.rfind('.');
    int j = srcFilename.rfind('/');
    string path = srcFilename.substr(0, j) + "/output/";
    string name = path + filename + "_" + srcFilename.substr(j + 1);
    if (0 != access(path.c_str(), 0)) {
        // if this folder not exist, create a new one.
        mkdir(path.c_str());
    }
    vector<int> imwrite_params;
    Mat cvtImg;
    string file_ext = toLowerCase(srcFilename.substr(i));
    if (file_ext == ".pgm" || file_ext == ".ppm" || file_ext == ".pbm") {
        imwrite_params.push_back(CV_IMWRITE_PXM_BINARY);
        imwrite_params.push_back(0);
        cvtImg = image.clone();
    } else if (file_ext == ".jpg" || file_ext == ".jpeg") {
        imwrite_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        imwrite_params.push_back(100);
        cvtImg = image.clone();
    } else if (file_ext == ".png") {
        imwrite_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        imwrite_params.push_back(0);
        cvtImg = image.clone();
    } else {
        cvtImg = image.clone();
    }
    //cvtImg = image.clone();
    imwrite(name, cvtImg);
    return 0;
}

int imgShow(const string &winname, Mat &img) {
    namedWindow(winname);
    imshow(winname, img);
    waitKey(1000);
    return 0;
}

int pixelSaturation(double value) {
    if (value < 0) {
        return 0;
    } else if (value > 255) {
        return 255;
    } else {
        return (int) cvRound(value);
    }
}

int pixelSaturation(int value) {
    if (value < 0) {
        return 0;
    } else if (value > 255) {
        return 255;
    } else {
        return value;
    }
}

double bicubic_sw(double x) {
    const double a = -0.5;
    double x_abs = abs(x);
    double sw = 0;
    if (x_abs <= 1) {
        sw = (a + 2) * pow(x_abs, 3) - (a + 3) * pow(x_abs, 2) + 1;
    } else if (x_abs < 2) {
        sw = a * pow(x_abs, 3) - 5 * a * pow(x_abs, 2) + 8 * a * x_abs - 4 * a;
    } else {
        sw = 0;
    }
    return sw;
}