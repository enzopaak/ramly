//  FCAI: OOP Programming, 2023, Assignment 1
//  Program Name:				CS213-2023-20220740-20220709-20220954-A1-Part1.cpp
//  Last Modification Date:	09/10/2023
//  Author 1, ID and Group:     Ahmed Emad, 20220740, A
//  Author 2, ID and Group:     Mohammed Adam, 20220709, A
//  Author 3, ID and Group:     Mohammed Ahmed, 20220954, A
//  Teaching Assistant:		    N/A
//  Purpose:                    Assignment 1

#include <iostream>
#include "bmplib.h"
#include <unistd.h>
#include <cmath>

using namespace std;

// Adding arrays
unsigned char imgGS[SIZE][SIZE];
unsigned char imgGS2[SIZE][SIZE];
unsigned char imgGS3[SIZE][SIZE];
unsigned char imgRGB[SIZE][SIZE][RGB];
unsigned char quarter[(SIZE/2)*(SIZE/2)] = {};
// all filter functions:
void bandw(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (imgGS[i][j] > 127)
                imgGS[i][j] = 255;
            else
                imgGS[i][j] = 0;
        }
    }
    showGSBMP(imgGS);
    // Picking the threshold for changing bits to either 0 or 255
}

void flip(){
    cout << "type H for horizontal, type V for vertical: ";
    string horv;
    cin >> horv;
    if (horv == "H"){                                   // Flipping for X axis
        for (int y = 0; y < 128; y++){
            for (int x = 0; x < 256; x++){
                unsigned char temp[SIZE][SIZE];         // Going bit by bit.
                temp[x][y] = imgGS[x][y];               // Copying first bit to a temporary location
                imgGS[x][y] = imgGS[x][256 - 1 - y];    // Copying value of last bit and putting it in first bit (flip positions)
                imgGS[x][256 - 1 - y] = temp[x][y];     // Copying the value of first bit from temp, to last bit
            }
        }
    } else {
        for (int x = 0; x < 128; x++){                  // Flipping for Y axis, same process as above
            for (int y = 0; y < 256; y++){
                unsigned char temp[SIZE][SIZE];
                temp[x][y] = imgGS[x][y];
                imgGS[x][y] = imgGS[256 - 1 - x][y];
                imgGS[256 - 1 - x][y] = temp[x][y];
            }
        }
    }
    showGSBMP(imgGS);
}

void weweLight() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            imgGS[i][j] += ((255 - imgGS[i][j]) / 2);

        }
    }
    showGSBMP(imgGS);
    // this function takes the 50% of the bits in the pixels and add it to the original without passing the white color bits limit
//------------------------------------------------------------------------------------
}
void weweDarken(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            imgGS[i][j] = imgGS[i][j] * 0.5;

        }
    }
    showGSBMP(imgGS);
}
// this function darken the color by dividing it by 2 or multiply by half

void loadForMerge(){
    char cwd[PATH_MAX];
    string newPath = "\\imgs\\";
    char imgnm2[100];
    cout << "Please enter image 2 (with extension): ";
    cin >> imgnm2;
    newPath += imgnm2;
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), newPath.c_str()),imgGS2);


    // a function that loads two images
}
//-------------------------------------------------------------------------------------------
void merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            imgGS3[i][j] = (imgGS[i][j] + imgGS2[i][j]) / 2;
        }

        // a function that takes two images and merge them by adding their bits and taking their average
    }
    showGSBMP(imgGS3);
}
//-------------------------------------------------------------------------
void savingMerge(){
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, imgGS3);

    // saving merge
}

void rotate90() {
    unsigned char rot[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            rot[i][j] = imgGS[i][j];            // Copying value of bit to temp location
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            imgGS[j][SIZE - 1 - i] = rot[i][j];     // Copying value of bit to be rotated from temp location
        }
    }
}
void rotate() {
    string dgree;
    cout << "Choose a degree to rotate 90, 180 or 270: ";
    cin >> dgree;
    if ( dgree == "270" || dgree == "180" || dgree == "90") {
        int angle = stoi(dgree);            // Change string to int value
        for (int i = 0; i < angle / 90; i++) {
            rotate90();
        }
    }
    else {
        cout << "Wrong! Please enter a mentioned degree: ";
        return rotate();
    }
    showGSBMP(imgGS);
}
void invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            imgGS[i][j] = 255 - imgGS[i][j];        // Invert bit value by reducing it from 255
        }
    }
    showGSBMP(imgGS);
}

