// Author : Akshata Bhat
// USC ID : 9560895350
// Email : akshatab@usc.edu
// Submission Date : 3/4/2018


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

unsigned char** Floyd_Steinberg_method_color_diff(unsigned char** origImage, unsigned char** newImage, int width, int height)
{
    int error=0;
    for (int i = 0; i < height ; ++i) {
        if(i%2 == 0){
            for (int j = 0; j < width; ++j) {
                error = int(origImage[i][j]) - int(newImage[i][j]);
                if(j+1 != width)
                    origImage[i][j + 1] = (unsigned char) (float(origImage[i][j + 1]) + float(error) * (7.0 / 16.0));
                if (i+1 != height && j+1 != width)
                    origImage[i + 1][j + 1] = (unsigned char) (float(origImage[i + 1][j + 1]) + float(error) * (1.0 / 16.0));
                if (i + 1 != height)
                    origImage[i + 1][j] = (unsigned char) (float(origImage[i + 1][j]) + float(error) * (5.0 / 16.0));
                if (j - 1 != -1 && i+1 != height)
                    origImage[i + 1][j - 1] = (unsigned char) (float(origImage[i+1][j - 1]) + float(error) * (3.0 / 16.0));
            }
        }
        else{
            for (int j = width-1; j > 0; --j) {
                error = int(origImage[i][j]) - int(newImage[i][j]);
                if (j-1 != -1)
                    origImage[i][j-1] = (unsigned char)(float(origImage[i][j-1]) + float(error) * (7.0 / 16.0));
                if (j-1 != -1 && i+1 != height)
                    origImage[i+1][j-1] = (unsigned char)(float(origImage[i+1][j-1]) + float(error) * (1.0 / 16.0));
                if (i+1 != height)
                    origImage[i+1][j] = (unsigned char)(float(origImage[i+1][j]) + float(error) * (5.0 / 16.0));
                if (i+1 != height && j+1 != width)
                    origImage[i+1][j+1] = (unsigned char)(float(origImage[i+1][j+1]) + float(error) * (3.0 / 16.0));
            }

        }

    }
    return origImage;
}

int pyramid_MBVQ(int R, int G, int B)
{
    if((R+G) > 255){
        if((G+B) > 255){
            if((R+G+B) > 510)
                return 1;
            else
                return 2;
        }
        else
            return 3;
    }
    else{
        if(!((G+B) > 255)){
            if(!(R+G+B) > 255)
                return 4;
            else
                return 5;
        }
        else
            return 6;
    }
}

