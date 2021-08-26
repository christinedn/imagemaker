#include "ImageMaker.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

// Demo message.  That or it demonstrates the "king of flavor".
void demo_msg() {
    cout << "This program demos the features of the ImageMaker class." << endl;
    cout << "You do not need to modify anything in the program, but" << endl;
    cout << "you are welcome to change/use it for debugging." << endl;

    cout << endl;

    cout << "The unit_tests folder contain the tests that will be" << endl;
    cout << "used for grading.  Do not change these! If you do" << endl;
    cout << "accidentally change them, I suggest using the git revert" << endl;
    cout << "command to bring the files back to the original state." << endl;
}

void draw_house() {
    ImageMaker img;

    // Set size of house to 450x450
    img.SetWidth(450);
    img.SetHeight(450);

    // Draw brown roof (brown triangle)
    img.SetPenRed(165);
    img.SetPenGreen(42);
    img.SetPenBlue(42);
    img.DrawLine(50,200, 200, 50);
    img.DrawLine(200, 50, 350, 200);
    img.DrawLine(50,200, 350, 200);

    // Draw red brick walls (183,50,57)
    img.SetPenRed(255);
    img.SetPenGreen(50);
    img.SetPenBlue(57);

    // Draw bricks. Each brick is 25x20.
    for (int y = 200; y < 400; y+=20) {
        for (int x = 100; x < 300; x+=25) {
            img.DrawRectangle(x,y,x+25,y+20);
        }
    }

    // Draw brown door
    img.SetPenRed(165);
    img.SetPenGreen(42);
    img.SetPenBlue(42);
    for (int y = 280; y <= 400; y++) {
        img.DrawLine(175,y,225,y);
    }

    img.SaveImage("red_brick_house.ppm");
}

// Used for chaos_game
struct PointT {
    int x;
    int y;
};

// https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle
void chaos_game() {

    ImageMaker img;
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

        img.DrawPixel(x, y);

        r.x = x;
        r.y = y;
    }

    img.SaveImage("sierpiski.ppm");
}


struct RGB_T {
    RGB_T(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    int r;
    int g;
    int b;
};


// https://en.wikipedia.org/wiki/Bilinear_interpolation
void gradient_square() {
    ImageMaker img;
    img.SetWidth(800);
    img.SetHeight(800);

    RGB_T topLeft(255,0,0);     // Red in upper left
    RGB_T topRight(0,255,0);    // Green in upper right
    RGB_T bottomLeft(0,0,255);  // Blue in lower left
    RGB_T bottomRight(255, 255, 255);   // White in lower right

    // Fill using bilinear interpolation
    for(int r=0;r<img.GetWidth();r++){
        for(int c=0;c<img.GetHeight();c++){
            float oneMinusX=float(img.GetWidth()-1-r)/(img.GetWidth()-1);
            float oneMinusY=float(img.GetHeight()-1-c)/(img.GetHeight()-1);

            int red = topLeft.r*oneMinusX*oneMinusX*oneMinusY +
                      topRight.r*oneMinusY*r/float(img.GetHeight()-1) +
                      bottomLeft.r*oneMinusX*c/float(img.GetWidth()-1) +
                      bottomRight.r*r*c/(float(img.GetWidth()-1)*(img.GetHeight()-1));

            int green = topLeft.g*oneMinusX*oneMinusX*oneMinusY +
                        topRight.g*oneMinusY*r/float(img.GetHeight()-1) +
                        bottomLeft.g*oneMinusX*c/float(img.GetWidth()-1) +
                        bottomRight.g*r*c/(float(img.GetWidth()-1)*(img.GetHeight()-1));

            int blue = topLeft.b*oneMinusX*oneMinusX*oneMinusY +
                       topRight.b*oneMinusY*r/float(img.GetHeight()-1) +
                       bottomLeft.b*oneMinusX*c/float(img.GetWidth()-1) +
                       bottomRight.b*r*c/float((img.GetWidth()-1)*(img.GetHeight()-1));

            img.SetPenRed(red);
            img.SetPenGreen(green);
            img.SetPenBlue(blue);
            img.DrawPixel(c,r);

        }
    }
    img.SaveImage("gradient_800x800.ppm");

}

int main() {

    // Feel free to add your own code here for testing purposes.

    demo_msg();         // Welcome message

    cout << "Drawing house to demo DrawLine and DrawRectangle." << endl;
    draw_house();       // Demos DrawLine and DrawRectangle

    cout << "Drawing fractal and gradient square to demo DrawPixel." << endl;
    chaos_game();       // Demos DrawPixel
    gradient_square();  // Demos DrawPixel
    return 0;
}

