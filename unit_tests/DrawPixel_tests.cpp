/**
 * Created by Varick Erickson on 1/25/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 * If you want to run your own tests, it is recommended you use the provided
 * ImageMaker_driver.cpp file.
 *
 * The purpose of this file is to test DrawPixel.  Several functions here
 * use the DrawPixel function to draw a fractal.  You do not need to understand these
 * functions.
 */

#include "catch.hpp"
#include <math.h>
#include <complex>
#include <iostream>
#include <istream>
#include "unit_utils.h"
#include "../ImageMaker.h"

TEST_CASE("Testing Draw Pixel") {
    SECTION("Testing valid input") {
        SECTION("Draw Test") {
            ImageMaker* img = new ImageMaker();
            img->SetWidth(400);
            img->SetHeight(400);
            for (int x = 0; x < img->GetWidth(); x++) {
                for (int y = 0; y < img->GetHeight(); y++) {
                    img->SetPenRed(x%256);
                    img->SetPenGreen(y%256);
                    img->SetPenBlue((x+y)%256);
                    img->DrawPixel(x, y);
                }
            }
            img->SaveImage("test_images/colorsq_test.ppm");
            delete img;

            // REQUIRE checks are in compare_images (see unit_util.h)
            compare_images("images/colorsq.ppm", "test_images/colorsq_test.ppm");
        }
    }
    SECTION("Testing invalid coordinates") {
        ImageMaker* img = new ImageMaker();
        SECTION("Testing DrawPixel with negative x values") {
            for (int x = -MAX_WIDTH; x < 0; x++) {
                for (int y = 0; y < img->GetHeight(); y++) {
                    REQUIRE_THROWS_WITH(img->DrawPixel(x, y), "Point out of bounds");
                }
            }
        }
        SECTION("Testing DrawPixel with negative y values") {
            for (int x = 0; x < img->GetWidth(); x++) {
                for (int y = -MAX_HEIGHT; y < 0; y++) {
                    REQUIRE_THROWS_WITH(img->DrawPixel(x, y), "Point out of bounds");
                }
            }
        }
        SECTION("Testing DrawPixel with negative x,y values") {
            for (int x = -MAX_WIDTH; x < 0; x++) {
                for (int y = -MAX_HEIGHT; y < 0; y++) {
                    REQUIRE_THROWS_WITH(img->DrawPixel(x, y), "Point out of bounds");
                }
            }
        }
        SECTION("Testing DrawPixel(0,0) with image width and height 0") {
            REQUIRE_THROWS_WITH(img->DrawPixel(0,0),"Point out of bounds");
        }
        delete img;
    }
}