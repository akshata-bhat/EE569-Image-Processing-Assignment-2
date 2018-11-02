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


//Function to convert from values 0,1 to 0,255
unsigned char** binary_to_monochrome(unsigned char** outputImage, int width, int height){
    unsigned char **writeImage = NULL;
    writeImage = create_2Darray(writeImage, width,height);
    for (int i = 0; i < height ; ++i) {
        for (int j = 0; j < width ; ++j) {
            if(outputImage[i][j] == '1'){
                writeImage[i][j] = (unsigned char)255;
            }
            else
                writeImage[i][j] = (unsigned char)0;
        }
    }
    return writeImage;
}

//Function to convert from values 0, 255 to 0, 1
unsigned char** monochrome_to_binary(unsigned char** origImage, int width, int height){
    unsigned char **binImage = NULL;
    binImage = create_2Darray(binImage, width,height);
    int threshold=127, count=0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(origImage[i][j] > threshold){
                binImage[i][j] = '1';
            }
            else {
                binImage[i][j] = '0';
                count ++;
            }
        }
    }
    return binImage;
}

//Function to convert black pixels to white and vice versa
unsigned char** invert_image(unsigned char** origImage, int width, int height){
    unsigned char **invertedImage = NULL;
    invertedImage = create_2Darray(invertedImage, width, height);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(origImage[i][j] == '1')
                invertedImage[i][j] = '0';
            else if(origImage[i][j] == '0')
                invertedImage[i][j] = '1';
        }
    }
    return invertedImage;
}


int bond_calculator(unsigned char* image, int N){
    int bond=0, k;
    for (k = 0; k < N*N; ++k) {
        if (image[k] == '1')
            if (k == 1 | k == 3 | k == 5 | k == 7)
                bond = bond + 2;
            else if(k == 0 | k == 2 | k == 6 | k == 8)
                bond = bond + 1;
    }
    return bond;
}

string char_to_string_convertor(unsigned char* image, int N){
    string temp_string="";
    for (int i = 0; i < N*N; ++i) {
        temp_string += image[i];
    }
    return temp_string;
}

int skeletonize_hit_calculator(string imageMask, int bond){
    string bond4a[4] = {"010011000", "010110000", "000110010", "000011010"};
    string bond4b[4] = {"001011001", "111010000", "100110100", "000010111"};
    string bond5[8] = {"110011000", "010011001", "011110000", "001011010", "011011000","110110000", "000110110", "000011011"};
    string bond6a[2] = {"011011001", "011110100"};
    string bond6b[8] = {"111011000", "011011001", "111110000", "110110100", "100110110", "000110111", "000011111", "001011011"};
    string bond7[4]	= {"111011001", "111110100", "100110111", "001011111"};
    string bond8[4]	= {"011011011", "111111000", "110110110", "000111111"};
    string bond9[8]	= {"111011011", "011011111", "111111100", "111111001", "111110110", "110110111", "100111111", "001111111"};
    string bond10[4] 	= {"111011111", "111111101", "111110111", "101111111"};
    string bond11[4] 	= {"111111011", "111111110", "110111111", "011111111"};
    int arrLength;

    switch(bond) {
        case 4 :
            arrLength = sizeof(bond4a)/sizeof(bond4a[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond4a[k] == imageMask)	return 1;}

            arrLength = sizeof(bond4b)/sizeof(bond4b[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond4b[k] == imageMask)	return 1;}
            break;

        case 5 :
            arrLength = sizeof(bond5)/sizeof(bond5[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond5[k] == imageMask)	return 1;}
            break;

        case 6 :
            arrLength = sizeof(bond6a)/sizeof(bond6a[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond6a[k] == imageMask)	return 1;}

            arrLength = sizeof(bond6b)/sizeof(bond6b[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond6b[k] == imageMask)	return 1;}
            break;

        case 7 :
            arrLength = sizeof(bond7)/sizeof(bond7[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond7[k] == imageMask)	return 1;}
            break;

        case 8 :
            arrLength = sizeof(bond8)/sizeof(bond8[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond8[k] == imageMask)	return 1;}
            break;

        case 9 :
            arrLength = sizeof(bond9)/sizeof(bond9[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond9[k] == imageMask)	return 1;}
            break;

        case 10 :
            arrLength = sizeof(bond10)/sizeof(bond10[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond10[k] == imageMask)	return 1;}
            break;

        case 11 :
            arrLength = sizeof(bond11)/sizeof(bond11[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond11[k] == imageMask)	return 1;}
            break;

        default:
            return 0;
    }
    return 0;
}

