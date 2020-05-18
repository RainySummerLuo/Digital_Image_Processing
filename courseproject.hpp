//
// Created by rainy on 2020/5/3.
//

#ifndef LAB_COURSEPROJECT_HPP
#define LAB_COURSEPROJECT_HPP

#endif //LAB_COURSEPROJECT_HPP

int imgCannyEdge(Mat &);

void cannyEdge_origin_opencv(Mat &, Mat &, double, double, int);

void cannyEdge_origin_custom(Mat &, Mat &, double, double, int);

void cannyEdge_origin(Mat &, Mat &, int, float);

void gaussianBlur(Mat &, Mat &);

float** gaussKernel(int, float);

void deleteKernel(float**, int);

void xyGradient(Mat &, Mat &);

Mat x_gradient(const Mat&);

Mat y_gradient(const Mat&);

void nonMaximumSuppression(Mat &, Mat &);

void threshold(Mat &, Mat &, double, double);

void linkage(Mat, Mat);