#include "ImageMaker.h"
#include <fstream>

ImageMaker::ImageMaker() {
    width = 0;
    height = 0;
    pen_red = 0;
    pen_green = 0;
    pen_blue = 0;
    // initialize variable image matrix to be white
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            image[x][y][RED] = 255;
            image[x][y][GREEN] = 255;
            image[x][y][BLUE] = 255;
        }
    }
}

ImageMaker::ImageMaker(string filename) {
    // initialize variable image matrix to be white
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            image[x][y][RED] = 255;
            image[x][y][GREEN] = 255;
            image[x][y][BLUE] = 255;
        }
    }
    // load ppm into the image matrix
    LoadImage(filename);
    // setting the default pen color to black (0, 0, 0)
    pen_red = 0;
    pen_green = 0;
    pen_blue = 0;
}

void ImageMaker::LoadImage(string filename) {
    int maxColor;
    ifstream myFile;
    myFile.open(filename);
    if (!myFile.is_open())
        throw "File failed to open";

    // read contents of file
    myFile >> magic >> width >> height >> maxColor;
    if (magic != "P3")
        throw "Bad magic number";

    if (width < 0 || width > MAX_WIDTH)
        throw "Width out of bounds";

    if (height < 0 || height > MAX_HEIGHT)
        throw "Height out of bounds";

    if (maxColor != MAX_COLOR)
        throw "Max color range not 255";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            myFile >> image[x][y][RED] >> image[x][y][GREEN] >> image[x][y][BLUE];
            if (image[x][y][RED] < 0 || image[x][y][RED] > MAX_COLOR || image[x][y][GREEN] < 0 || image[x][y][GREEN] > MAX_COLOR || image[x][y][BLUE] < 0 || image[x][y][BLUE] > MAX_COLOR)
                throw "Color value invalid";
        }
    }
    myFile.close();
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
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            myFile << image[x][y][RED] << " " << image[x][y][GREEN] << " " << image[x][y][BLUE] << " ";
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
    if (!PointInBounds(x, y))
        throw "Point out of bounds";
    image[x][y][RED] = pen_red;
    image[x][y][GREEN] = pen_green;
    image[x][y][BLUE] = pen_blue;

}

void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2) {
    if (!PointInBounds(x1, y1) || !PointInBounds(x2, y2))
        throw "Point out of bounds";

    // draws a single pixel
    if ((x1 == x2) && (y2 == y1)) {
        DrawPixel(x1, y1);
        return;
    }

    // call DrawLine() 4 times to draw a rectangle
    // draw the top horizontal line
    DrawLine(x1, y1, x2, y1);
    // draw the bottom horizontal line
    DrawLine(x1, y2, x2, y2);
    // draw the left vertical line
    DrawLine(x1, y1, x1, y2);
    // draw the right vertical line
    DrawLine(x2, y1, x2, y2);

}

void ImageMaker::DrawLine(int x1, int y1, int x2, int y2) {
    if (!PointInBounds(x1, y1) || !PointInBounds(x2, y2))
        throw "Point out of bounds";

    // draws a single pixel
    if ((x1 == x2) && (y2 == y1)) {
        DrawPixel(x1, y1);
        return;
    }

    double x3, y3, m, b;
    // the if statements below will allow the same line to be produced whether user inputs DrawLine (2, 3, 6, 4) or DrawLine(6, 4, 2, 3)
    // to do this, find which x, y value is larger in the function parameters
    double largerX, smallerX, largerY, smallerY;
    if (x2 > x1) {
        largerX = x2;
        smallerX = x1;
    }
    if (x1 > x2) {
        largerX = x1;
        smallerX = x2;
    }
    if (y1 > y2) {
        largerY = y1;
        smallerY = y2;
    }
    if (y2 > y1) {
        largerY = y2;
        smallerY = y1;
    }
    // calculate slope
    y3 = y2-y1;
    x3 = x2-x1;
    if (x3 == 0.0) {
        // vertical slope
        for (int i = smallerY; i <= largerY; i++) {
            DrawPixel(x1, i);
        }
    } else {
        m = (double)y3/x3;
        // calculate b using x, y coordinate and slope
        b = y1-m*x1;

        // now that slope intercept formula is found, you can find any x, y coordinate along that line
        for (int tempX = smallerX; tempX <= largerX; tempX++) {
            double tempY = m*tempX+b;
            tempY = round(tempY);
            DrawPixel(tempX, tempY);
        }
    }
}

bool ImageMaker::PointInBounds(int x, int y) {
    if (x < 0 || x > width-1 || y < 0 || y > height-1)
        return false;
    return true;
}
