/**
 * Created by Varick Erickson on 1/25/2021.
 *
 * You should not remove or change any of the utility functions in this file.
 *
 * Utilities used by the test are placed here.
 */
#ifndef IMAGEMAKER_UNIT_UTILS_H
#define IMAGEMAKER_UNIT_UTILS_H

#include <iostream>
#include <fstream>
#include "../ImageMaker.h"

// Compares two ppm images
// Ignores differences in whitespace.
void compare_images(string imgFilename1, string imgFilename2) {
    // Compare the two files

    ifstream img1File;
    img1File.open(imgFilename1);
    if (img1File.fail()) {
        // If this fails, then file was removed
        // or SaveImage doesn't work
        INFO("File " << imgFilename1 << " did not open.");
        INFO("Possible causes: File may have been moved or SaveImage did not save the file");
        FAIL();
    }


    ifstream img2File;
    img2File.open(imgFilename2);
    if (img2File.fail()) {
        // If this fails, then file was removed
        // or SaveImage doesn't work
        INFO("File " << imgFilename2 << " did not open.");
        INFO("Possible causes:");
        INFO("Working directory not correct in run configuration (see guide on Blackboard).");
        INFO("SaveImage did not save the file. Many tests require SaveImage to work.");
        INFO("File may have been moved. Make sure you didn't delete or move anything in 'images' folder");
        FAIL();
    }


    // Check to see that the files match.
    int px1, px2;
    string magic1, magic2;
    int width1, height1, maxval1;
    int width2, height2, maxval2;
    img1File >> magic1 >> width1 >> height1 >> maxval1;
    img2File >> magic2 >> width2 >> height2 >> maxval2;

    // Check if the header matcher
    if(magic1 != magic2) {
        INFO(imgFilename1 << " did not match " << imgFilename2);
        INFO("Magic number doesn't match");
        INFO("Magic number " << imgFilename1 << ": " << magic1);
        INFO("Magic number " << imgFilename2 << ": " << magic2);
        FAIL();
    }

    if (width1 != width2) {
        INFO(imgFilename1 << " did not match " << imgFilename2);
        INFO("Widths don't match");
        INFO("Width " << imgFilename1 << ": " << width1);
        INFO("Width " << imgFilename2 << ": " << width2);
        FAIL();
    }

    if (height1 != height2) {
        INFO(imgFilename1 << " did not match " << imgFilename2);
        INFO("Heights don't match");
        INFO("Height " << imgFilename1 << ": " << height1);
        INFO("Height " << imgFilename2 << ": " << height2);
        FAIL();
    }
    if (maxval1 != maxval2){
        INFO("Max color values don't match");
        INFO("Max color value " << imgFilename1 << ": " << maxval1);
        INFO("Max color value " << imgFilename2 << ": " << maxval2);
        FAIL();
    }

    // Every value should be identical.
    int i = 0;
    string color[3] = {"Red", "Green", "Blue" };
    while (img1File >> px1 && img2File >> px2) {
        string colorLab = color[i%3];  // what color are we looking at?
        if (px1 != px2) {
            int y = i/(width1*3);       // each row should have width*3 pixel values
            int x = (i%(width1*3))/3;   // figure out the x coordinate
            INFO(imgFilename1 << " did not match " << imgFilename2);
            INFO(colorLab << " pixel values do not match at coordinate " << "(" << x << ", " << y << ")");
            INFO(colorLab << " value " << imgFilename1 << ": " << px1);
            INFO(colorLab << " value " << imgFilename2 << ": " << px2);
            FAIL();
        }
        i++;
    }

    if (i < width1*height1*3) {
        INFO(imgFilename1 << " did not match " << imgFilename2);
        INFO("Expected " << width1*height1 << " pixels, but only read " << i/3 << "pixels.");
        INFO("This usually means that the SaveImage function did not save the pixel information correctly.");
        INFO("Make sure you are writing values from the private variable image to the file");
        INFO("Make sure you have white space separating the pixel values.");
        FAIL();
    }
    img1File.close();
    img2File.close();

    SUCCEED();
}

// Used for chaos_game
struct PointT {
    int x;
    int y;
};

// https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle
void draw_fractal(ImageMaker& img) {
    img.SetWidth(800);
    img.SetHeight(800);

    PointT pts[3];
    pts[0].x = img.GetWidth()/2;
    pts[1].x = 0;
    pts[2].x = img.GetWidth()-1;

    pts[0].y = 0;
    pts[1].y = img.GetWidth()-1;
    pts[2].y = img.GetWidth()-1;

    PointT r;
    r.x = rand()%img.GetWidth();
    r.y = rand()%img.GetHeight();
    for (int i = 0; i < 1000000; i++) {
        PointT p = pts[rand()%3];
        int x = (p.x + r.x)/2;
        int y = (p.y + r.y)/2;

        int red = x%256;
        int green = y%256;
        int blue = (red + green)%256;
        img.SetPenRed(red);
        img.SetPenGreen(green);
        img.SetPenBlue(blue);

        img.DrawPixel(x, y);

        r.x = x;
        r.y = y;
    }

    img.SaveImage("test_images/sierpiski_test.ppm");
}


#endif //IMAGEMAKER_UNIT_UTILS_H