int shrink_hit_calculator(string imageMask, int bond){
    string bond1[4] = {"001010000", "100010000", "000010100", "000010001"};
    string bond2[4] = {"000011000", "010010000", "000110000", "000010010"};
    string bond3[8] = {"001011000", "011010000", "110010000", "100110000", "000110100", "000010110", "000010011", "000011001"};
    string bond4b[4] = {"001011001", "111010000", "100110100", "000010111"};
    string bond5[8] = {"110011000", "010011001", "011110000", "001011010", "011011000","110110000", "000110110", "000011011"};
    string bond6a[2] = {"110011001", "011110100"};
    string bond6b[8] = {"111011000", "011011001", "111110000", "110110100", "100110110", "000110111", "000011111", "001011011"};
    string bond7[4]	= {"111011001", "111110100", "100110111", "001011111"};
    string bond8[4]	= {"011011011", "111111000", "110110110", "000111111"};
    string bond9[8]	= {"111011011", "011011111", "111111100", "111111001", "111110110", "110110111", "100111111", "001111111"};
    string bond10[4] 	= {"111011111", "111111101", "111110111", "101111111"};
    int arrLength;

    switch(bond) {
        case 1 :
            arrLength = sizeof(bond1)/sizeof(bond1[0]);
            for (int k = 0; k < arrLength; ++k) {
                if(bond1[k] == imageMask)   return 1;}
            break;
        case 2 :
            arrLength = sizeof(bond2)/sizeof(bond2[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond2[k] == imageMask)	return 1;}
            break;

        case 3 :
            arrLength = sizeof(bond3)/sizeof(bond3[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond3[k] == imageMask)	return 1;}
            break;

        case 4 :
            arrLength = sizeof(bond4b)/sizeof(bond4b[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond4b[k] == imageMask)	return 1;}
            break;

        case 5 :
            arrLength = sizeof(bond5)/sizeof(bond5[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond5[k] == imageMask)	return 1;}
            break;

        case 6 :
            arrLength = sizeof(bond6a)/sizeof(bond6a[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond6a[k] == imageMask)	return 1;}

            arrLength = sizeof(bond6b)/sizeof(bond6b[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond6b[k] == imageMask)	return 1;}
            break;

        case 7 :
            arrLength = sizeof(bond7)/sizeof(bond7[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond7[k] == imageMask)	return 1;}
            break;

        case 8 :
            arrLength = sizeof(bond8)/sizeof(bond8[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond8[k] == imageMask)	return 1;}
            break;

        case 9 :
            arrLength = sizeof(bond9)/sizeof(bond9[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond9[k] == imageMask)	return 1;}
            break;

        case 10 :
            arrLength = sizeof(bond10)/sizeof(bond10[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond10[k] == imageMask)	return 1;}
            break;

        default:
            return 0;
    }
    return 0;
}