int main(int argc, char *argv[]) {
    FILE* fptr1;

    if (argc != 5){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "Syntax : hw2_prob2c <input_img.raw> <width> <height> <bytes per pixel>" << endl;
        return 0;
    }

    int width= atoi(argv[2]);
    int height= atoi(argv[3]);
    int bytesPerPixel = atoi(argv[4]);
    int totalBytes=width*height*bytesPerPixel;

    unsigned char* Imagedata = NULL;
    Imagedata = new unsigned char[totalBytes];
    memset(Imagedata,0,totalBytes);

    if (!(fptr1 = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    unsigned char** Image2D_R = NULL;
    unsigned char** Image2D_G = NULL;
    unsigned char** Image2D_B = NULL;
    Image2D_R = create_2Darray(Image2D_R, width, height);
    Image2D_G = create_2Darray(Image2D_G, width, height);
    Image2D_B = create_2Darray(Image2D_B, width, height);

    int i,j,count=0;
    while(count<totalBytes)
    {
        for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                Image2D_R[i][j]=Imagedata[count];
                Image2D_G[i][j]=Imagedata[count+1];
                Image2D_B[i][j]=Imagedata[count+2];
                count=count+3;
            }
        }
    }

    unsigned char** Image2D_C = NULL;
    unsigned char** Image2D_M = NULL;
    unsigned char** Image2D_Y = NULL;
    Image2D_C = create_2Darray(Image2D_C, width, height);
    Image2D_M = create_2Darray(Image2D_M, width, height);
    Image2D_Y = create_2Darray(Image2D_Y, width, height);

    for(i=0;i<width;i++)
    {
        for(j=0;j<height;j++)
        {
            Image2D_C[i][j]=(1 - (int(Image2D_R[i][j]) / 255.0)) * 255;
            Image2D_M[i][j]=(1 - (int(Image2D_G[i][j]) / 255.0)) * 255;
            Image2D_Y[i][j]=(1 - (int(Image2D_B[i][j]) / 255.0)) * 255;
            //Grayscale_CMY[i][j]=(0.21 * Image2D_C[i][j]) + (0.72 * Image2D_M[i][j]) + (0.07 * Image2D_Y[i][j]);
        }
    }

    ////Floyd Steinberg Diffusion method
    unsigned char **outputFlyod_Cyan = NULL;
    outputFlyod_Cyan = Floyd_Steinberg_method(Image2D_C, width, height);
    unsigned char **outputFlyod_Magenta = NULL;
    outputFlyod_Magenta = Floyd_Steinberg_method(Image2D_M, width, height);
    unsigned char **outputFlyod_Yellow = NULL;
    outputFlyod_Yellow = Floyd_Steinberg_method(Image2D_Y, width, height);

    for(i=0;i<width;i++)
    {
        for(j=0;j<height;j++)
        {
            Image2D_R[i][j]=(unsigned char)((int)(1 - (int(outputFlyod_Cyan[i][j]) / 255.0)) * 255);
            Image2D_G[i][j]=(unsigned char)((int)(1 - (int(outputFlyod_Magenta[i][j]) / 255.0)) * 255);
            Image2D_B[i][j]=(unsigned char)((int)(1 - (int(outputFlyod_Yellow[i][j]) / 255.0)) * 255);
            //Grayscale_CMY[i][j]=(0.21 * Image2D_C[i][j]) + (0.72 * Image2D_M[i][j]) + (0.07 * Image2D_Y[i][j]);
        }
    }


    count = 0;
    while(count<width*height*3)
    {
        for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                Imagedata[count] =   Image2D_R[i][j];
                Imagedata[count+1] = Image2D_G[i][j];
                Imagedata[count+2] = Image2D_B[i][j];
                count=count+3;
            }
        }
    }

    if (!(fptr1=fopen("CMY_output.raw","wb"))) {
        cout << "Cannot open file." << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char),width*height*3, fptr1);
    fclose(fptr1);


    // Color diffusion

    memset(Imagedata,0,totalBytes* sizeof(unsigned char));

    if (!(fptr1 = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    count=0;
    while(count<totalBytes)
    {
        for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                Image2D_R[i][j]=Imagedata[count];
                Image2D_G[i][j]=Imagedata[count+1];
                Image2D_B[i][j]=Imagedata[count+2];
                count=count+3;
            }
        }
    }

    unsigned char** new_Image2D_C = NULL;
    unsigned char** new_Image2D_M = NULL;
    unsigned char** new_Image2D_Y = NULL;
    new_Image2D_C = create_2Darray(new_Image2D_C, width, height);
    new_Image2D_M = create_2Darray(new_Image2D_M, width, height);
    new_Image2D_Y = create_2Darray(new_Image2D_Y, width, height);

    // C=0, M=1, Y=2, R=3, G=4, B=5, W=6, K=7
    int colors[8][3] = {{0, 255, 0}, {255, 0, 0}, {0, 0, 255}, {255, 0, 255}, {0, 255, 255}, {255, 255, 0}, {0, 0, 0}, {255, 255, 255}};
    int closest_match;
    double* quad_colors = NULL;
    quad_colors = new double[4];
    int quadruple=0, m;
    double diff;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            quadruple = pyramid_MBVQ(Image2D_R[i][j], Image2D_G[i][j], Image2D_B[i][j]);
            switch (quadruple) {
                case 1: {// CMYW C=0, M=1, Y=2, R=3, G=4, B=5, W=6, K=7
                    memset(quad_colors, 0, 4*sizeof(float));
                    int combo1[4] = {0, 1, 2, 6};
                    for (m = 0; m < 4; m++) {
                        //cout << combo1[m] << endl;
                        diff = sqrt(pow((Image2D_C[i][j] - colors[combo1[m]][0]), 2) +
                                    pow((Image2D_M[i][j] - colors[combo1[m]][1]), 2) +
                                    pow((Image2D_Y[i][j] - colors[combo1[m]][2]), 2));
                        quad_colors[m] = diff;
                    }
                    closest_match = position_of_minimum_value(quad_colors, 4);

                    new_Image2D_C[i][j] = (unsigned char) colors[combo1[closest_match]][0];
                    new_Image2D_M[i][j] = (unsigned char) colors[combo1[closest_match]][1];
                    new_Image2D_Y[i][j] = (unsigned char) colors[combo1[closest_match]][2];
                }
                    break;

                case 2: {// MYGC C=0, M=1, Y=2, R=3, G=4, B=5, W=6, K=7
                    memset(quad_colors, 0, 4*sizeof(float));
                    int combo2[4] = {1, 2, 4, 0};
                    for (m = 0; m < 4; m++) {
                        diff = sqrt(pow((Image2D_C[i][j] - colors[combo2[m]][0]), 2) +
                                    pow((Image2D_M[i][j] - colors[combo2[m]][1]), 2) +
                                    pow((Image2D_Y[i][j] - colors[combo2[m]][2]), 2));
                        quad_colors[m] = diff;
                    }
                    closest_match = position_of_minimum_value(quad_colors, 4);

                    new_Image2D_C[i][j] = (unsigned char) colors[combo2[closest_match]][0];
                    new_Image2D_M[i][j] = (unsigned char) colors[combo2[closest_match]][1];
                    new_Image2D_Y[i][j] = (unsigned char) colors[combo2[closest_match]][2];
                }
                    break;

                case 3:
                {// RGMY C=0, M=1, Y=2, R=3, G=4, B=5, W=6, K=7
                    memset(quad_colors, 0, 4*sizeof(float));
                    int combo3[4] = {3, 4, 1, 2};
                    for (m = 0; m < 4; m++) {
                        diff = sqrt(pow((Image2D_C[i][j] - colors[combo3[m]][0]), 2) +
                                    pow((Image2D_M[i][j] - colors[combo3[m]][1]), 2) +
                                    pow((Image2D_Y[i][j] - colors[combo3[m]][2]), 2));
                        quad_colors[m] = diff;
                    }
                    closest_match = position_of_minimum_value(quad_colors, 4);

                    new_Image2D_C[i][j] = (unsigned char)colors[combo3[closest_match]][0];
                    new_Image2D_M[i][j] = (unsigned char)colors[combo3[closest_match]][1];
                    new_Image2D_Y[i][j] = (unsigned char)colors[combo3[closest_match]][2];
                }
                    break;

                case 4:
                {// KRGB C=0, M=1, Y=2, R=3, G=4, B=5, W=6, K=7
                    memset(quad_colors, 0, 4*sizeof(float));
                    int combo4[4] = {7, 3, 4, 5};
                    for (m = 0; m < 4; m++) {
                        diff = sqrt(pow((Image2D_C[i][j] - colors[combo4[m]][0]), 2) +
                                    pow((Image2D_M[i][j] - colors[combo4[m]][1]), 2) +
                                    pow((Image2D_Y[i][j] - colors[combo4[m]][2]), 2));
                        quad_colors[m] = diff;
                    }
                    closest_match = position_of_minimum_value(quad_colors, 4);

                    new_Image2D_C[i][j] = (unsigned char)colors[combo4[closest_match]][0];
                    new_Image2D_M[i][j] = (unsigned char)colors[combo4[closest_match]][1];
                    new_Image2D_Y[i][j] = (unsigned char)colors[combo4[closest_match]][2];
                }
                    break;

                case 5:
                { // RGBM C=0, M=1, Y=2, R=3, G=4, B=5, W=6, K=7
                    memset(quad_colors, 0, 4*sizeof(float));
                    int combo5[4] = {3, 4, 5, 1};
                    for (m = 0; m < 4; m++) {
                        diff = sqrt(pow((Image2D_C[i][j] - colors[combo5[m]][0]), 2) +
                                    pow((Image2D_M[i][j] - colors[combo5[m]][1]), 2) +
                                    pow((Image2D_Y[i][j] - colors[combo5[m]][2]), 2));
                        quad_colors[m] = diff;
                    }
                    closest_match = position_of_minimum_value(quad_colors, 4);
                    new_Image2D_C[i][j] = (unsigned char)colors[combo5[closest_match]][0];
                    new_Image2D_M[i][j] = (unsigned char)colors[combo5[closest_match]][1];
                    new_Image2D_Y[i][j] = (unsigned char)colors[combo5[closest_match]][2];
                }
                    break;

                case 6:
                { //CMGB C=0, M=1, Y=2, R=3, G=4, B=5, W=6, K=7
                    memset(quad_colors, 0, 4*sizeof(float));
                    int combo6[] = {0, 1, 4, 5};
                    for (m = 0; m < 4; m++) {
                        diff = sqrt(pow((Image2D_C[i][j] - colors[combo6[m]][0]), 2) +
                                    pow((Image2D_M[i][j] - colors[combo6[m]][1]), 2) +
                                    pow((Image2D_Y[i][j] - colors[combo6[m]][2]), 2));
                        quad_colors[m] = diff;
                    }
                    closest_match = position_of_minimum_value(quad_colors, 4);

                    new_Image2D_C[i][j] = (unsigned char)colors[combo6[closest_match]][0];
                    new_Image2D_M[i][j] = (unsigned char)colors[combo6[closest_match]][1];
                    new_Image2D_Y[i][j] = (unsigned char)colors[combo6[closest_match]][2];
                }
                    break;
                default:
                    break;
            }
        }
    }


    unsigned char** output_Image2D_C = NULL;
    unsigned char** output_Image2D_M = NULL;
    unsigned char** output_Image2D_Y = NULL;
    output_Image2D_C = Floyd_Steinberg_method_color_diff(Image2D_C,  new_Image2D_C, width, height);
    output_Image2D_M = Floyd_Steinberg_method_color_diff(Image2D_M,  new_Image2D_M, width, height);
    output_Image2D_Y = Floyd_Steinberg_method_color_diff(Image2D_Y,  new_Image2D_Y, width, height);

    unsigned char* Imageout = NULL;
    Imageout = convert_2Dto1D(output_Image2D_C, width, height);
    if (!(fptr1=fopen("Cyan_output.raw","wb"))) {
        cout << "Cannot open file." << endl;
        exit(1);
    }
    fwrite(Imageout, sizeof(unsigned char),width*height, fptr1);
    fclose(fptr1);

    for(i=0;i<width;i++)
    {
        for(j=0;j<height;j++)
        {
            Image2D_R[i][j]=(unsigned char)((int)(1 - (int(output_Image2D_C[i][j]) / 255.0)) * 255);
            Image2D_G[i][j]=(unsigned char)((int)(1 - (int(output_Image2D_M[i][j]) / 255.0)) * 255);
            Image2D_B[i][j]=(unsigned char)((int)(1 - (int(output_Image2D_Y[i][j]) / 255.0)) * 255);
            //Grayscale_CMY[i][j]=(0.21 * Image2D_C[i][j]) + (0.72 * Image2D_M[i][j]) + (0.07 * Image2D_Y[i][j]);
        }
    }

    memset(Imagedata,0,totalBytes);
    count = 0;
    while(count<width*height*3)
    {
        for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                Imagedata[count] =   Image2D_R[i][j];
                Imagedata[count+1] = Image2D_G[i][j];
                Imagedata[count+2] = Image2D_B[i][j];
                count=count+3;
            }
        }
    }

    if (!(fptr1=fopen("Color_diffusion_output.raw","wb"))) {
        cout << "Cannot open file." << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char),width*height*3, fptr1);
    fclose(fptr1);

    return 0;
}