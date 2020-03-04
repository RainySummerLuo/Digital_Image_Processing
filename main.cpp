#include "lab1.hpp"
#include "io.hpp"

int main() {
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

    char filename_src[] = "../pic/lena.jpg";
    // lab2_2_1(filename_src);
    // lab2_2_2(filename_src);
    // lab2_2_3(filename_src);
    return 0;
}