int thinning_hit_calculator(string imageMask, int bond){
    string bond4a[4] = {"010011000", "010110000", "000110010", "000011010"};
    string bond4b[4] = {"001011001", "111010000", "100110100", "000010111"};
    string bond5[8] = {"110011000", "010011001", "011110000", "001011010", "011011000","110110000", "000110110", "000011011"};
    string bond6a[2] = {"011011001", "011110100"};
    string bond6b[8] = {"111011000", "011011001", "111110000", "110110100", "100110110", "000110111", "000011111", "001011011"};
    string bond7[4]	= {"111011001", "111110100", "100110111", "001011111"};
    string bond8[4]	= {"011011011", "111111000", "110110110", "000111111"};
    string bond9[8]	= {"111011011", "011011111", "111111100", "111111001", "111110110", "110110111", "100111111", "001111111"};
    string bond10[4] = {"111011111", "111111101", "111110111", "101111111"};
    //string bond11[4] = {"111111011", "111111110", "110111111", "011111111"};
    int arrLength;

    switch(bond) {
        case 4 :
            arrLength = sizeof(bond4a)/sizeof(bond4a[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond4a[k] == imageMask)	return 1;}

            arrLength = sizeof(bond4b)/sizeof(bond4b[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond4b[k] == imageMask)	return 1;}
            break;

        case 5 :
            arrLength = sizeof(bond5)/sizeof(bond5[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond5[k] == imageMask)	return 1;}
            break;

        case 6 :
            arrLength = sizeof(bond6a)/sizeof(bond6a[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond6a[k] == imageMask)	return 1;}

            arrLength = sizeof(bond6b)/sizeof(bond6b[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond6b[k] == imageMask)	return 1;}
            break;

        case 7 :
            arrLength = sizeof(bond7)/sizeof(bond7[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond7[k] == imageMask)	return 1;}
            break;

        case 8 :
            arrLength = sizeof(bond8)/sizeof(bond8[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond8[k] == imageMask)	return 1;}
            break;

        case 9 :
            arrLength = sizeof(bond9)/sizeof(bond9[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond9[k] == imageMask)	return 1;}
            break;

        case 10 :
            arrLength = sizeof(bond10)/sizeof(bond10[0]);
            for (int k = 0; k < arrLength; ++k)
            {if(bond10[k] == imageMask)	return 1;}
            break;

        default:
            return 0;
    }
    return 0;
}

int Stage2_shrink_thin_hit_calculator(string image){
    int hit_value;
    string shrink_thin[37] = {"00m0m0000", "m000m0000",//spur
                              "0000m00m0", "0000mm000", //Single connection
                              "00m0mm000", "0mm0m0000","mm00m0000", "m00mm0000",//L cluster
                              "000mm0m00", "0000m0mm0", "0000m00mm", "0000mm00m",//L cluster
                              "0mmmm0000", "mm00mm000", "0m00mm00m", "00m0mm0m0",//4-connected offset
                              "0am0mbm00", "mb0am000m", "00mam0mb0", "m000mb0am", //Spur corner cluster
                              "mmdmmdddd",//Corner Cluster
                              "dm0mmmd00", "0mdmmm00d", "00dmmm0md", "d00mmmdm0",//Tee Branch
                              "dmdmm00m0", "0m0mm0dmd", "0m00mmdmd", "dmd0mm0m0",//Tee Branch
                              "mdmdmdabc", "mdcdmbmda", "cbadmdmdm", "admbmdcdm",//Vee Branch
                              "dm00mmm0d", "0mdmm0d0m", "dommm00md", "m0d0mmdm0"};//Diagonal
    char temp; int abc_found;
    for (int i = 0; i < 37; ++i)
    {
        hit_value=1;
        string mask = shrink_thin[i];
        temp='0';
        abc_found=0;
        for (int j = 0; j < 9; ++j)
        {
            if (mask[j]=='a' || mask[j]=='b' || mask[j]=='c')
            {
                temp=(unsigned char)(temp | image[j]);
                abc_found++;
                continue;
            }
            if(mask[j]=='d')
               continue;
            if(mask[j]=='m'){
                if (image[j]=='1')
                    continue;
                else{
                    hit_value=0;
                    break;
                }
            }
            if (mask[j]!=image[j]){
                hit_value=0;
                break;
            }
        }
        if(temp!='1' && abc_found>0)
            hit_value=0;
        if(hit_value == 1){
            return 1;
        }
    }
    return 0;
}

