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

int imgSave(const string &filename, const Mat &img) {
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
        cvtImg = img.clone();
    } else if (file_ext == ".jpg" || file_ext == ".jpeg") {
        imwrite_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        imwrite_params.push_back(100);
        cvtImg = img.clone();
    } else if (file_ext == ".png") {
        imwrite_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        imwrite_params.push_back(0);
        cvtImg = img.clone();
    } else {
        cvtImg = img.clone();
    }
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

void convertRGB2GRAY(const Mat &srcImg, Mat &dstImg) {
    if (!srcImg.data || srcImg.channels() != 3) {
        return;
    }
    dstImg = Mat::zeros(srcImg.size(), CV_8U);
    uchar *pointSrcImg = srcImg.data;
    uchar *pointDstImg = dstImg.data;
    int stepImage = srcImg.step;
    int stepImageGray = dstImg.step;
    for (int i = 0; i < dstImg.rows; i++) {
        for (int j = 0; j < dstImg.cols; j++) {
            pointDstImg[i * stepImageGray + j] =
                    0.114 * pointSrcImg[i * stepImage + 3 * j] +
                    0.587 * pointSrcImg[i * stepImage + 3 * j + 1] +
                    0.299 * pointSrcImg[i * stepImage + 3 * j + 2];
        }
    }
}

int findMedian(vector<int>& nums) {
    int median = nums[0];
    int count = 0;
    for (auto const& num: nums) {
        if (num > median) {
            median = num;
            count++;
        }
        if (count == 5) {
            break;
        }
    }
    return median;
}

int findMin(vector<int>& nums) {
    int min = nums[0];
    int count = 0;
    for (auto const& num: nums) {
        if (min > num) {
            min = num;
            count++;
        }
        if (count == 5) {
            break;
        }
    }
    return min;
}

int findMax(vector<int>& nums) {
    int max = nums[0];
    int count = 0;
    for (auto const& num: nums) {
        if (max < num) {
            max = num;
            count++;
        }
        if (count == 5) {
            break;
        }
    }
    return max;
}

int meanVector(vector<int>& nums, int tSize) {
    int mean = 0;
    for (int i = 0; i < tSize; ++i) {
        int min = nums[0];
        int minIndex = 0;
        int max = nums[0];
        int maxIndex = 0;
        for (int j = 0; j < nums.size(); ++j) {
            int num = nums[j];
            if(num > max) {
                max = num;
                maxIndex = j;
            }
        }
        nums.erase(nums.begin() + maxIndex);
        for (int j = 0; j < nums.size(); ++j) {
            int num = nums[j];
            if(num < min) {
                min = num;
                minIndex = j;
            }
        }
        nums.erase(nums.begin() + minIndex);
    }
    int sum = 0;
    for (int j = 0; j < nums.size(); ++j) {
        sum += nums[j];
    }
    mean = pixelSaturation((double)sum / nums.size());
    return mean;
}