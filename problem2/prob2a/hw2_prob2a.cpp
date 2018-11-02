// Author : Akshata Bhat
// USC ID : 9560895350
// Email : akshatab@usc.edu
// Submission Date : 3/4/2018


#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include "my_header_file.h"
using namespace std;

unsigned char** fixed_thresholding(unsigned char **Image, int width, int height){
    int i, j, threshold = 127;
    unsigned char **outputImage = new unsigned char *[height];
    for (i = 0; i < height; ++i) {
        outputImage[i] = new unsigned char[width];
        memset(outputImage[i], 0, width *sizeof(unsigned char));
    }
    for(i=0; i<height; i++) {
        for (j = 0; j < width; j++) {
            if (Image[i][j] < (unsigned char)threshold)
                outputImage[i][j] = (unsigned char)0;
            else
                outputImage[i][j] = (unsigned char)255;
        }
    }
    return outputImage;
}

unsigned char** random_thresholding(unsigned char **Image, int width, int height){
    int i, j, threshold;
    unsigned char **outputImage = new unsigned char *[height];
    for (i = 0; i < height; ++i) {
        outputImage[i] = new unsigned char[width];
        memset(outputImage[i], 0, width *sizeof(unsigned char));
    }

    srand(time(NULL));
    for(i=0; i<height; i++) {
        for (j = 0; j < width; j++) {
            threshold = rand() % 256;
            cout << threshold << endl;
            if ((int)Image[i][j] > threshold)
                outputImage[i][j] = (unsigned char)255;
            else
                outputImage[i][j] = (unsigned char)0;
        }
    }
    return outputImage;
}

unsigned char* display_thresholding_4_levels(unsigned char* inputImage, int width, int height) {
    int in_color_lvl = 256; // input color levels
    int out_color_lvl = 4; // output color levels
    int index = 0;
    int *sortedAddress = NULL;
    sortedAddress = new int[width * height];


    for (int j = 0; j < 256; ++j) {
        for (int i = 0; i < width * height; ++i) {
            if (inputImage[i] == (unsigned char)j) {
                sortedAddress[index] = i;
                index++;
            }
        }
    }

    unsigned char *new_Image = NULL;
    new_Image = new unsigned char[width * height];

    int binCount = 4; // No of bins
    int pixelsPerBin = (int) (width * height) / binCount;

    unsigned char Intensities[4] = {0, 85, 170, 255};

    int count = 0;
    index = 0;
    while (count<width * height) {
        for (int i = 0; i < pixelsPerBin; ++i) {
            new_Image[(sortedAddress[count])] = Intensities[index];
            count = count + 1;
        }
        index++;
        if (index == binCount)
            break;
    }
    return new_Image;
}


// Calculating the threshold matrix
void create_threshold_matrix(int N, int** IndexN, float **thresholdMatrix){
    int i,j;
    for (int i = 0; i < N ; ++i) {
        for (int j = 0; j < N ; ++j) {
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N ; ++j) {
            thresholdMatrix[i][j] = (float(IndexN[i][j]) + 0.5)/float(N*N);
        }
    }
}

// Function to create each quadrant of the Index matrix
void create_index_quadrant(int N, int row, int col, int add_val, int **outputIndex, int **prev_IndexN) {
    int xStart, yStart, col_start = col;
    xStart=row % (N/2);
    yStart=col % (N/2);
    for (int x = xStart; x < xStart+(N/2); ++x) {
        col=col_start;
        for (int y = yStart; y < yStart+(N/2); ++y) {
            outputIndex[row][col] = prev_IndexN[x][y]*4 + add_val;
            col++;
        }
        row++;
    }
}

