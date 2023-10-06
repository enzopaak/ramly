#include <iostream>
#include "bmplib.h"
#include <unistd.h>

using namespace std;
unsigned char imgGS[SIZE][SIZE];
unsigned char imgRGB[SIZE][SIZE][RGB];

int main() {
    string imageName, path = "\\imgs\\", filter;
    cout << "Enter full Image Name (ex: elephant.bmp): ";
    cin >> imageName;
    path += imageName;
    char cwd[PATH_MAX];
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), imgGS);
    cout << "Select Filter by typing the letters between brackets: \n1. Black & White (BW)\n4. Flip Image (FI)\n\nYour choice: ";
    cin >> filter;
    if (filter == "BW"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (imgGS[i][j] > 127)
                    imgGS[i][j] = 255;
                else
                    imgGS[i][j] = 0;
            }
        }
    } else if (filter == "FI"){
        cout << "type H for horizontal, type V for vertical: ";
        string horv;
        cin >> horv;
        if (horv == "H"){
            for (int y = 0; y < 128; y++){
                for (int x = 0; x < 256; x++){
                    unsigned char temp[SIZE][SIZE];
                    temp[x][y] = imgGS[x][y];
                    imgGS[x][y] = imgGS[x][256 - 1 - y];
                    imgGS[x][256 - 1 - y] = temp[x][y];
                }
            }
        } else {
            for (int x = 0; x < 128; x++){
                for (int y = 0; y < 256; y++){
                    unsigned char temp[SIZE][SIZE];
                    temp[x][y] = imgGS[x][y];
                    imgGS[x][y] = imgGS[256 - 1 - x][y];
                    imgGS[256 - 1 - x][y] = temp[x][y];
                }
            }
        }
    }
    showGSBMP(imgGS);
    return 0;
}