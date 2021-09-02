#include "ImageMaker.h"
#include <fstream>

ImageMaker::ImageMaker() {
    width = 0;
    height = 0;
    pen_red = 0;
    pen_green = 0;
    pen_blue = 0;
    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; j < MAX_HEIGHT; j++) {
            image[i][j][RED] = 255;
            image[i][j][GREEN] = 255;
            image[i][j][BLUE] = 255;
        }
    }
}

ImageMaker::ImageMaker(string filename) {
    // initialize variable image to be white
    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; i < MAX_HEIGHT; j++) {
            image[i][j][RED] = 255;
            image[i][j][GREEN] = 255;
            image[i][j][BLUE] = 255;
        }
    }
    // load ppm into the image matrix
    LoadImage(filename);
    // setting the default pen color to black (0, 0, 0)
    SetPenRed(0);
    SetPenGreen(0);
    SetPenBlue(0);
    //    pen_red = 0;
    //    pen_green = 0;
    //    pen_blue = 0;
}

void ImageMaker::LoadImage(string filename) {
    int maxColor;
    ifstream myFile;
    if (!myFile.is_open()) {
        throw "File failed to open";
    }
    // read contents of file
    while (myFile >> magic >> width >> height >> maxColor) {
        if (magic != "P3") {
            throw "Bad magic number";
        }
        if (width > MAX_WIDTH) {
            throw "Width out of bounds";
        }
        if (height > MAX_HEIGHT)
            throw "Height out of bounds";
        if (maxColor != MAX_COLOR) {
            throw "Max color range not 255";
        }
        break;
    }

    // start a new while loop to start storing color values in (x, y)
    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; j < MAX_HEIGHT; j++) {
            while (myFile >> pen_red >> pen_green >> pen_blue) {
                if (pen_red < 0 || pen_red > MAX_COLOR || pen_green < 0 || pen_green > MAX_COLOR || pen_blue < 0 || pen_blue > MAX_COLOR) {
                    throw "Color value invalid";
                }
                image[i][j][RED] = pen_red;
                image[i][j][GREEN] = pen_green;
                image[i][j][BLUE] = pen_blue;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; j < MAX_HEIGHT; j++) {
            image[i][j][0] = 255;
            image[i][j][1] = 255;
            image[i][j][2] = 255;
        }
    }
}

void ImageMaker::SaveImage(string filename) {
    // write to the file
    ofstream myFile;
    myFile.open(filename);
    if (width == 0 || height == 0) {
        throw "Image must have non-zero dimensions";
    }
    // write header information
    //myFile << magic; (?)
    myFile << "P3" << endl << width << " " << height << endl << MAX_COLOR << endl;
    // write out the RGB values from the private variable "image"
    for (int i = 0; i < MAX_WIDTH; i++) {
        for (int j = 0; j < MAX_HEIGHT; j++) {
            myFile << image[i][j][RED] << " " << image[i][j][GREEN] << " " << image[i][j][BLUE] << " ";
        }
    }
    myFile.close();
}

int ImageMaker::GetWidth() {
    return width;
}

int ImageMaker::GetHeight() {
    return height;
}

void ImageMaker::SetWidth(int width) {
    if (width < 0 || width > MAX_WIDTH)
        throw "Width out of bounds";
    this->width = width;
}

void ImageMaker::SetHeight(int height) {
    if (height < 0 || height > MAX_HEIGHT)
        throw "Height out of bounds";
    this->height = height;
}

int ImageMaker::GetPenRed() {
    return pen_red;
}

int ImageMaker::GetPenGreen() {
    return pen_green;
}

int ImageMaker::GetPenBlue() {
    return pen_blue;
}

void ImageMaker::SetPenRed(int newR) {
    if (newR < 0 || newR > MAX_COLOR)
        throw "Color value invalid";
    pen_red = newR;
}

void ImageMaker::SetPenGreen(int newG) {
    if (newG < 0 || newG > MAX_COLOR)
        throw "Color value invalid";
    pen_green = newG;
}

void ImageMaker::SetPenBlue(int newB) {
    if (newB < 0 || newB > MAX_COLOR)
        throw "Color value invalid";
    pen_blue = newB;
}

void ImageMaker::DrawPixel(int x, int y) {

}

void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2) {

}

void ImageMaker::DrawLine(int x1, int y1, int x2, int y2) {

}

bool ImageMaker::PointInBounds(int x, int y) {
    if (x < 0 || x > width || y < 0 || y > height)
        return false;
    return true;
}
