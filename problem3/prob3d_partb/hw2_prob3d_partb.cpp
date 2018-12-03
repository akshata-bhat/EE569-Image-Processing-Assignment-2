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
#define label_count 100
using namespace std;

int firstLabel = 1;
int currentLabel = 2;

int table[label_count][2]={0};
int tRow = 0;


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

//Function to convert from values 0, 255 to 0, 1
unsigned char** monochrome_to_binary(unsigned char** origImage, int width, int height){
    unsigned char **binImage = NULL;
    binImage = create_2Darray(binImage, width,height);
    int threshold=127, count=0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(origImage[i][j] < threshold){
                binImage[i][j] = '0';
            }
            else {
                binImage[i][j] = '1';
                count ++;
            }
        }
    }
    return binImage;
}


//Function to convert from values 0,1 to 0,255
unsigned char** binary_to_monochrome(unsigned char** binImage, int width, int height){
    unsigned char **monochromeImage = NULL;
    monochromeImage = create_2Darray(monochromeImage, width,height);
    for (int i = 0; i < height ; ++i) {
        for (int j = 0; j < width ; ++j) {
            if(binImage[i][j] == '1'){
                monochromeImage[i][j] = (unsigned char)255;
            }
            else
                monochromeImage[i][j] = (unsigned char)0;
        }
    }
    return monochromeImage;
}

void lookupTable_update(int a1, int b1){
    if(a1 == 0 || b1 == 0)
        return;
    if(tRow == 0){
        table[tRow][0] = a1;
        table[tRow][1] = b1;
        tRow++;
        return;
    }
    else{
        for (int i = 0; i < label_count; ++i) {
            if (table[i][0] == a1 && table[i][1] == b1)
                return;
        }
        for (int i = 0; i < label_count; ++i) {
            if(table[i][0]==0 && table[i][1]==0)
                break;
            if(a1==table[i][0]  || a1==table[i][1]){
                for (int k = 0; k < label_count; ++k) {
                    if (table[k][0] == table[i][0] && table[k][1] == b1)
                        return;
                }
                table[tRow][0] = table[i][0];
                table[tRow][1] = b1;
                tRow++;
                return;
            }

            if(b1==table[i][0]  || b1==table[i][1]){
                if(a1 < table[i][0]){
                    table[tRow][0] = a1;
                    table[tRow][1] = table[i][1];
                    table[i][0] = a1;
                    table[i][1] = b1;
                    tRow++;
                    return;
                }
                else{
                    for (int k = 0; k < label_count; ++k) {
                        if (table[k][0] == table[i][0] && table[k][1] == a1)
                            return;
                    }
                    table[tRow][0] = table[i][0];
                    table[tRow][1] = a1;
                    tRow++;
                    return;
                }
            }
        }
    }

    table[tRow][0] = a1;
    table[tRow][1] = b1;
    tRow++;
    return;
}

void label_assignment(int* neighbours, int* labelNxN, int** labels_matrix, int current_i, int current_j){
    int a, b, c, d;
    a=neighbours[3];
    b=neighbours[0];
    c=neighbours[1];
    d=neighbours[2];
    if(a+b+c+d == 0) {
        labels_matrix[current_i][current_j] = ++currentLabel;
    }
    else if(a+b+c+d == 1) {
        labelNxN = insertion_sort_increasing(labelNxN, 4);
        labels_matrix[current_i][current_j] = labelNxN[0];
    }
    else if(a+b+c+d == 2){
        labelNxN = insertion_sort_increasing(labelNxN, 4);
        labels_matrix[current_i][current_j] = labelNxN[0];
        lookupTable_update(labelNxN[0], labelNxN[1]);

    }
    else if(a+b+c+d == 3){
        labelNxN = insertion_sort_increasing(labelNxN, 4);
        labels_matrix[current_i][current_j] = labelNxN[0];
        lookupTable_update(labelNxN[0], labelNxN[1]);
        lookupTable_update(labelNxN[0], labelNxN[2]);
    }
    else{
        labelNxN = insertion_sort_increasing(labelNxN, 4);
        labels_matrix[current_i][current_j] = labelNxN[0];
        lookupTable_update(labelNxN[0], labelNxN[1]);
        lookupTable_update(labelNxN[0], labelNxN[2]);
        lookupTable_update(labelNxN[0], labelNxN[3]);

    }
}

