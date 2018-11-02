// Author : Akshata Bhat
// USC ID : 9560895350
// Email : akshatab@usc.edu
// Submission Date : 2/4/2018


#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <time.h>
#include "my_header_file.h"
using namespace std;

unsigned char** Floyd_Steinberg_method(unsigned char** Image, int width, int height)
{
    int threshold = 127, error=0;
    for (int i = 0; i < height ; ++i) {
        if(i%2 == 0){
            for (int j = 0; j < width; ++j) {
                int temp = int(Image[i][j]);
                if (Image[i][j] < (unsigned char) threshold)
                    Image[i][j] = (unsigned char) 0;
                else
                    Image[i][j] = (unsigned char) 255;
                error = temp - int(Image[i][j]);
                if(j+1 != width)
                    Image[i][j + 1] = (unsigned char) (float(Image[i][j + 1]) + float(error) * (7.0 / 16.0));
                if (i+1 != height && j+1 != width)
                    Image[i + 1][j + 1] = (unsigned char) (float(Image[i + 1][j + 1]) + float(error) * (1.0 / 16.0));
                if (i + 1 != height)
                    Image[i + 1][j] = (unsigned char) (float(Image[i + 1][j]) + float(error) * (5.0 / 16.0));
                if (j - 1 != -1 && i+1 != height)
                    Image[i + 1][j - 1] = (unsigned char) (float(Image[i+1][j - 1]) + float(error) * (3.0 / 16.0));
            }
        }
        else{
            for (int j = width-1; j > 0; --j) {
                int temp =int(Image[i][j]);
                if (Image[i][j] < (unsigned char)threshold)
                    Image[i][j] = (unsigned char)0;
                else
                    Image[i][j] = (unsigned char)255;
                error = temp - int(Image[i][j]);
                if (j-1 != -1)
                    Image[i][j-1] = (unsigned char)(float(Image[i][j-1]) + float(error) * (7.0 / 16.0));
                if (j-1 != -1 && i+1 != height)
                    Image[i+1][j-1] = (unsigned char)(float(Image[i+1][j-1]) + float(error) * (1.0 / 16.0));
                if (i+1 != height)
                    Image[i+1][j] = (unsigned char)(float(Image[i+1][j]) + float(error) * (5.0 / 16.0));
                if (i+1 != height && j+1 != width)
                    Image[i+1][j+1] = (unsigned char)(float(Image[i+1][j+1]) + float(error) * (3.0 / 16.0));
            }

        }

    }
    return Image;
}

unsigned char** Diffusion_5x5method(unsigned char** Image, int width, int height, float* diffuser) {
    int threshold = 127, error = 0;
    for (int i = 0; i < height; ++i) {
        if(i%2 == 0){
            for (int j = 0; j < width; ++j) {
                int temp = int(Image[i][j]);
                //cout << temp << "\t";
                if (Image[i][j] < (unsigned char) threshold)
                    Image[i][j] = (unsigned char) 0;
                else
                    Image[i][j] = (unsigned char) 255;
                error = temp - int(Image[i][j]);
                //cout << temp << endl;
                if (j + 1 < width) {
                    Image[i][j + 1] = (unsigned char) (float(Image[i][j + 1]) + float(error) * diffuser[0]);
                    if (j + 2 < width)
                        Image[i][j + 2] = (unsigned char) (float(Image[i][j + 2]) + float(error) * diffuser[1]);
                }
                if (i + 1 < height){
                    if (j - 1 > -1){
                        Image[i + 1][j - 1] = (unsigned char) (float(Image[i + 1][j - 1]) + float(error) * diffuser[3]);
                        if (j - 2 > -1)
                            Image[i + 1][j - 2] = (unsigned char) (float(Image[i + 1][j - 2]) +
                                                                     float(error) * diffuser[2]);
                    }
                    Image[i + 1][j] = (unsigned char) (float(Image[i + 1][j]) + float(error) * diffuser[4]);
                    if (j + 1 < width) {
                        Image[i + 1][j + 1] = (unsigned char) (float(Image[i + 1][j + 1]) + float(error) * diffuser[5]);
                        if (j + 2 < width)
                            Image[i + 1][j + 2] = (unsigned char) (float(Image[i + 1][j + 2]) + float(error) * diffuser[6]);
                    }
                }
                if (i + 2 < height) {
                    if (j - 1 > -1) {
                        Image[i + 2][j - 1] = (unsigned char) (float(Image[i + 2][j - 1]) + float(error) * diffuser[8]);
                        if (j - 2 > -1)
                            Image[i + 2][j - 2] = (unsigned char) (float(Image[i + 2][j - 2]) +
                                                                     float(error) * diffuser[7]);
                    }
                    Image[i + 2][j] = (unsigned char) (float(Image[i + 2][j]) + float(error) * diffuser[9]);
                    if (j + 1 < width) {
                        Image[i + 2][j + 1] = (unsigned char) (float(Image[i + 2][j + 1]) + float(error) * diffuser[10]);
                        if (j + 2 < width)
                            Image[i + 2][j + 2] = (unsigned char) (float(Image[i + 2][j + 2]) + float(error) * diffuser[11]);
                    }
                }
            }
        }
        else{
            for (int j = width-1; j > 0; --j) {
                int temp = int(Image[i][j]);
                if (Image[i][j] < (unsigned char) threshold)
                    Image[i][j] = (unsigned char) 0;
                else
                    Image[i][j] = (unsigned char) 255;
                error = temp - int(Image[i][j]);
                if (j - 1 > -1) {
                    Image[i][j - 1] = (unsigned char) (float(Image[i][j - 1]) + float(error) * diffuser[0]);
                    if (j - 2 > -1)
                        Image[i][j - 2] = (unsigned char) (float(Image[i][j - 2]) + float(error) * diffuser[1]);
                }
                if (i + 1 < height){
                    if (j - 1 > -1){
                        Image[i + 1][j - 1] = (unsigned char) (float(Image[i + 1][j - 1]) + float(error) * diffuser[3]);
                        if (j - 2 > -1)
                            Image[i + 1][j - 2] = (unsigned char) (float(Image[i + 1][j - 2]) +
                                                                   float(error) * diffuser[2]);
                    }
                    Image[i + 1][j] = (unsigned char) (float(Image[i + 1][j]) + float(error) * diffuser[4]);
                    if (j + 1 < width) {
                        Image[i + 1][j + 1] = (unsigned char) (float(Image[i + 1][j + 1]) + float(error) * diffuser[5]);
                        if (j + 2 < width)
                            Image[i + 1][j + 2] = (unsigned char) (float(Image[i + 1][j + 2]) + float(error) * diffuser[6]);
                    }
                }
                if (i + 2 < height) {
                    if (j - 1 > -1) {
                        Image[i + 2][j - 1] = (unsigned char) (float(Image[i + 2][j - 1]) + float(error) * diffuser[8]);
                        if (j - 2 > -1)
                            Image[i + 2][j - 2] = (unsigned char) (float(Image[i + 2][j - 2]) +
                                                                   float(error) * diffuser[7]);
                    }
                    Image[i + 2][j] = (unsigned char) (float(Image[i + 2][j]) + float(error) * diffuser[9]);
                    if (j + 1 < width) {
                        Image[i + 2][j + 1] = (unsigned char) (float(Image[i + 2][j + 1]) + float(error) * diffuser[10]);
                        if (j + 2 < width)
                            Image[i + 2][j + 2] = (unsigned char) (float(Image[i + 2][j + 2]) + float(error) * diffuser[11]);
                    }
                }
            }
        }
    }
    return Image;
}


