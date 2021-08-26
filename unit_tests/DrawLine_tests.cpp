/**
 * Created by Varick Erickson on 1/25/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 * If you want to run your own tests, it is recommended you use the provided
 * ImageMaker_driver.cpp file.
 *
 * The purpose of this file is to test the DrawLine functions.
 */

#include "catch.hpp"
#include <iostream>
#include "../ImageMaker.h"
#include "unit_utils.h"

// Just in case M_PI is not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

TEST_CASE("Testing DrawLine") {
    ImageMaker* img = new ImageMaker();
    img->SetWidth(MAX_HEIGHT / 4);
    img->SetHeight(MAX_WIDTH / 4);

    SECTION("Testing DrawLine with negative x1 values") {
        for (int x = -MAX_WIDTH; x < 0; x++) {
            for (int y = 0; y < img->GetHeight(); y++) {
                REQUIRE_THROWS_WITH(img->DrawLine(x, y, 0, 0), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawLine with negative x2 values") {
        for (int x = -MAX_WIDTH; x < 0; x++) {
            for (int y = 0; y < img->GetHeight(); y++) {
                REQUIRE_THROWS_WITH(img->DrawLine(0, 0, x, y), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawLine with negative y1 values") {
        for (int x = 0; x < img->GetWidth(); x++) {
            for (int y = -MAX_HEIGHT; y < 0; y++) {
                REQUIRE_THROWS_WITH(img->DrawLine(x, y, 0, 0), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawLine with negative y2 values") {
        for (int x = 0; x < img->GetWidth(); x++) {
            for (int y = -MAX_HEIGHT; y < 0; y++) {
                REQUIRE_THROWS_WITH(img->DrawLine(0, 0, x, y), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawLine with negative x1,y1 values") {
        for (int x = -MAX_WIDTH; x < 0; x++) {
            for (int y = -MAX_HEIGHT; y < 0; y++) {
                REQUIRE_THROWS_WITH(img->DrawLine(x, y, 0, 0), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawLine with negative x2,y2 values") {
        for (int x = -MAX_WIDTH; x < 0; x++) {
            for (int y = -MAX_HEIGHT; y < 0; y++) {
                REQUIRE_THROWS_WITH(img->DrawLine(0, 0, x, y), "Point out of bounds");
            }
        }
    }
    delete img;

    SECTION("Test (x1,y1) == (x2,y2)") {
        // Should behave the same as drawing a pixel at x1,y1
        int width = 20;
        int height = 10;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                ImageMaker *img1, *img2;
                img1 = new ImageMaker();
                img2 = new ImageMaker();
                img1->SetWidth(width);
                img1->SetHeight(height);
                img2->SetWidth(width);
                img2->SetHeight(height);

                img1->DrawLine(x, y, x, y);
                img2->DrawPixel(x, y);
                img1->SaveImage("test_images/xy1.ppm");
                img2->SaveImage("test_images/xy2.ppm");
                delete img1;
                delete img2;

                compare_images("test_images/xy1.ppm", "test_images/xy2.ppm");
            }
        }
    }
    SECTION("Testing vertical lines") {

        ImageMaker* img = new ImageMaker();
        img->SetWidth(10);
        img->SetHeight(10);
        for (int x = 0; x < img->GetWidth(); x+=2) {
            img->DrawLine(x,0,x,img->GetHeight()-1);
        }
        img->SaveImage("test_images/zebra_test.ppm");

        compare_images("images/zebra.ppm", "test_images/zebra_test.ppm");
        delete img;
    }
    SECTION("Testing typical use case (draw a house)"){
        ImageMaker* img = new ImageMaker();
        img->SetWidth(500);
        img->SetHeight(450);

        // Set pen color
        img->SetPenRed(155);
        img->SetPenGreen(10);
        img->SetPenBlue(150);

        // roof
        img->DrawLine(50,200, 200, 50);
        img->DrawLine(200, 50, 350, 200);
        img->DrawLine(50,200, 350, 200);

        // walls
        img->DrawLine(100,200, 100, 400);
        img->DrawLine(300,200, 300, 400);

        // floor
        img->DrawLine(100,400, 300, 400);

        img->SaveImage("test_images/house_test.ppm");

        delete img;
        compare_images("images/house.ppm", "test_images/house_test.ppm");

    }
    SECTION("Testing coordinate order") {

        int width = 10;
        int height = 5;

        // Try every combination of points in a 10x5 image
        for (int x1 = 0; x1 < width; x1++) {
            for (int y1 = 0; y1 < height; y1++) {
                for (int x2 = 0; x2 < width; x2++) {
                    for (int y2 = 0; y2 < height; y2++) {

                        double angle = abs(atan2(y2 - y1, x2 - x1)/M_PI*180);

                        // Rounding issues causes slightly different lines
                        // to be drawn when reversing coordinate order.
                        // This only occurs with VERY shallow angles.
                        // We only test slope angles between 15 and 165
                        if (angle >= 15 && angle <= 165) {

                            // Create two blank images
                            ImageMaker *img1, *img2;
                            img1 = new ImageMaker();
                            img2 = new ImageMaker();
                            img1->SetWidth(width);
                            img1->SetHeight(height);
                            img2->SetWidth(width);
                            img2->SetHeight(height);

                            // Try both orders and save the results.
                            img1->DrawLine(x1, y1, x2, y2);
                            img2->DrawLine(x2, y2, x1, y1);
                            img1->SaveImage("test_images/line1_order_test.ppm");
                            img2->SaveImage("test_images/line2_order_test.ppm");
                            delete img1;
                            delete img2;

                            // Check to see if they are both the same.
                            // If you fail this test, it may be helpful to look at the contents of these files.
                            compare_images("test_images/line1_order_test.ppm", "test_images/line2_order_test.ppm");
                        }
                    }
                }
            }
        }
    }
}
