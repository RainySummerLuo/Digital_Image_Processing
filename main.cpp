#include "lab1.hpp"

#include "io.hpp"

int main() {
    char filename[] = "../pic/lena.jpg";
    char filename_pgm[] = "../pic/lena.pgm";
    char filename_out[] = "../pic/output.pgm";
    // lab2_2_1(filename);
    // lab2_2_2(filename);
    // lab2_2_3(filename);
    TestReadImage(filename_pgm, filename_out);
    return 0;
}