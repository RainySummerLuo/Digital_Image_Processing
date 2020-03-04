//
// Created by rainy on 2020/3/4.
//

#include <opencv2/opencv.hpp>

using namespace cv;

int lab1_2_1(char *filename) {
    printf("Hello world\n");
    Mat image = imread(filename);
    if (image.empty())
    {
        std::cout << "Hey! Can't read the image!" << std::endl;
        system("PAUSE");
        return EXIT_FAILURE;
    }
    namedWindow("My Image");
    imshow("My Image", image);
    waitKey(5000);
    return EXIT_SUCCESS;
}

int lab1_2_2() {
    // ��ȡԴͼ��ת��Ϊ�Ҷ�ͼ��
    Mat srcImage = cv::imread(R"(.\bh3.png)");
    // �ж��ļ��Ƿ������ȷ
    if (!srcImage.data)
        return 1;
    // ͼ����ʾ
    imshow("srcImage", srcImage);
    // �ȴ����̼���
    waitKey(0);
    return 0;
}

int lab1_2_3() {
    // ��ȡԴͼ��ת��Ϊ�Ҷ�ͼ��
    IplImage* img;
    img = cvvLoadImage(".\bh3.png");
    // �ж��ļ��Ƿ������ȷ
    if (!img)
        return 1;
    // ͼ����ʾ
    cvvShowImage("srcImage", img);
    // �ȴ����̼���
    waitKey(0);
    return 0;
}