// Calculating the Index matrix
int** create_index_matrix(int N, int **Index2, int **prev_IndexN){
    int i;
    int **outputIndex = new int *[N];
    for (i = 0; i < N; ++i) {
        outputIndex[i] = new int[N];
        memset(outputIndex[i], 0, N *sizeof(int));
    }
    int row=0,col=0, add_val; //xStart, yStart;
    while(row < N & col < N){
        // For the first quadrant of Index matrix
        row = 0; col = 0;
        add_val=Index2[0][0]; // add_val = 1
        create_index_quadrant(N, row, col, add_val, outputIndex, prev_IndexN);

        // For the second quadrant of Index matrix
        row = 0; col = N/2;
        add_val=Index2[0][1]; // add_val = 2
        create_index_quadrant(N, row, col, add_val, outputIndex, prev_IndexN);

        // For the third quadrant of Index matrix
        row = N/2; col = 0;
        add_val=Index2[1][0]; // add_val = 3
        create_index_quadrant(N, row, col, add_val, outputIndex, prev_IndexN);

        // For the fourth quadrant of Index matrix
        row = N/2; col = N/2;
        add_val=Index2[1][1]; // add_val = 0
        create_index_quadrant(N, row, col, add_val, outputIndex, prev_IndexN);
        break;
    }
    return outputIndex;
}
unsigned char** creat_halftone_image(int N, float** thresholdMatrix, unsigned char** inputArray, unsigned char** outputArray, int width, int height){
    int i, j, x,y, xLimit=0, yLimit=0, index=0;
    float array_value;
    for (i = 0; i < height; i=i+N) {
        for (j = 0; j < width ; j=j+N) {
            index =0;
            yLimit = j+N;
            xLimit = i+N;
            for (x = i; x < xLimit; ++x) {
                for (y = j; y < yLimit ; ++y) {
                    array_value = (float)int(inputArray[x][y])/255.0;
                    if(array_value > thresholdMatrix[x%N][y%N])
                        outputArray[x][y] = 255;
                    else
                        outputArray[x][y] = 0;
                    ++index;
                }
            }
        }
    }
    return outputArray;
}

void dithering_matrix(unsigned char **inputImage,unsigned char** outImage2D_2,
                                 unsigned char** outImage2D_4, unsigned char** outImage2D_8, int width, int height){
    // Calculating the Threshold matrix
    int **Index2 = NULL;
    Index2 = create_2Darray(Index2, 2, 2);
    Index2[0][0]=1;
    Index2[0][1]=2;
    Index2[1][0]=3;
    Index2[1][1]=0;

    int **Index4 = NULL;
    Index4 = create_2Darray(Index4, 4, 4);
    Index4 = create_index_matrix(4, Index2, Index2);

    int **Index8 = NULL;
    Index8 = create_2Darray(Index8, 8, 8);
    Index8 = create_index_matrix(8, Index2, Index4);

    float **thresholdMatrix2 = NULL;
    thresholdMatrix2 = create_2Darray(thresholdMatrix2, 2, 2);
    create_threshold_matrix(2, Index2, thresholdMatrix2);
    outImage2D_2 = create_2Darray(outImage2D_2, width, height);
    outImage2D_2 = creat_halftone_image(2, thresholdMatrix2, inputImage, outImage2D_2,width, height);

    float **thresholdMatrix4 = NULL;
    thresholdMatrix4 = create_2Darray(thresholdMatrix4, 4, 4);
    create_threshold_matrix(4, Index4, thresholdMatrix4);
    outImage2D_4 = create_2Darray(outImage2D_4, width, height);
    outImage2D_4 = creat_halftone_image(4, thresholdMatrix4, inputImage, outImage2D_4, width, height);

    float **thresholdMatrix8 = NULL;
    thresholdMatrix8 = create_2Darray(thresholdMatrix8, 8, 8);
    create_threshold_matrix(8, Index8, thresholdMatrix8);
    outImage2D_8 = create_2Darray(outImage2D_8, width, height);
    outImage2D_8 = creat_halftone_image(8, thresholdMatrix8, inputImage, outImage2D_8,width, height);
}

