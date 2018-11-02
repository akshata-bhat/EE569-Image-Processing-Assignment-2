// Author : Akshata Bhat
// USC ID : 9560895350
// Email : akshatab@usc.edu
// Submission Date : 3/4/2018


#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "my_header_file.h"
using namespace std;

unsigned char** square_to_disc(unsigned char** inputImage, int width, int height){
    double  x, y, u, v;
    int i, j, r,c;
    float mid = width/2 -1;
    unsigned char **outputImage = NULL;
    outputImage = create_2Darray(outputImage, width, height);
    for (i = 0; i < height ; ++i) {
        for (j = 0; j < width; ++j) {
            x = double(i - mid) / mid;
            y = double(j - mid) / mid;
            u = x * sqrt(1 - pow(y, 2) / 2);
            v = y * sqrt(1 - pow(x, 2) / 2);
            r = int(u * mid + mid);
            c = int(v * mid + mid);
            outputImage[r][c] = inputImage[i][j];
        }
    }
    return outputImage;
}

unsigned char** disc_to_square(unsigned char** inputImage, int width, int height){
    double  x, y, u, v, x1, y1;
    int i, j, r,c,r1, c1;
    float mid = width/2 -1;
    unsigned char **reverseImage = NULL;
    reverseImage = create_2Darray(reverseImage, width, height);
    for (i = 0; i < height ; ++i) {
        for (j = 0; j < width ; ++j) {
            x=double(i-mid)/mid;
            y=double(j-mid)/mid;
            u = x * sqrt(1 - pow(y, 2)/2);
            v = y * sqrt(1 - pow(x, 2)/2);
            r=int(u*mid+mid);
            c=int(v*mid+mid);
            x1=(0.5*sqrt(abs(2.0+u*u-v*v+(2.0*sqrt(2.0)*u)))) - (0.5*sqrt(abs(2.0+u*u-v*v-(2*sqrt(2.0)*u))));
            y1=(0.5*sqrt(abs(2.0-u*u+v*v+(2.0*sqrt(2.0)*v)))) - (0.5*sqrt(abs(2.0-u*u+v*v-(2*sqrt(2.0)*v))));
            r1=round(x1*mid+mid);
            c1=round(y1*mid+mid);
            reverseImage[r1][c1] = inputImage[r][c];
        }
    }
    return reverseImage;
}

int main(int argc, char *argv[]) {
    FILE *fptr1, *fptr2;

    if (argc != 5) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "Syntax : prob1a <input_image.raw> <width> <height> <bytes_per_pixel>" << endl;
        return 0;
    }

    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    int bytesPerPixel = atoi(argv[4]);
    int totalBytes = width * height * bytesPerPixel;

    unsigned char* Imagedata = NULL;
    Imagedata = new unsigned char[totalBytes];
    unsigned char* Imagedata1 = NULL;
    Imagedata1 = new unsigned char[totalBytes];
    unsigned char* Imagedata2 = NULL;
    Imagedata2 = new unsigned char[totalBytes];

    if (!(fptr1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    //To convert a square image to a circular image
    int i, j, count=0;
    unsigned char **Image2D_R = NULL;
    unsigned char **Image2D_G = NULL;
    unsigned char **Image2D_B = NULL;
    Image2D_R = create_2Darray(Image2D_R, width, height);
    Image2D_G = create_2Darray(Image2D_G, width, height);
    Image2D_B = create_2Darray(Image2D_B, width, height);

    while(count<totalBytes) {
        for(i=0;i<height;i++) {
            for(j=0;j<width;j++) {
                Image2D_R[i][j]=Imagedata[count];
                Image2D_G[i][j]=Imagedata[count+1];
                Image2D_B[i][j]=Imagedata[count+2];
                count=count+3;
            }
        }
    }

    unsigned char **outputImage2D_R = NULL;
    unsigned char **outputImage2D_G = NULL;
    unsigned char **outputImage2D_B = NULL;
    outputImage2D_R = square_to_disc(Image2D_R, width, height);
    outputImage2D_G = square_to_disc(Image2D_G, width, height);
    outputImage2D_B = square_to_disc(Image2D_B, width, height);;


    count =0;
    while (count < totalBytes) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                Imagedata1[count] = outputImage2D_R[i][j];
                Imagedata1[count+1] = outputImage2D_G[i][j];
                Imagedata1[count+2] = outputImage2D_B[i][j];
                count = count + 3;
            }
        }
    }

    if (!(fptr2 = fopen("Warped_output.raw", "wb"))) {
        cout << "Cannot open file: Warped_output.raw" << endl;
        exit(1);
    }
    fwrite(Imagedata1, sizeof(unsigned char), totalBytes, fptr2);
    fclose(fptr2);

    // To convert a circular image to a square image
    unsigned char **reverseImage2D_R = NULL;
    unsigned char **reverseImage2D_G = NULL;
    unsigned char **reverseImage2D_B = NULL;

    reverseImage2D_R = disc_to_square(outputImage2D_R , width, height);
    reverseImage2D_G = disc_to_square(outputImage2D_G , width, height);
    reverseImage2D_B = disc_to_square(outputImage2D_B , width, height);

    count =0;
    while (count < totalBytes) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                Imagedata2[count] = reverseImage2D_R[i][j];
                Imagedata2[count+1] = reverseImage2D_G[i][j];
                Imagedata2[count+2] = reverseImage2D_B[i][j];
                count = count + 3;
            }
        }
    }


    if (!(fptr2 = fopen("Reversed_output.raw", "wb"))) {
        cout << "Cannot open file: Reversed_output.raw" << endl;
        exit(1);
    }
    fwrite(Imagedata2, sizeof(unsigned char), totalBytes, fptr2);
    fclose(fptr2);

    return 0;
}