int sort_lookup_table() {
    int length = 0;
    for (int i = 0; i < 100; i++) {
        if (table[i][0] > 0)
            ++length;
    }

    int i,j=0,temp1, temp2;
    bool swapped = false;
    for(i=0;i<length;++i){
        for(j=0;j<(length-i);++j){
            if(table[j][0]>table[j+1][0]){
                temp1 = table[j][0];
                temp2 = table[j][1];
                table[j][0] = table[j+1][0];
                table[j][1] = table[j+1][1];
                table[j+1][0] = temp1;
                table[j+1][1] = temp2;
                swapped=true;
            }
        }
        if(!(swapped)){
            cout<<"The table is sorted"<<endl;
            break;
        }
    }

    return length+1;
}

int** replace_labels(int length, int height, int width, int** labelsMatrix){
    for(int k=length -1; k>0; k--){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (labelsMatrix[i][j] == table[k][1]){
                    labelsMatrix[i][j] = table[k][0];
                }
            }
        }
    }
    return labelsMatrix;
}

int** label_1to16(int* origLabels, int** labelsMatrix, int width, int height){
    int* uniquelabels = NULL;
    uniquelabels = new int [16]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    for (int k = 0; k < 16; ++k) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; ++j) {
                if (labelsMatrix[i][j] == origLabels[k])
                    labelsMatrix[i][j] = uniquelabels[k];
            }
        }
    }
    return labelsMatrix;
    }

int* return_nonzero_elements(int* list, int length){
    int count=0;
    for (int i = 0; i < length; ++i) {
        if(list[i] > 0)
            ++count;
    }
    int* positive_terms = NULL;
    positive_terms = new int[length];
    count=0;
    for (int j = 0; j < length; ++j) {
        if(list[count] > 0){
            positive_terms[j] = list[count];
            ++count;
        }
    }
    return  positive_terms;
}

int** assignment_stage(unsigned char** inputImage, int width, int height) {
    int **labelsMatrix = NULL;
    labelsMatrix = create_2Darray(labelsMatrix, width, height);
    int ** relabeledMatrix = NULL;
    int i, j, x=0, y=0, N=3, xStart = 0, yStart = 0, xLimit = 0, yLimit = 0, index = 0, row, col;
    int *imgNxN = NULL;
    imgNxN = new int[4];
    int *labelNxN = NULL;
    labelNxN = new int[4];
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            if (inputImage[i][j] == '1') {
                if(firstLabel == 1){
                    labelsMatrix[i][j] = ++firstLabel;
                    firstLabel = 0;
                    continue;
                }
                xStart = i - (N / 2);
                yStart = j - (N / 2);
                yLimit = j + (N / 2);
                xLimit = i + (N / 2);
                index = 0;
                memset(imgNxN, 0, 4*sizeof(int));
                memset(labelNxN, 0, 4*sizeof(int));
                x=xStart;
                while(x <= xLimit)
                {
                    y=yStart;
                    while(y <= yLimit)
                    {
                        row = x;
                        col = y;
                        if (row < 0) row = 0;
                        if (col < 0) col = 0;
                        if (row > height - 1) row = height - 1;
                        if (col > width - 1) col = width - 1;
                        imgNxN[index] = (inputImage[row][col])-'0';
                        labelNxN[index] = labelsMatrix[row][col];
                        index++;
                        if(index == 4)
                            break;
                        y++;
                   }
                    if(index == 4)
                        break;
                    x++;
                }
                label_assignment(imgNxN, labelNxN, labelsMatrix, i, j);
            }
        }
    }

    int length = sort_lookup_table();
    relabeledMatrix = replace_labels(length, height, width, labelsMatrix);
    int* labels1D = NULL;
    int* origlabels_16 = NULL; // Unique 16 labels not in sequence
    int** newlabels_16 = NULL;

    labels1D = convert_2Dto1D(relabeledMatrix, width, height);
    labels1D = insertion_sort_increasing(labels1D,width*height);
    origlabels_16 = return_nonzero_elements(labels1D, width*height);
    newlabels_16 = label_1to16(origlabels_16, labelsMatrix, width, height);
    return newlabels_16;
}

void rightRotate(int* list, int rotate_value, int elements_count)
{
    int i;
    for (i = 0; i < rotate_value; i++)
    {
        int n = elements_count;
        int i, temp;
        temp = list[n-1];
        for (i = n-1; i >0; i--)
            list[i] = list[i-1];
        list[0] = temp;
    }
}

int compare2Arrays(int* list1, int* list2, int length ) {
    for (int i = 0; i < length ; ++i) {
        if(list1[i]!=list2[i])
            return 0;
    }
    return 1;
}