int Stage2_skeletonize_hit_calculator(string image){
    int hit_value=1;
    string skeletonize[26] = {"0000m000m", "0000m0m00", "00m0m0000", "m000m0000",//spur
                              "0000m00m0", "0000mm000", "000mm0000", "0m00m0000",//4-connection
                              "0m00mm000", "0m0mm0000", "0000mm0m0", "000mm00m0",//L-corner
                              "mmdmmdddd", "ddddmmdmm", //corner cluster
                              "dmdmmmddd", "dmdmmddmd", "dddmmmdmd", "dmddmmdmd",//Tee Branch
                              "mdmdmdabc", "mdcdmbmda", "cbadmdmdm", "admbmdcdm",//Vee branch
                              "dm00mmm0d", "0mdmm0d0m", "d0mmm00md", "m0d0mmdm0"};//Diagonal Branch
    char temp; int abc_found;
    for (int i = 0; i < 26; ++i)
    {
        hit_value=1;
        string mask = skeletonize[i];
        temp='0';
        abc_found=0;
        for (int j = 0; j < 9; ++j)
        {
            if (mask[j]=='a' || mask[j]=='b' || mask[j]=='c')
            {
                //cout << mask[j]<< endl;
                temp=(unsigned char)(temp | image[j]);
                abc_found++;
                continue;
            }
            if(mask[j]=='d')
                continue;
            if(mask[j]=='m'){
                if (image[j]=='1')
                    continue;
                else{
                    hit_value=0;
                    break;
                }
            }
            if (mask[j]!=image[j]){
                hit_value=0;
                break;
            }
        }
        if(temp!='1' && abc_found>0)
            hit_value=0;
        if(hit_value == 1){
            return 1;
        }
    }
    return 0;
}

unsigned char** Stage2_unconditional_skeletonize(unsigned char** firstImage, unsigned char** binaryImage, int width, int height){
    unsigned char **secondImage = NULL;
    secondImage = create_2Darray(secondImage, width,height);
    int i, j, x, y, N=3, xStart=0, yStart=0, xLimit=0, yLimit=0, index=0, row, col, bond=0;
    unsigned char *imgNxN = NULL;
    imgNxN = new unsigned char[N*N];
    int hit_value;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            if(firstImage[i][j] == '1') {
                xStart = i - (N / 2);
                yStart = j - (N / 2);
                yLimit = j + (N / 2);
                xLimit = i + (N / 2);
                index = 0;
                memset(imgNxN, 0, N * N);
                for (x = xStart; x <= xLimit; ++x) {
                    for (y = yStart; y <= yLimit; ++y) {
                        row = x;
                        col = y;
                        if (row < 0) row = 0;
                        if (col < 0) col = 0;
                        if (row > height - 1) row = height - 1;
                        if (col > width - 1) col = width - 1;
                        imgNxN[index] = firstImage[row][col];
                        index++;
                    }
                }
                string temp_string = char_to_string_convertor(imgNxN, N);
                hit_value = Stage2_skeletonize_hit_calculator(temp_string);
                if(hit_value == 1)
                    secondImage[i][j] = binaryImage[i][j];
                else if(hit_value == 0)
                    secondImage[i][j] = '0';
            }
            else
                secondImage[i][j] = binaryImage[i][j];
        }
    }
    return secondImage;
}

unsigned char** Stage2_unconditional_thin_shrink(unsigned char** firstImage, unsigned char** binaryImage, int width, int height){
    unsigned char **secondImage = NULL;
    secondImage = create_2Darray(secondImage, width,height);
    int i, j, x, y, N=3, xStart=0, yStart=0, xLimit=0, yLimit=0, index=0, row, col, bond=0;
    unsigned char *imgNxN = NULL;
    imgNxN = new unsigned char[N*N];
    int hit_value;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            if(firstImage[i][j] == '1') {
                xStart = i - (N / 2);
                yStart = j - (N / 2);
                yLimit = j + (N / 2);
                xLimit = i + (N / 2);
                index = 0;
                memset(imgNxN, 0, N * N);
                for (x = xStart; x <= xLimit; ++x) {
                    for (y = yStart; y <= yLimit; ++y) {
                        row = x;
                        col = y;
                        if (row < 0) row = 0;
                        if (col < 0) col = 0;
                        if (row > height - 1) row = height - 1;
                        if (col > width - 1) col = width - 1;
                        imgNxN[index] = firstImage[row][col];
                        index++;
                    }
                }
                string temp_string = char_to_string_convertor(imgNxN, N);
                hit_value = Stage2_shrink_thin_hit_calculator(temp_string);
                if(hit_value == 1)
                    secondImage[i][j] = binaryImage[i][j];
                else if(hit_value == 0)
                    secondImage[i][j] = '0';
            }
            else
                secondImage[i][j] = binaryImage[i][j];
        }
    }
    return secondImage;
}

