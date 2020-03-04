#include "io.hpp"
#include "pgmreader.hpp"

using namespace cv;

void medFilter(Image *image, Image *outimage) {
    unsigned char *tempin, *tempout;
    unsigned char *buff;
    int i, j, height, width;
    int med = 0, max0;
    int p, q;

    tempin = image->data;
    tempout = outimage->data;

    height = outimage->Height;
    width = outimage->Width;

    buff = (unsigned char *) malloc(9);

    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            for (p = 0; p < 3; p++) {
                for (q = 0; q < 3; q++) {
                    buff[3 * p + q] = tempin[(i - 1 + p) * width + j - 1 + q];
                }
            }
            for (p = 0; p < 5; p++) {
                max0 = 0;
                for (q = 0; q < 9 - p; q++) {
                    if (buff[q] >= max0) {
                        max0 = buff[q];
                        med = q;
                    }
                }
                buff[med] = buff[8 - p];
                buff[8 - p] = max0;
            }
            tempout[i * width + j] = buff[4];
        }
    }
}

void avgFilter(Image *image, Image *outimage) {
    unsigned char *tempin, *tempout;
    int i, j, height, width;
    int sum;
    int p, q;

    tempin = image->data;
    tempout = outimage->data;

    height = outimage->Height;
    width = outimage->Width;

    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            sum = 0;
            for (p = 0; p < 3; p++) {
                for (q = 0; q < 3; q++) {
                    sum += tempin[(i - 1 + p) * width + j - 1 + q];
                }
            }
            tempout[i * width + j] = (int) (sum / 9.0);
        }
    }
}

int lab1_1(char *srcFilename, char *outFilename) {
    Image *inImage, *outImageAvg;

    inImage = ReadPNMImage(srcFilename);

    char comment[] = "# test average";

    outImageAvg = CreateNewImage(inImage, comment);

    avgFilter(inImage, outImageAvg);

    SavePNMImage(outImageAvg, outFilename);
}

int lab1_2(char *srcFilename, char *outFilename) {
    Image *inImage, *outImageMed;

    inImage = ReadPNMImage(srcFilename);

    char comment[] = "# test median";

    outImageMed = CreateNewImage(inImage, comment);

    medFilter(inImage, outImageMed);

    SavePNMImage(outImageMed, outFilename);
}

int lab2_2_1(char *filename) {
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

int lab2_2_2(char *filename) {
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

int lab2_2_3(char *filename) {
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