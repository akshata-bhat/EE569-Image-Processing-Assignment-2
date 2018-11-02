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

unsigned char** embed_into_bigger_image(unsigned char** inputImage, unsigned char** embeddedImage, int width, int height) {
    int x=0,y=0;
    for (int i = 0.5*height; i < 1.5*height; i++) {
        x=i-(0.5*height);
        for (int j = 1.5*width; j < 2.5*width; ++j) {
            y=j-(1.5*width);
            embeddedImage[i][j] = inputImage[x][y];
        }
    }
    return  embeddedImage;
}


int main(int argc, char *argv[]) {
    FILE *fptr1;

    if (argc != 7) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout
                << "Syntax : hw2_prob1b <left.raw> <middle.raw> <right.raw> <width> <height> <bytes_per_pixel>"
                << endl;
        return 0;
    }

    char *inputFilename1 = argv[1];
    char *inputFilename2 = argv[2];
    char *inputFilename3 = argv[3];
    int width = atoi(argv[4]);
    int height = atoi(argv[5]);
    int bytesPerPixel = atoi(argv[6]);
    int totalBytes = width * height * bytesPerPixel;


    int i, j, count=0;
    unsigned char *Imagedata2 = NULL;
    Imagedata2 = read_1Darray_from_file(width*bytesPerPixel, height, inputFilename2);
    unsigned char **Image2D_R = NULL;
    unsigned char **Image2D_G = NULL;
    unsigned char **Image2D_B = NULL;
    Image2D_R = create_2Darray(Image2D_R, width, height);
    Image2D_G = create_2Darray(Image2D_G, width, height);
    Image2D_B = create_2Darray(Image2D_B, width, height);

    while(count<totalBytes) {
        for(i=0;i<height;i++) {
            for(j=0;j<width;j++) {
                Image2D_R[i][j]=Imagedata2[count];
                Image2D_G[i][j]=Imagedata2[count+1];
                Image2D_B[i][j]=Imagedata2[count+2];
                count=count+3;
            }
        }
    }

    int embeddedWidth = 4*width;
    int embeddedHeight = 2*height;
    unsigned char** bigImage_R = NULL;
    unsigned char** bigImage_G = NULL;
    unsigned char** bigImage_B = NULL;
    bigImage_R = create_2Darray(bigImage_R, 4*width, 2*height);
    bigImage_G = create_2Darray(bigImage_G, 4*width, 2*height);
    bigImage_B = create_2Darray(bigImage_B, 4*width, 2*height);
    unsigned char** outputEmbeddedImage = NULL;

    bigImage_B = embed_into_bigger_image(Image2D_B, bigImage_B, width, height);
    bigImage_R = embed_into_bigger_image(Image2D_R, bigImage_R, width, height);
    bigImage_G = embed_into_bigger_image(Image2D_G, bigImage_G, width, height);

    unsigned char* Imagedata = NULL;
    Imagedata = new unsigned char[embeddedWidth * embeddedHeight *bytesPerPixel];

    // Writing the embedded image into a file
    count =0;
    while (count < (embeddedWidth * embeddedHeight *bytesPerPixel)) {
        for (i = 0; i < embeddedHeight; i++) {
            for (j = 0; j < embeddedWidth; j++) {
                Imagedata[count] =   bigImage_R[i][j];
                Imagedata[count+1] = bigImage_G[i][j];
                Imagedata[count+2] = bigImage_B[i][j];
                count = count + 3;
            }
        }
    }
    char filename1[] = "Embedded_middle.raw";
    write_1Darray_to_file(Imagedata, 4*width*bytesPerPixel, 2*height, filename1);

    //Creating the homographic transformation for left image

    unsigned char *Imagedata1 = NULL;
    Imagedata1 = read_1Darray_from_file(width*bytesPerPixel, height, inputFilename1);
    count = 0;
    while(count<totalBytes) {
        for(i=0;i<height;i++) {
            for(j=0;j<width;j++) {
                Image2D_R[i][j]=Imagedata1[count];
                Image2D_G[i][j]=Imagedata1[count+1];
                Image2D_B[i][j]=Imagedata1[count+2];
                count=count+3;
            }
        }
    }

    long double* H_left = NULL;
    H_left = new long double[9] { 0.5437031003555, - 0.0225273759966, - 170.0585878150077,
                                  - 0.1298946058189, 0.6991203343690, - 104.0611976595122,
                                  - 0.0004751996361, - 0.0000636200573, 1.1660075342241 };
    double a, b, c;

    for (int i = 0; i < embeddedHeight; ++i) {
        for (int j = 0; j < embeddedWidth; ++j) {
            a = (long double)(j)*H_left[0] + (long double)(i)*H_left[1] + 1.0*H_left[2];
            b = (long double)(j)*H_left[3] + (long double)(i)*H_left[4] + 1.0*H_left[5];
            c = (long double)(j)*H_left[6] + (long double)(i)*H_left[7] + 1.0*H_left[8];
            a=a/c;
            b=b/c;
            if(a >= 0 && a < width && b>=0 && b<height) {
                bigImage_R[i][j] = Image2D_R[int(b)][int(a)];
                bigImage_G[i][j] = Image2D_G[int(b)][int(a)];
                bigImage_B[i][j] = Image2D_B[int(b)][int(a)];
            }
        }
    }

    count =0;
    while (count < (embeddedWidth * embeddedHeight *bytesPerPixel)) {
        for (i = 0; i < embeddedHeight; i++) {
            for (j = 0; j < embeddedWidth; j++) {
                Imagedata[count] =   bigImage_R[i][j];
                Imagedata[count+1] = bigImage_G[i][j];
                Imagedata[count+2] = bigImage_B[i][j];
                count = count + 3;
            }
        }
    }
    char filename2[] = "Embedded_left_middle.raw";
    write_1Darray_to_file(Imagedata, 4*width*bytesPerPixel, 2*height, filename2);


    // Transforming the right.raw image and stitching it to the k
    unsigned char *Imagedata3 = NULL;
    Imagedata3 = read_1Darray_from_file(width*bytesPerPixel, height, inputFilename3);
    count = 0;
    while(count<totalBytes) {
        for(i=0;i<height;i++) {
            for(j=0;j<width;j++) {
                Image2D_R[i][j]=Imagedata3[count];
                Image2D_G[i][j]=Imagedata3[count+1];
                Image2D_B[i][j]=Imagedata3[count+2];
                count=count+3;
            }
        }
    }

    long double* H_right = NULL;

    H_right = new long double[9] {1.167100669469, 0.008546635661, -1086.540059496630,
                             0.187368183407, 1.091074416275, -549.001284928812,
                             0.000620824966, 0.000015597095, 0.418219279425};

    for (int i = 0; i < embeddedHeight; ++i) {
        for (int j = 0; j < embeddedWidth; ++j) {
            a = (long double)(j)*H_right[0] + (long double)(i)*H_right[1] + 1.0*H_right[2];
            b = (long double)(j)*H_right[3] + (long double)(i)*H_right[4] + 1.0*H_right[5];
            c = (long double)(j)*H_right[6] + (long double)(i)*H_right[7] + 1.0*H_right[8];
            a=a/c;
            b=b/c;
            if(a >= 0 && a < width && b>=0 && b<height) {
                bigImage_R[i][j] = Image2D_R[int(b)][int(a)];
                bigImage_G[i][j] = Image2D_G[int(b)][int(a)];
                bigImage_B[i][j] = Image2D_B[int(b)][int(a)];
            }
        }
    }

    count =0;
    while (count < (embeddedWidth * embeddedHeight *bytesPerPixel)) {
        for (i = 0; i < embeddedHeight; i++) {
            for (j = 0; j < embeddedWidth; j++) {
                Imagedata[count] =   bigImage_R[i][j];
                Imagedata[count+1] = bigImage_G[i][j];
                Imagedata[count+2] = bigImage_B[i][j];
                count = count + 3;
            }
        }
    }
    char filename3[] = "Embedded_left_middle_right.raw";
    write_1Darray_to_file(Imagedata, 4*width*bytesPerPixel, 2*height, filename3);

    count=0;
    Imagedata2 = read_1Darray_from_file(width*bytesPerPixel, height, inputFilename2);
    while(count<totalBytes) {
        for(i=0;i<height;i++) {
            for(j=0;j<width;j++) {
                Image2D_R[i][j]=Imagedata2[count];
                Image2D_G[i][j]=Imagedata2[count+1];
                Image2D_B[i][j]=Imagedata2[count+2];
                count=count+3;
            }
        }
    }

    bigImage_B = embed_into_bigger_image(Image2D_B, bigImage_B, width, height);
    bigImage_R = embed_into_bigger_image(Image2D_R, bigImage_R, width, height);
    bigImage_G = embed_into_bigger_image(Image2D_G, bigImage_G, width, height);

    // Writing the embedded image into a file
    count =0;
    while (count < (embeddedWidth * embeddedHeight *bytesPerPixel)) {
        for (i = 0; i < embeddedHeight; i++) {
            for (j = 0; j < embeddedWidth; j++) {
                Imagedata[count] =   bigImage_R[i][j];
                Imagedata[count+1] = bigImage_G[i][j];
                Imagedata[count+2] = bigImage_B[i][j];
                count = count + 3;
            }
        }
    }
    char filename4[] = "Final_output_panorama.raw";
    write_1Darray_to_file(Imagedata, 4*width*bytesPerPixel, 2*height, filename4);

    return 0;
}



