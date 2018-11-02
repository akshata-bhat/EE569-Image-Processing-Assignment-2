// Author : Akshata Bhat
// USC ID : 9560895350
// Email : akshatab@usc.edu
// Submission Date : 3/4/2018

#ifndef HW2_PROB2_3A_MY_FILE_HEADER_H
#define HW2_PROB2_3A_MY_FILE_HEADER_H

#endif //HW2_PROB2_3A_MY_FILE_HEADER_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

float** create_2Darray(float** array, int width, int height);
int** create_2Darray(int** array, int width, int height);
unsigned char** create_2Darray(unsigned char** array, int width, int height);
unsigned char max_val(unsigned char, unsigned char, unsigned char);
unsigned char min_val(unsigned char, unsigned char, unsigned char);
int mostFrequentValue(int a[], int length);
int min_val_index(float intensity, float b[]);
int mostFrequentValue(int a[], int length);
int closest_value(int intensity, int b[], int levels);

float** create_2Darray(float** array, int width, int height)
{
    array = new float *[height];
    for (int i = 0; i < height; ++i) {
        array[i] = new float[width];
        memset(array[i], 0, width *sizeof(float));
    }
    return array;
}

int** create_2Darray(int** array, int width, int height)
{
    int i;
    array = new int *[height];
    for (i = 0; i < height; ++i) {
        array[i] = new int[width];
        memset(array[i], 0, width *sizeof(int));
    }
    return array;
}

unsigned char** create_2Darray(unsigned char** array, int width, int height)
{
    int i;
    array = new unsigned char *[height];
    for (i = 0; i < height; ++i) {
        array[i] = new unsigned char[width];
        memset(array[i], 0, width *sizeof(unsigned char));
    }
    return array;
}

unsigned char min_val(unsigned char a, unsigned char b, unsigned char c)
{

    if( a<=b && a<=c )
        return a;

    else if( b<=a && b<=c )
        return b;

    else if( c<=a && c<=b )
        return c;

}

unsigned char max_val(unsigned char a, unsigned char b, unsigned char c)
{

    if( a>=b && a>=c )
        return a;

    else if( b>=a && b>=c )
        return b;

    else if( c>=a && c>=b )
        return c;

}

int mostFrequentValue(int a[], int length)
{
    int count = 1, tempValCount;
    int tempVal = 0 ;
    int mostFrequent = a[0];
    for (int i = 0; i < (length - 1); i++)
    {
        tempVal = a[i];
        tempValCount = 0;
        for (int j = 1; j < length; j++)
        {
            if (tempVal == a[j])
                tempValCount++;
        }
        if (tempValCount > count)
        {
            count = tempValCount;
            mostFrequent = tempVal;
        }
    }
    return mostFrequent;
}

int median_value_calc(int list[], int length)
{
    int center = (length+1)/2;
    int insert_pos,valueTo_insert;
    for(int i=1;i<length;++i){
        insert_pos=i;
        valueTo_insert=list[insert_pos];
        while(insert_pos>0&&list[insert_pos-1]>valueTo_insert){
            list[insert_pos]=list[insert_pos-1];
            insert_pos--;
        }
        if(insert_pos!=i){
            list[insert_pos]=valueTo_insert;
        }
    }
    return list[center];
}

int min_val_index(float intensity, float b[])
{
    float diff[256];
    float min;
    int position = 0;
    for(int i=0; i<256; i++ )
    {
        diff[i] = abs(intensity - b[i]);
    }
    min = diff[0];
    for(int i=1; i<256; i++)
    {
        if(min >= diff[i])
        {
            min = diff[i];
            position = i;
        }
    }
    return position;
}

double psnr_calc(unsigned char a[], unsigned char b[], int width, int height)
{
    double MSE = 0.0;
    double psnr = 0.0;
    double MSE_diff = 0.0;
    int MAX = 255;
    int i;

    for(i=0; i < width*height; i++)
    {
        MSE_diff = abs(int(a[i]) - int(b[i]));
        MSE = MSE + MSE_diff*MSE_diff;
    }
    MSE = double(MSE)/double(width*height);

    if(MSE == 0)
        return 99.0;

    psnr = 10*log10(MAX*MAX/MSE);
    return psnr;
}