unsigned char** Stage1_conditional_shrink(unsigned char** binaryImage, int width, int height){
    unsigned char **firstImage = NULL;
    firstImage = create_2Darray(firstImage, width,height);
    int i, j, x, y, N=3, xStart=0, yStart=0, xLimit=0, yLimit=0, index=0, row, col, bond=0;
    unsigned char *imgNxN = NULL;
    imgNxN = new unsigned char[N*N];
    int hit_value;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            if(binaryImage[i][j] == '1') {
                xStart = i - (N / 2);
                yStart = j - (N / 2);
                yLimit = j + (N / 2);
                xLimit = i + (N / 2);
                index = 0;
                memset(imgNxN, 0, N * N);
                for (x = xStart; x <= xLimit; ++x) {
                    for (y = yStart; y <= yLimit; ++y) {
                        row = x;
                        col = y;
                        if (row < 0) row = 0;
                        if (col < 0) col = 0;
                        if (row > height - 1) row = height - 1;
                        if (col > width - 1) col = width - 1;
                        imgNxN[index] = binaryImage[row][col];
                        index++;
                    }
                }
                bond = bond_calculator(imgNxN, N);
                string temp_string = char_to_string_convertor(imgNxN, N);
                hit_value = shrink_hit_calculator(temp_string, bond);
                if(hit_value == 1)
                    firstImage[i][j] = '1';
                else if(hit_value == 0)
                    firstImage[i][j] = '0';
            }
            else
                firstImage[i][j] = '0';
        }
    }
    return firstImage;
}


unsigned char** Stage1_conditional_thin(unsigned char** binaryImage, int width, int height){
    unsigned char **firstImage = NULL;
    firstImage = create_2Darray(firstImage, width,height);
    int i, j, x, y, N=3, xStart=0, yStart=0, xLimit=0, yLimit=0, index=0, row, col, bond=0;
    unsigned char *imgNxN = NULL;
    imgNxN = new unsigned char[N*N];
    int hit_value;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            if(binaryImage[i][j] == '1') {
                xStart = i - (N / 2);
                yStart = j - (N / 2);
                yLimit = j + (N / 2);
                xLimit = i + (N / 2);
                index = 0;
                memset(imgNxN, 0, N * N);
                for (x = xStart; x <= xLimit; ++x) {
                    for (y = yStart; y <= yLimit; ++y) {
                        row = x;
                        col = y;
                        if (row < 0) row = 0;
                        if (col < 0) col = 0;
                        if (row > height - 1) row = height - 1;
                        if (col > width - 1) col = width - 1;
                        imgNxN[index] = binaryImage[row][col];
                        index++;
                    }
                }
                bond = bond_calculator(imgNxN, N);
                string temp_string = char_to_string_convertor(imgNxN, N);
                hit_value = thinning_hit_calculator(temp_string, bond);
                if(hit_value == 1)
                    firstImage[i][j] = '1';
                else if(hit_value == 0)
                    firstImage[i][j] = '0';
            }
            else
                firstImage[i][j] = '0';
        }
    }
    return firstImage;
}

unsigned char** Stage1_conditional_skeletonize(unsigned char** binaryImage, int width, int height){
    unsigned char **firstImage = NULL;
    firstImage = create_2Darray(firstImage, width,height);
    int i, j, x, y, N=3, xStart=0, yStart=0, xLimit=0, yLimit=0, index=0, row, col, bond=0;
    unsigned char *imgNxN = NULL;
    imgNxN = new unsigned char[N*N];
    int hit_value;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            if(binaryImage[i][j] == '1') {
                xStart = i - (N / 2);
                yStart = j - (N / 2);
                yLimit = j + (N / 2);
                xLimit = i + (N / 2);
                index = 0;
                memset(imgNxN, 0, N * N);
                for (x = xStart; x <= xLimit; ++x) {
                    for (y = yStart; y <= yLimit; ++y) {
                        row = x;
                        col = y;
                        if (row < 0) row = 0;
                        if (col < 0) col = 0;
                        if (row > height - 1) row = height - 1;
                        if (col > width - 1) col = width - 1;
                        imgNxN[index] = binaryImage[row][col];
                        index++;
                    }
                }
                bond = bond_calculator(imgNxN, N);
                string temp_string = char_to_string_convertor(imgNxN, N);
                hit_value = skeletonize_hit_calculator(temp_string, bond);
                if(hit_value == 1)
                    firstImage[i][j] = '1';
                else if(hit_value == 0)
                    firstImage[i][j] = '0';
            }
            else
                firstImage[i][j] = '0';
        }
    }
    return firstImage;
}