int main(int argc, char *argv[]) {
    FILE *fptr1;

    if (argc != 5) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "Syntax : hw2_prob2b <input_image.raw> <width> <height> <bytes_per_pixel>" << endl;
        return 0;
    }

    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    int bytesPerPixel = atoi(argv[4]);
    int totalBytes = width * height * bytesPerPixel;

    unsigned char* Imagedata = NULL;
    Imagedata = new unsigned char[totalBytes];
    memset(Imagedata,0,totalBytes);

    if (!(fptr1 = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    unsigned char **Image2D = NULL;
    Image2D = convert_1Dto2D(Imagedata,width,height);

    //Floyd Steinberg Diffusion method
    unsigned char **outputFlyod = NULL;
    outputFlyod = Floyd_Steinberg_method(Image2D, width, height);
    unsigned char* Imagedata1 = NULL;
    Imagedata1 = convert_2Dto1D(outputFlyod, width,height);
    char filename1[] = "ErrorDiffusion-FloydSteinberg.raw";
    write_1Darray_to_file(Imagedata1,width,height,filename1);


    float JJN[12] = {7.0/48.0, 5.0/48.0,
                     3.0/48.0, 5.0/48.0, 7.0/48.0, 5.0/48.0, 3.0/48.0,
                     1.0/48.0, 3.0/48.0, 5.0/48.0, 3.0/48.0, 1.0/48.0};
    unsigned char **Image2D_J = NULL;
    Image2D_J = convert_1Dto2D(Imagedata,width,height);
    unsigned char **outputJJN = NULL;
    outputJJN = Diffusion_5x5method(Image2D_J, width,height, JJN);
    unsigned char* Imagedata2 = NULL;
    Imagedata2 = convert_2Dto1D(outputJJN, width,height);
    char filename2[] = "ErrorDiffusion-JJN.raw";
    write_1Darray_to_file(Imagedata2,width,height,filename2);


    float Stucki[12] = {8.0/42.0, 4.0/42.0,
                        2.0/42.0, 4.0/42.0, 8.0/42.0, 4.0/42.0, 2.0/42.0,
                        1.0/42.0, 2.0/42.0, 4.0/42.0, 2.0/42.0, 1.0/42.0};
    unsigned char **Image2D_S = NULL;
    Image2D_S = convert_1Dto2D(Imagedata,width,height);
    unsigned char **outputStucki = NULL;
    outputStucki = Diffusion_5x5method(Image2D_S, width,height, Stucki);
    unsigned char* Imagedata3 = NULL;
    Imagedata3 = convert_2Dto1D(outputStucki, width,height);
    char filename3[] = "ErrorDiffusion-Stucki.raw";
    write_1Darray_to_file(Imagedata3,width,height,filename3);


    float Akshata[12] = {36.0/186.0, 18.0/186.0,
                          9.0/186.0, 18.0/186.0, 36.0/186.0, 18.0/186.0, 9.0/186.0,
                          3.0/186.0, 9.0/186.0, 18.0/186.0, 9.0/186.0, 3.0/186.0};
    unsigned char **Image2D_Ak = NULL;
    Image2D_Ak = convert_1Dto2D(Imagedata,width,height);
    unsigned char **outputAk = NULL;
    outputAk = Diffusion_5x5method(Image2D_Ak, width,height, Akshata);
    unsigned char* Imagedata4 = NULL;
    Imagedata4 = convert_2Dto1D(outputAk, width,height);
    char filename4[] = "ErrorDiffusion-Akshata.raw";
    write_1Darray_to_file(Imagedata4,width,height,filename4);

    return 0;
}