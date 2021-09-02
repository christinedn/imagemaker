//
// Assignment Created by Varick Erickson
//

#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <cmath>
#include <fstream>

const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 800;
const int MAX_COLOR = 255;
enum COLOR { RED, GREEN, BLUE };

using namespace std;

//  Please put your pre and post comments in this file. See page 139 in the textbook.

class ImageMaker
{
public:
    /* Function: Constructor that takes in no parameters
     * Precondition: None
     * Postcondition: An ImageMaker object will be created
     */
    ImageMaker();
    /* Function: Constructor that takes in a filename
     * Precondition: File name must exist
     * Postcondition: Data is stored within the object variables
     * The function throws a "File failed to open" error if file cannot be opened
     */
    ImageMaker(string filename);
    /*
     * Function: Opens image with filename and stores information into the object's member variables
     * Precondition: File name must exist
     * Postcondition: Data is stored within the object variables
     * The function throws a "File failed to open" error if file cannot be opened
     * The function throws a "Bad magic number" if the magic number is not P3
     * The function throws a "Width out of bounds" if the width is negative or greater than MAX_WIDTH
     * The function throws a "Height out of bounds" if the height is negative or greater than MAX_HEIGHT
     * The function throws a "Max color range not 255" if the max color is not 255
     * The function throws a "Color value invalid" tf any of the color values is negative or greater than 255
     */
    void LoadImage(string filename);
    /*
     * Function: Opens image with filename and stores information into the object's member variables
     * Precondition: File name must exist
     * Postcondition: Data is stored within the object variables
     * The function throws a "File failed to open" error if file cannot be opened
     * The function throws a "Bad magic number" error if the magic number is not P3
     * The function throws a "Width out of bounds" error if the width is negative or greater than MAX_WIDTH
     * The function throws a "Height out of bounds" error if the height is negative or greater than MAX_HEIGHT
     * The function throws a "Max color range not 255" error if the max color is not 255
     * The function throws a "Color value invalid" error if any of the color values is negative or greater than 255
     */
    void SaveImage(string filename);
    /*
     * Function: Stores the data of the object into a file name
     * Precondition: Width and height must have non-zero dimensions
     * Postcondition: A output file is created with magic number, width, height, max color, and RGB pixels
     * The function throws an "Image must have non-zero dimensions" error if width and height have non-zero dimensions
     */

    // Size functions
    /*
     * Function: Returns the width
     * Precondition: None
     * Postcondition: Width is returned
     */
    int GetWidth();
    /*
     * Function: Returns the height
     * Precondition: None
     * Postcondition: Height is returned
     */
    int GetHeight();
    /*
     * Function: Sets the width
     * Precondition: Width must be positive and less than MAX_WIDTH
     * Postcondition: Width will be set.
     * Function throws a "Width out of bounds" error if width is negative or greater than MAX_WIDTH
     */
    void SetWidth(int width);
    /*
     * Function: Sets the height
     * Precondition: Height must be positive and less than MAX_HEIGHT
     * Postcondition: Height will be set.
     * Function throws a "Height out of bounds" error if height is negative or greater than MAX_HEIGHT
     */
    void SetHeight(int height);

    // Color functions
    /*
     * Function: Returns the number of red
     * Precondition: None
     * Postcondition: Number of red is returned
     */
    int GetPenRed();
    /*
     * Function: Returns the number of green
     * Precondition: None
     * Postcondition: Number of green is returned
     */
    int GetPenGreen();
    /*
     * Function: Returns the number of blue
     * Precondition: None
     * Postcondition: Number of blue is returned
     */
    int GetPenBlue();
    /*
     * Function: Sets the number of red
     * Precondition: Red must be positive and less than 255
     * Postcondition: pen_red will be set
     * Throws a "Color value invalid" error if number is negative or greater than 255
     */
    void SetPenRed(int newR);
    /*
     * Function: Sets the number of green
     * Precondition: Green must be positive and less than 255
     * Postcondition: pen_green will be set
     * Throws a "Color value invalid" error if number is negative or greater than 255
     */
    void SetPenGreen(int newG);
    /*
     * Function: Sets the number of blue
     * Precondition: Blue must be positive and less than 255
     * Postcondition: pen_blue will be set
     * Throws a "Color value invalid" error if number is negative or greater than 255
     */
    void SetPenBlue(int newB);

    // Drawing methods
    // These methods will use the current red, green, blue values of the pen
    /* Function: Draws a single pixel
     * Precondition: Values x and y must be positive and less than width and height
     * Postcondition: A pixel will have been drawn using current pen color
     * Function will throw a "Point out of bounds" error if either x or y is negative or greater than width and height
     */
    void DrawPixel(int x, int y);
    /* Function: Draws a rectangle
     * Preconditon: Values x and y must be positive and less than width and height
     * Postcondition: A rectangle will have been draw using current pen color
     * Function will throw a "Point out of bounds" error if either x or y is negative or greater than width and height
     */
    void DrawRectangle(int x1, int y1, int x2, int y2);
    /* Function: Draws a line
     * Preconditon: Values x and y must be positive and less than width and height
     * Postcondition: A line will have been drawn using current pen color
     * Function will throw a "Point out of bounds" error if either x or y is negative or greater than width and height
     */
    void DrawLine(int x1, int y1, int x2, int y2);

private:
    string magic;
    int width;
    int height;
    int pen_red;    // Used by draw functions
    int pen_green;  // Used by draw functions
    int pen_blue;   // Used by draw functions
    bool PointInBounds(int x, int y);  // Not a bad idea to implement

               //   x          y
    short image[MAX_WIDTH][MAX_HEIGHT][3];
};

#endif //IMAGEMAKER_H