int Counting_stars(unsigned char** inputImage, int width, int height){
    int i, j, x, y, N=3, xStart=0, yStart=0, xLimit=0, yLimit=0, index=0, row, col;
    unsigned char *imgNxN = NULL;
    imgNxN = new unsigned char[N*N];
    int star_count=0;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            xStart = i - (N / 2);
            yStart = j - (N / 2);
            yLimit = j + (N / 2);
            xLimit = i + (N / 2);
            index = 0;
            memset(imgNxN, 0, N * N);
            for (x = xStart; x <= xLimit; ++x) {
                for (y = yStart; y <= yLimit; ++y) {
                    row = x;
                    col = y;
                    if (row < 0) row = 0;
                    if (col < 0) col = 0;
                    if (row > height - 1) row = height - 1;
                    if (col > width - 1) col = width - 1;
                    imgNxN[index] = inputImage[row][col];
                    index++;
                }
            }
            string temp_string = char_to_string_convertor(imgNxN, N);
            if(temp_string == "000010000") {
                ++star_count;
            }
        }
    }
    return star_count;
}

unsigned char** shrinking_stage1_stage2(unsigned char** binaryImage, int width, int height, int itr_count){
    unsigned char **firstImage = NULL;
    unsigned char **secondImage = NULL;
    unsigned char **tempImage = NULL;
    int star_frequency;
    int* frequency_counter = NULL;
    frequency_counter = new int[itr_count];
    memset(frequency_counter, 0, sizeof(int)*itr_count);
    int prevCount=0;

    //Repeating the Stages 1 and 2 to make the figure smaller
    tempImage = binaryImage;
    for (int k = 0; k < itr_count; ++k) {
        star_frequency = Counting_stars(tempImage, width, height);
        frequency_counter[k] = star_frequency-prevCount;
        if((prevCount-star_frequency)!=0) {
            cout << k << "\t" << (star_frequency-prevCount) << endl;
        }
        prevCount = star_frequency;
        firstImage = Stage1_conditional_shrink(tempImage, width, height);
        secondImage = Stage2_unconditional_thin_shrink(firstImage, tempImage, width, height);
        tempImage=secondImage;
    }
    return tempImage;
}

unsigned char** thinning_stage1_stage2(unsigned char** binaryImage, int width, int height, int itr_count){
    unsigned char **firstImage = NULL;
    unsigned char **secondImage = NULL;
    unsigned char **tempImage = NULL;
    //Repeating the Stages 1 and 2 to make the figure smaller
    tempImage = binaryImage;
    for (int k = 0; k < itr_count; ++k) {
        firstImage = Stage1_conditional_thin(tempImage, width, height);
        secondImage = Stage2_unconditional_thin_shrink(firstImage, tempImage, width, height);
        tempImage = secondImage;
    }
    return tempImage;
}


unsigned char** skeletonizing_stage1_stage2(unsigned char** binaryImage, int width, int height, int itr_count){
    unsigned char **firstImage = NULL;
    unsigned char **secondImage = NULL;
    unsigned char **tempImage = NULL;

    //Repeating the Stages 1 and 2 to make the figure smaller
    tempImage = binaryImage;
    for (int k = 0; k < itr_count; ++k) {

        firstImage = Stage1_conditional_skeletonize(tempImage, width, height);
        secondImage = Stage2_unconditional_skeletonize(firstImage, tempImage, width, height);
        tempImage=secondImage;
    }
    return tempImage;
}


unsigned char** Erosion(unsigned char** inputImage, int width, int height){
    unsigned char **outputImage = NULL;
    outputImage = create_2Darray(outputImage, width,height);
    int i, j, x, y, N=11, xStart=0, yStart=0, xLimit=0, yLimit=0, index=0, row, col, hit_value=0;
    unsigned char *imgNxN = NULL;
    imgNxN = new unsigned char[N*N];
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            hit_value=0;
            xStart = i - (N / 2);
            yStart = j - (N / 2);
            yLimit = j + (N / 2);
            xLimit = i + (N / 2);
            index = 0;
            memset(imgNxN, 0, N * N);
            for (x = xStart; x <= xLimit; ++x) {
                for (y = yStart; y <= yLimit; ++y) {
                    row = x;
                    col = y;
                    if (row < 0) row = 0;
                    if (col < 0) col = 0;
                    if (row > height - 1) row = height - 1;
                    if (col > width - 1) col = width - 1;
                    imgNxN[index] = inputImage[row][col];
                    index++;
                }
            }
            string temp_string = char_to_string_convertor(imgNxN, N);
            for(int k=0; k<N*N; k++) {
                if (temp_string[k] == '1') {
                    hit_value++;
                }
            }
            if(hit_value == 121)
                outputImage[i][j] = '1';
            else
                outputImage[i][j] = '0';
        }
    }
    return outputImage;
}


