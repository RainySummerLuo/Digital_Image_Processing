#include "io.hpp"

#include "lab1.hpp"
#include "lab2.hpp"
#include "lab3.hpp"
#include "lab4.hpp"
#include "lab5.hpp"
#include "lab6.hpp"

int main() {
    //char srcFile[] = "../pic/lab4/lena.png";
    char srcFile[] = "../pic/lab5/noise.png";
    srcFilename = srcFile;
    /*
    char filename_lena_pgm[] = "../pic/lab1/lena.pgm";
    char filename_lena_out_1[] = "../pic/lab1/lena_output_1.pgm";
    char filename_lena_out_2[] = "../pic/lab1/lena_output_2.pgm";
    lab1_1(filename_lena_pgm, filename_lena_out_1);
    lab1_2(filename_lena_pgm, filename_lena_out_2);

    char filename_noise_pgm[] = "../pic/lab1/noise.pgm";
    char filename_noise_out_1[] = "../pic/lab1/noise_output_1.pgm";
    char filename_noise_out_2[] = "../pic/lab1/noise_output_2.pgm";
    lab1_1(filename_noise_pgm, filename_noise_out_1);
    lab1_2(filename_noise_pgm, filename_noise_out_2);

    // lab2_2_1(filename_src);
    // lab2_2_2(filename_src);
    // lab2_2_3(filename_src);
    */

    Mat srcImg = imgRead(srcFile);
    //imgReduce_alternative_line(srcImg, 0.5);
    //imgReduce_fractional_linear_reduction(srcImg, 0.5);
    //imgEnlarge_pixel_replication(srcImg, 2);
    //imgEnlarge_nearest_neighbor_interpolation(srcImg, 2);
    //imgEnlarge_bilinear_interpolation(srcImg, 2);
    //imgEnlarge_bicubic_interpolation(srcImg, 2);
    //imgEnlarge_fractional_linear_expansion(srcImg, 2);
    //imgNegative(srcImg);

    //imgTranslation(srcImg, 50, 30);
    //imgRotation(srcImg, 45);
    //imgShear_x(srcImg, CV_PI / 3);
    //imgShear_y(srcImg, CV_PI / 3);

    //imgSharpen_Laplacian(srcImg);
    //imgSharpen_Sobel(srcImg);
    //imgCorrection_GammaCorrection(srcImg, 1);
    //imgEnhancement_Histogram_Local(srcImg, 6);
    //imgEnhancement_Histogram_Global(srcImg);

    //img2D_DFT(srcImg);
    imgReconstruct(srcImg);

    //imgHPF_fingerprint(srcImg);
    return 0;
}