int main(int argc, char *argv[]) {
    FILE *fptr1, *fptr2;

    if (argc != 5) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "Syntax : hw2_prob2a <input_image.raw> <width> <height> <bytes_per_pixel>" << endl;
        return 0;
    }

    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    int bytesPerPixel = atoi(argv[4]);
    int totalBytes = width * height * bytesPerPixel;

    unsigned char Imagedata[totalBytes];

    if (!(fptr1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    //Reading the image data into a 2D array
    int i, j, count = 0;
    unsigned char **Image2D = NULL;
    Image2D = create_2Darray(Image2D, width, height);
    while (count < totalBytes) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                Image2D[i][j] = Imagedata[count];
                count = count + 1;
            }
        }
    }

    // Fixed Thresholding

    unsigned char **outputImage2D = NULL;
    outputImage2D = fixed_thresholding(Image2D, width, height);
    count =0;
    while (count < totalBytes) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                Imagedata[count] = outputImage2D[i][j];
                count = count + 1;
            }
        }
    }

    if (!(fptr2 = fopen("Fixed_threshold_output.raw", "wb"))) {
        cout << "Cannot open file: Fixed_threshold_output.raw" << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), totalBytes, fptr2);
    fclose(fptr2);


    // Random Thresholding

    memset(Imagedata, 0, sizeof(unsigned char));
    outputImage2D = random_thresholding(Image2D, width, height);
    count =0;
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                Imagedata[count] = outputImage2D[i][j];
                count ++;
            }
        }

    if (!(fptr2 = fopen("Random_threshold_output.raw", "wb"))) {
        cout << "Cannot open file: Random_threshold_output.raw" << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), totalBytes, fptr2);
    fclose(fptr2);

    // Dithering for a 2x2, 4x4 and 8x8 matrix

    unsigned char** outImage2D_2 = NULL;
    unsigned char** outImage2D_4 = NULL;
    unsigned char** outImage2D_8 = NULL;
    outImage2D_2 = create_2Darray(outImage2D_2, width, height);
    outImage2D_4 = create_2Darray(outImage2D_4, width, height);
    outImage2D_8 = create_2Darray(outImage2D_8, width, height);

    int **Index2 = NULL;
    Index2 = create_2Darray(Index2, 2, 2);
    Index2[0][0]=1;
    Index2[0][1]=2;
    Index2[1][0]=3;
    Index2[1][1]=0;

    int **Index4 = NULL;
    Index4 = create_index_matrix(4, Index2, Index2);

    int **Index8 = NULL;
    Index8 = create_index_matrix(8, Index2, Index4);

    float **thresholdMatrix2 = NULL;
    thresholdMatrix2 = create_2Darray(thresholdMatrix2, 2, 2);
    create_threshold_matrix(2, Index2, thresholdMatrix2);
    outImage2D_2 = create_2Darray(outImage2D_2, width, height);
    creat_halftone_image(2, thresholdMatrix2, Image2D, outImage2D_2,width, height);

    float **thresholdMatrix4 = NULL;
    thresholdMatrix4 = create_2Darray(thresholdMatrix4, 4, 4);
    create_threshold_matrix(4, Index4, thresholdMatrix4);
    outImage2D_4 = create_2Darray(outImage2D_4, width, height);
    creat_halftone_image(4, thresholdMatrix4, Image2D, outImage2D_4, width, height);

    float **thresholdMatrix8 = NULL;
    thresholdMatrix8 = create_2Darray(thresholdMatrix8, 8, 8);
    create_threshold_matrix(8, Index8, thresholdMatrix8);

    outImage2D_8 = create_2Darray(outImage2D_8, width, height);
    creat_halftone_image(8, thresholdMatrix8, Image2D, outImage2D_8,width, height);
    //dithering_matrix(Image2D, outImage2D_2, outImage2D_4, outImage2D_8, width, height);
    int N=512;
    for (int i = 0; i < N ; ++i) {
        for (int j = 0; j < N ; ++j) {
        }
    }

    count = 0;
    unsigned char Imagedata_2[totalBytes];
    unsigned char Imagedata_4[totalBytes];
    unsigned char Imagedata_8[totalBytes];
    while (count < totalBytes) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                Imagedata_2[count] = outImage2D_2[i][j];
                Imagedata_4[count] = outImage2D_4[i][j];
                Imagedata_8[count] = outImage2D_8[i][j];
                count = count + 1;
            }
        }
    }
    if (!(fptr2 = fopen("Dithering_matrix_2x2.raw", "wb"))) {
        cout << "Cannot open file: Dithering_matrix_2x2.raw" << endl;
        exit(1);
    }
    fwrite(Imagedata_2, sizeof(unsigned char), totalBytes, fptr2);
    fclose(fptr2);

    if (!(fptr2 = fopen("Dithering_matrix_4x4.raw", "wb"))) {
        cout << "Cannot open file: Dithering_matrix_2x2.raw" << endl;
        exit(1);
    }
    fwrite(Imagedata_4, sizeof(unsigned char), totalBytes, fptr2);
    fclose(fptr2);

    if (!(fptr2 = fopen("Dithering_matrix_8x8.raw", "wb"))) {
        cout << "Cannot open file: Dithering_matrix_8x8.raw" << endl;
        exit(1);
    }
    fwrite(Imagedata_8, sizeof(unsigned char), totalBytes, fptr2);
    fclose(fptr2);


    // Display 4 intensity levels
    if (!(fptr1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    unsigned char* output_4intensities = NULL;
    output_4intensities = display_thresholding_4_levels(Imagedata, width, height);

    if (!(fptr2 = fopen("Display_4_Thresholding_levels.raw", "wb"))) {
        cout << "Cannot open file: Display_4_Thresholding_levels.raw" << endl;
        exit(1);
    }
    fwrite(output_4intensities, sizeof(unsigned char), width*height, fptr2);
    fclose(fptr2);

    return 0;
}