unsigned char** Dilation(unsigned char** inputImage, int width, int height){
    unsigned char **outputImage = NULL;
    outputImage = create_2Darray(outputImage, width,height);
    int i, j, x, y, N=27, xStart=0, yStart=0, xLimit=0, yLimit=0, index=0, row, col, hit_value=0;
    unsigned char *imgNxN = NULL;
    imgNxN = new unsigned char[N*N];
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            xStart = i - (N / 2);
            yStart = j - (N / 2);
            yLimit = j + (N / 2);
            xLimit = i + (N / 2);
            index = 0;
            memset(imgNxN, 0, N * N);
            for (x = xStart; x <= xLimit; ++x) {
                for (y = yStart; y <= yLimit; ++y) {
                    row = x;
                    col = y;
                    if (row < 0) row = 0;
                    if (col < 0) col = 0;
                    if (row > height - 1) row = height - 1;
                    if (col > width - 1) col = width - 1;
                    imgNxN[index] = inputImage[row][col];
                    index++;
                }
            }
            string temp_string = char_to_string_convertor(imgNxN, N);
            hit_value=0;
            for(int k=0; k<N*N; k++){
                if(temp_string[k] == '1'){
                    hit_value=1;
                    break;
                }
            }
            if(hit_value == 1)
                outputImage[i][j] = '1';
            else
                outputImage[i][j] = '0';
        }
    }
    return outputImage;
}