int holes_protrusions_calculator(int** relabeledMatrix, unsigned char** inputImage, int width, int height) {
    int index = 0;
    int *address_X = NULL;
    address_X = new int[5000];
    int *address_Y = NULL;
    address_Y = new int[5000];
    int *min_valX = NULL;
    min_valX = new int[16];
    int *min_valY = NULL;
    min_valY = new int[16];
    int *max_valY = NULL;
    max_valY = new int[16];
    
    // Finding the starting point for each puzzle - (x, y) co-oridinate in order to perform the 45x45 xor multiplication
    
    // Storing the coordinates of all pixels which have the same label 1 - 16 
    int count = 0;
    for (int k = 1; k <= 16; k++) {
        memset(address_X, 0, sizeof(int));
        memset(address_Y, 0, sizeof(int));
        index = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (relabeledMatrix[i][j] == k) {
                    address_X[index] = i;
                    address_Y[index] = j;
                    index++;
                }
            }
        }

        // sorting the addresses of pixels labeled "n", in order to get the starting and ending y coordinates for that object 
        address_Y = insertion_sort_increasing(address_Y, 5000);
        min_valY[k - 1] = address_Y[0];
        address_Y = sort_decreasing(address_Y, 5000);
        max_valY[k - 1] = address_Y[0];
        int m, n;
        for (m = 0; m < height; ++m) {
            for (n = 0; n < width; ++n) {
                if (relabeledMatrix[m][n] == k) {
                    if (n == min_valY[k - 1]) {
                        min_valX[k - 1] = m;
                        break;
                    }
                }
            }
            if (n == min_valY[k - 1])
                break;
        }

    }

    unsigned char **tempImage = NULL;
    tempImage = inputImage;

    // Creating an array to save the 45x45 xor result
    unsigned char **XorArray = NULL;
    XorArray = new unsigned char *[45];
    for (int i = 0; i < 45; ++i) {
        XorArray[i] = new unsigned char[45];
        memset(XorArray[i], 1, 45 * sizeof(unsigned char));
    }

    // Performing the XOR operation
    int x = 0, y = 0; // mask co-ordinates
    int N = 46, xLimit = 0, yLimit = 0;

    for (int k = 1; k <= 16; ++k) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i == min_valX[k - 1] && j == min_valY[k - 1]) {
                    yLimit = j + N;
                    xLimit = i + N;
                    for (x = i; x < xLimit; ++x) {
                        for (y = j; y < yLimit; ++y) {
                            if (tempImage[x][y] == '1')
                                tempImage[x][y] = '0';
                            else
                                tempImage[x][y] = '1';
                        }
                    }
                }
            }
        }
    }

    int **holes = NULL;
    holes = create_2Darray(holes, 4, 16);
    int **protrusions = NULL;
    protrusions = create_2Darray(protrusions, 4, 16);
    int midX, midY, d;
    for (int k = 1; k <= 16; ++k) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i == min_valX[k - 1] && j == min_valY[k - 1]) {
                    midX = i + N / 2;
                    midY = j + N / 2;
                    //To calculate protrusions in each puzzle
                    d = (N / 2) + 2;
                    count = 0;
                    if (tempImage[midX - d][midY] == '1') { // Checking a protrusion on the left(West)
                        protrusions[k - 1][count] = 1;
                    }
                    count++;

                    if (tempImage[midX][midY + d] == '1') { // protrusion at the bottom(south)
                        protrusions[k - 1][count] = 1;
                    }
                    count++;

                    if (tempImage[midX + d][midY] == '1') {  // protrusion on the right(east)
                        protrusions[k - 1][count] = 1;
                    }
                    count++;

                    if (tempImage[midX][midY - d] == '1') { // protrusion at the top(north)
                        protrusions[k - 1][count] = 1;
                    }

                    //To calculate holes in each puzzle
                    count = 0;
                    d = (N / 2) - 2;
                    //top
                    if (tempImage[midX - d][midY] == '1') { // left
                        holes[k - 1][count] = 1;
                    }
                    count++;
                    //right
                    if (tempImage[midX][midY + d] == '1') { // bottom
                        holes[k - 1][count] = 1;
                    }
                    count++;
                    //bottom
                    if (tempImage[midX + d][midY] == '1') { // right
                        holes[k - 1][count] = 1;
                    }
                    count++;
                    //left
                    if (tempImage[midX][midY - d] == '1') {  //top
                        holes[k - 1][count] = 1;
                    }
                }
            }
        }
    }

    int *temp_H1 = NULL;
    temp_H1 = new int[4];
    memset(temp_H1, 0, sizeof(int));
    int *temp_P1 = NULL;
    temp_P1 = new int[4];
    memset(temp_P1, 0, sizeof(int));
    int *temp_H2 = NULL;
    temp_H2 = new int[4];
    memset(temp_H2, 0, sizeof(int));
    int *temp_P2 = NULL;
    temp_P2 = new int[4];
    memset(temp_P2, 0, sizeof(int));
    int match_flag = 0, non_unique_elements = 0, total_elements = 16, table_updated, table_ptr=0, elements=16;
    bool n_found=false;
    bool m_found=false;
    int **matches = NULL;
    matches = create_2Darray(matches, 2, 20);
    
    // Comparing 2 jig saws at a time - P1H1 and P2H2
    for (int m = 1; m <= 16; ++m) {
        
        // Loading the first jigsaw, which is to be compared with the rest  
        for (int k = 0; k < 4; k++) {
            temp_H1[k] = holes[m - 1][k];
            temp_P1[k] = protrusions[m - 1][k];
        }
        for (int n = 1; n <= 16; ++n) {
            if (m != n) {
                // Loading the second jigsaw
                for (int k = 0; k < 4; k++) {
                    temp_H2[k] = holes[n - 1][k];
                    temp_P2[k] = protrusions[n - 1][k];
                }
                for (int l = 0; l < 4; ++l) {
                    if ((compare2Arrays(temp_H1, temp_H2, 4) && compare2Arrays(temp_P1, temp_P2, 4))) {
                        elements -=1;
                        match_flag = 1;
                        break;
                    }
                    
                    // Right rotate by 1 position
                    rightRotate(temp_H2, 1, 4);
                    rightRotate(temp_P2, 1, 4);
                }
                if (match_flag == 1) {
                    table_updated = 0;
                    for (int p = 0; p < 20; p++) {
                        if (matches[p][0] == n && matches[p][1] == m) {
                            table_updated = 1;
                            break;
                        }
                    }
                    if (table_updated != 1){
                        m_found = false;
                        n_found = false;

                        for (int i = 0; i < 20; ++i) {
                            if(matches[i][0] == m || matches[i][1] == m) {
                                m_found = true;
                                break;
                            }
                        }
                        for (int i = 0; i < 20; ++i) {
                            if (matches[i][0] == n || matches[i][1] == n) {
                                n_found = true;
                                break;
                            }
                        }
                        if(m_found == false)
                            non_unique_elements += 1;
                        if(n_found == false)
                            non_unique_elements += 1;
                        if(m_found == false && n_found == false){
                            matches[table_ptr][0] = m;
                            matches[table_ptr][1] = n;
                            table_ptr+=1;
                            non_unique_elements += 2;
                        }
                    }
                    match_flag = 0;
                }
            }
        }
    }

    unsigned char **newImage2D = NULL;
    unsigned char *Imagedata2 = NULL;
    newImage2D = binary_to_monochrome(tempImage, width, height);
    Imagedata2 = convert_2Dto1D(newImage2D, width, height);
    char filename3[] = "Final_xor.raw";
    write_1Darray_to_file(Imagedata2, width, height, filename3);

    int unique_elements = total_elements - elements;
    return unique_elements;
}

int main(int argc, char *argv[]) {
    FILE *fptr1;

    if (argc != 4) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout
                << "Syntax : hw2_prob3d_partb <input.raw> <width> <height>"
                << endl;
        return 0;
    }

    char *inputFilename = argv[1];
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    unsigned char **origImage2D = NULL;
    unsigned char **binaryImage2D = NULL;
    int **relabeledMatrix = NULL;
    unsigned char **invertedImage2D = NULL;
    unsigned char *Imagedata1 = NULL;
    Imagedata1 = read_1Darray_from_file(width, height, inputFilename);
    origImage2D = convert_1Dto2D(Imagedata1, width, height);
    binaryImage2D = monochrome_to_binary(origImage2D, width, height);
    invertedImage2D = invert_image(binaryImage2D, width, height);
    relabeledMatrix = assignment_stage(invertedImage2D, width, height);
    int unique_elements = holes_protrusions_calculator(relabeledMatrix, invertedImage2D, width, height);

    cout << "Number of unique elements: " << unique_elements << endl;

    return 0;
}