void edge() {
    // first convert the image to black and white to get extreme contrasts
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (imgGS[i][j] > 127)
                imgGS[i][j] = 255;
            else
                imgGS[i][j] = 0;
        }
    }
    // find bits in the same column and row that have equal values and convert them to white
    // if they're not equal then they're edges and are converted to black
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (imgGS[i][j] == imgGS[i+1][j] & imgGS[i][j] == imgGS[i][j+1]){
                imgGS[i][j] = 255;
            } else {
                imgGS[i][j] = 0;
            }
        }
    }
    showGSBMP(imgGS);
}

void mirror1() {
    // mirrors the left half
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            imgGS[x][256 - 1 - y] = imgGS[x][y];
        }
    }
    showGSBMP(imgGS);
}
void mirror2() {
    // mirrors the right half
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            imgGS[x][y] = imgGS[x][256 - 1 - y];
        }
    }
    showGSBMP(imgGS);
}
void mirror3() {
    //mirrors the top half
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            imgGS[256 - 1 - x][y] = imgGS[x][y];
        }
    }
    showGSBMP(imgGS);
}
void mirror4() {
    // mirrors the bottom half
    for (int x = 0; x < 256; x++) {
        for (int y = 0; y < 256; y++) {
            imgGS[x][y] = imgGS[256 - 1 - x][y];
        }
    }
    showGSBMP(imgGS);
}
void crop(){
    // this function takes a desired x & y position to start from
    // then takes a width and length from input
    // then turns every bit from the edge of the image to the x and y values to 0
    // then turns every bit after the x position + the width desired to 0
    // then turns every bit after the y position + the length desired to 0
    int posx, posy, w, l;
    cout << "Enter the desired x and y values to crop the image to: ";
    cin >> posx >> posy;
    cout << "Enter the desired width and length of the cropped image: ";
    cin >> w >> l;
    for (int i = 0; i < posx; i++){
        if (posx >= 256) {
            cout << "Invalid dimensions.";
            break;
        }
        for (int j = 0; j < 256; j++){
            if (posy >= 256) {
                cout << "Invalid dimensions.";
                break;
            }
            imgGS[i][j] = 0;
        }
    }
    for (int j = 0; j < posx; j++){
        for (int i = 0; i < 256; i++){
            imgGS[i][j] = 0;
        }
    }
    for (int i = 256; i > posx + w; i--){
        for (int j = 256; j >= 0; j--){
            imgGS[i][j] = 0;
        }
    }
    for (int j = 256; j > posy + l; j--){
        for (int i = 256; i >= 0; i--){
            imgGS[i][j] = 0;
        }
    }

    showGSBMP(imgGS);
}

void blur(){
    int ks = 5;
    int kc = ks / 2;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int n  = 0;
            for (int w = -kc; w <= kc; ++w){
                for ( int z = -kc; z<=kc;++z){
                    int m = j + w;
                    int v = i + z;

                    if(m >= 0 && m < SIZE && v >= 0 && v < SIZE){
                        n += imgGS[m][v];
                    }
                }
            }
            imgGS3[256 - i][j] = n / (ks * ks);
        }
    }
    unsigned char rot[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            rot[i][j] = imgGS3[i][j];            // Copying value of bit to temp location
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            imgGS3[j][SIZE - 1 - i] = rot[i][j];     // Copying value of bit to be rotated from temp location
        }
    }
    showGSBMP(imgGS3);
}


void GetQuarter(unsigned char * & ptr, int quarter){
    if (quarter < 1 or quarter > 4)
        cout << "ERROR QUARTER";
    int start_r = 0 , end_r =SIZE/2 ;
    int start_c = 0 ,end_c = SIZE/2;
    if (quarter == 2) {
        start_c = SIZE/2 , end_c=SIZE;
        }
    else if (quarter == 3) {
        start_r = SIZE / 2 , end_r= SIZE;
    }
    else if (quarter == 4) {
        start_r = SIZE / 2;
        start_c = SIZE / 2;
        end_r = SIZE;
        end_c = SIZE;
    }
    int k = 0;
    for (int i = start_r; i < end_r; i++) {
        for (int j = start_c; j < end_c; j++) {
            ptr[k++] = image[i][j];
        }
    }
}

void GetQuarter(unsigned char * & ptr, int quarter){
    if (quarter < 1 or quarter > 4)
        cout << "ERROR QUARTER";
    int start_r = 0 , end_r =SIZE/2 ;
    int start_c = 0 ,end_c = SIZE/2;
    if (quarter == 2) {
        start_c = SIZE/2 , end_c=SIZE;
    }
    else if (quarter == 3) {
        start_r = SIZE / 2 , end_r= SIZE;
    }
    else if (quarter == 4) {
        start_r = SIZE / 2;
        start_c = SIZE / 2;
        end_r = SIZE;
        end_c = SIZE;
    }
    int k = 0;
    for (int i = start_r; i < end_r; i++) {
        for (int j = start_c; j < end_c; j++) {
            ptr[k++] = image[i][j];
        }
    }
}

