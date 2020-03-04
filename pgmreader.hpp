#ifndef LAB_PGMREADER_HPP
#define LAB_PGMREADER_HPP

typedef struct Image {
    int Width;
    int Height;
    int Type;  // Gray=1, Color=2;
    unsigned char *data;
    char comments[15][100];
    int num_comment_lines;
} Image;

void SavePNMImage(Image *, char *);

Image *SwapImage(Image *);

Image *ReadPNMImage(char *);

Image *CreateNewImage(Image *, char *comment);

#endif //LAB_PGMREADER_HPP