int main(int argc, char *argv[]) {
    FILE *fptr1;

    if (argc != 13) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "Syntax : hw2_prob3abcd <input_shrink.raw> <width1> <height1> <input_thin.raw> <width2> <height2> <input_skeletonize.raw> <width3> <height3> <input_counting_game.raw> <width4> <height4>" << endl;
        return 0;
    }

    unsigned char **origImage2D = NULL;
    unsigned char **binaryImage2D = NULL;
    int count;

    //Shrinking and counting stars

    char* inputFilename1 = argv[1];
    int width1 = atoi(argv[2]);
    int height1 = atoi(argv[3]);
    unsigned char **shrinkOutput2D = NULL;
    unsigned char **shrinkWrite2D=NULL;
    unsigned char *Imagedata1 = NULL;
    Imagedata1 = read_1Darray_from_file(width1,height1,inputFilename1);
    origImage2D = convert_1Dto2D(Imagedata1, width1, height1);
    binaryImage2D = monochrome_to_binary(origImage2D, width1, height1);
    shrinkOutput2D = shrinking_stage1_stage2(binaryImage2D, width1, height1, 15);
    count = Counting_stars(shrinkOutput2D, width1, height1);
    cout << "Number of stars: " << --count << endl;
    shrinkWrite2D = binary_to_monochrome(shrinkOutput2D, width1, height1);
    Imagedata1 = convert_2Dto1D(shrinkWrite2D, width1, height1);
    char outputFilename1[] = "Final_Shrink.raw";
    write_1Darray_to_file(Imagedata1, width1, height1, outputFilename1);


    // Thinning//
    char* inputFilename2 = argv[4];
    int width2 = atoi(argv[5]);
    int height2 = atoi(argv[6]);
    unsigned char *Imagedata2 = NULL;
    unsigned char **invertedImage2D = NULL;
    unsigned char **invertedOutput2D = NULL;
    unsigned char **thin_output2D = NULL;
    unsigned char **thin_write2D = NULL;
    Imagedata2 = read_1Darray_from_file(width2,height2,inputFilename2);
    origImage2D = convert_1Dto2D(Imagedata2, width2, height2);
    binaryImage2D = monochrome_to_binary(origImage2D, width2, height2);
    invertedImage2D = invert_image(binaryImage2D, width2, height2);
    thin_output2D=thinning_stage1_stage2(invertedImage2D, width2, height2, 30);
    invertedOutput2D = invert_image(thin_output2D, width2, height2);
    thin_write2D = binary_to_monochrome(invertedOutput2D, width2, height2);
    Imagedata2 = convert_2Dto1D(thin_write2D, width2, height2);
    char filename2[] = "Final_Thin.raw";
    write_1Darray_to_file(Imagedata2, width2, height2, filename2);

    // Skeletonizing

    char* inputFilename3 = argv[7];
    int width3 = atoi(argv[8]);
    int height3 = atoi(argv[9]);
    unsigned char *Imagedata3 = NULL;
    unsigned char **skeletonizedOutput2D = NULL;
    unsigned char **skeletonizedWrite2D = NULL;
    Imagedata3 = read_1Darray_from_file(width3,height3,inputFilename3);
    origImage2D = convert_1Dto2D(Imagedata3, width3, height3);
    binaryImage2D = monochrome_to_binary(origImage2D, width3, height3);
    invertedImage2D = invert_image(binaryImage2D, width3, height3);
    skeletonizedOutput2D = skeletonizing_stage1_stage2(invertedImage2D, width3, height3, 45);
    invertedOutput2D = invert_image(skeletonizedOutput2D, width3, height3);
    skeletonizedWrite2D = binary_to_monochrome(invertedOutput2D, width3, height3);
    Imagedata3 = convert_2Dto1D(skeletonizedWrite2D, width3, height3);
    char filename3[] = "Final_Skeletonize.raw";
    write_1Darray_to_file(Imagedata3, width3, height3, filename3);

    char* inputFilename4 = argv[10];
    int width4 = atoi(argv[11]);
    int height4 = atoi(argv[12]);
    unsigned char *Imagedata4 = NULL;
    unsigned char **erodedOutput2D = NULL;
    unsigned char **dilatedOutput2D = NULL;
    unsigned char **shrinkedOutput2D = NULL;
    unsigned char **puzzleWrite2D = NULL;
    Imagedata4 = read_1Darray_from_file(width4,height4,inputFilename4);
    origImage2D = convert_1Dto2D(Imagedata4, width4, height4);
    binaryImage2D = monochrome_to_binary(origImage2D, width4, height4);
    invertedImage2D = invert_image(binaryImage2D, width4, height4);
    puzzleWrite2D = binary_to_monochrome(invertedImage2D, width4, height4);
    Imagedata4 = convert_2Dto1D(puzzleWrite2D, width4, height4);
    char filename4[] = "Inverted_puzzle.raw";
    write_1Darray_to_file(Imagedata4, width4, height4, filename4);

    erodedOutput2D = Erosion (invertedImage2D, width4, height4);
    puzzleWrite2D = binary_to_monochrome(erodedOutput2D, width4, height4);
    Imagedata4 = convert_2Dto1D(puzzleWrite2D, width4, height4);
    char filename5[] = "Eroded_output.raw";
    write_1Darray_to_file(Imagedata4, width4, height4, filename5);

    dilatedOutput2D = Dilation(erodedOutput2D, width4, height4);
    puzzleWrite2D = binary_to_monochrome(dilatedOutput2D, width4, height4);
    Imagedata4 = convert_2Dto1D(puzzleWrite2D, width4, height4);
    char filename6[] = "Dilated_output.raw";
    write_1Darray_to_file(Imagedata4, width4, height4, filename6);

    shrinkedOutput2D = shrinking_stage1_stage2(dilatedOutput2D, width4, height4, 40);
    count = Counting_stars(shrinkedOutput2D, width4, height4);
    cout << "Number of jigsaw puzzles: "<< count << endl;
    invertedOutput2D = invert_image(shrinkedOutput2D, width4, height4);
    puzzleWrite2D = binary_to_monochrome(invertedOutput2D, width4, height4);
    Imagedata4 = convert_2Dto1D(puzzleWrite2D, width4, height4);
    char filename7[] = "Final_Counting.raw";
    write_1Darray_to_file(Imagedata4, width4, height4, filename7);

    return 0;
}