void enlargeFilter() {
    int userquad;
    unsigned char * pQuad = quarter;
    cout << "choose a quarter 1, 2, 3 or 4?";
    cin >> userquad;

    GetQuarter(pQuad, userquad);
    int k = 0;
    for (int i = 0; i < SIZE; i+=2) {
        for (int j = 0; j < SIZE; j+=2) {
            imgGS[i][j] = pQuad[k];
            imgGS[i][j+1] = pQuad[k];
            imgGS[i+1][j] = pQuad[k];
            imgGS[i+1][j+1] = pQuad[k];
            k++;

        }
    }
}


void shrink() {
    int factor;
    int nsize = SIZE / factor;
    unsigned char nimage[nsize][nsize];
    for (int i = 0; i < nsize; i++) {
        for (int j = 0; j < nsize; j++) {
            int sum = 0;
            int count = 0;
            for (int x = i * factor; x < (i + 1) * factor; x++) {
                for (int y = j * factor; y < (j + 1) * factor; y++) {
                    // this loop checks for out of boundaries access
                    if (x < SIZE && y < SIZE) {
                        sum += imgGS3[x][y];
                        count++;
                    }
                }
            }

            if (count > 0) {
                nimage[i][j] = static_cast<unsigned char>(sum / count);
            }
        }
    }
    int y = SIZE - nsize;
    y = y*6;
    for(int x = nsize; x<y; x++){
        for(int w= nsize; w<y; w++){
            imgGS3[x][y]= 255;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            imgGS3[i][j] = 255;
        }
    }
    // Replace image with new image
    for (int i = 0; i < nsize; i++) {
        for (int j = 0; j < nsize; j++) {
            imgGS3[i][j] = nimage[i][j];
        }
    }
    showGSBMP(imgGS3);
}

void skew() {
    char n;
    cout << "Please enter H for horizontal skew or V for vertical skew: ";
    cin >> n;

    double rad;
    cout << "Please enter a degree: ";
    cin >> rad;
    //read the angle of skewness
    rad = (rad * M_PI) / 180;
    // convert the angle to radian
    double move = tan(rad);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            imgGS3[i][j] = 255;
            //create a white picture
        }
    }
    if (n == 'H') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int newj = j + static_cast<int>(move * (SIZE / 2 - i));
                if (newj >= 0 && newj < SIZE) {
                    imgGS3[i][newj] = imgGS[i][j];
                }
            }
        }
    } else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int newi = i + static_cast<int>(move * (SIZE / 2 - j));
                if (newi >= 0 && newi < SIZE) {
                    imgGS3[newi][j] = imgGS[i][j];

                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                imgGS[i][j] = imgGS3[i][j];
            }
        }
        showGSBMP(imgGS);
    }
}


int main() {
    string imageName, path = "\\imgs\\", filter;
    cout << "Enter full Image Name (without extension): ";
    cin >> imageName;
    path += imageName + ".bmp";
    char cwd[PATH_MAX];
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), imgGS);
    cout << "Select Filter by typing its number:"
            "\n1. Black & White"
            "\n2. Invert Image"
            "\n3. Merge 2 Images"
            "\n4. Flip Image"
            "\n5. Rotate Image"
            "\n6. Lighten & Darken"
            "\n7. Edge Detection"
            "\n9. Shrink Image"
            "\na. Mirror Image"
            "\nc. Blur Image"
            "\nd. Crop image"
            "\ne. Skew Image"
            "\n\nYour choice: ";

    cin >> filter;
    if (filter == "1"){
        bandw();
    } else if (filter == "2") {
        invert();
    } else if (filter == "3"){
        loadForMerge();
        savingMerge();
        merge();
    } else if (filter == "4"){
        flip();
    } else if (filter == "5"){
        rotate();
    } else if (filter == "6"){
        cout << "Enter 'L' for lighten or 'D' for Darken image: ";
        string lnd; cin >> lnd;
        if (lnd == "L"){
            weweLight();
        } else {
            weweDarken();
        }
    } else if (filter == "7"){
        edge();
        else if (filter == "8"){
        enlargeFilter();
    }
    } else if (filter == "9"){
        shrink();
    } else if (filter == "a"){
        mirror1();
        readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), imgGS);
        mirror2();
        readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), imgGS);
        mirror3();
        readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), imgGS);
        mirror4();
    } else if (filter == "c"){
        blur();
    } else if (filter == "d"){
        crop();
    } else if (filter == "e"){
        skew();
    }
    return 0;
}
