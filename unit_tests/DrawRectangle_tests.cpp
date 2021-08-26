/**
 * Created by Varick Erickson on 1/25/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 * If you want to run your own tests, it is recommended you use the provided
 * ImageMaker_driver.cpp file.
 *
 * The purpose of this file is to test DrawRectangle.
 */

#include "catch.hpp"
#include <iostream>
#include "../ImageMaker.h"
#include "unit_utils.h"

TEST_CASE("Testing DrawRectangle") {
    ImageMaker* img = new ImageMaker();
    img->SetWidth(MAX_HEIGHT / 4);
    img->SetHeight(MAX_WIDTH / 4);

    SECTION("Testing DrawRectangle with negative x1 values") {
        for (int x = -MAX_WIDTH; x < 0; x++) {
            for (int y = 0; y < img->GetHeight(); y++) {
                REQUIRE_THROWS_WITH(img->DrawRectangle(x, y, 0, 0), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawRectangle with negative x2 values") {
        for (int x = -MAX_WIDTH; x < 0; x++) {
            for (int y = 0; y < img->GetHeight(); y++) {
                REQUIRE_THROWS_WITH(img->DrawRectangle(0, 0, x, y), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawRectangle with negative y1 values") {
        for (int x = 0; x < img->GetWidth(); x++) {
            for (int y = -MAX_HEIGHT; y < 0; y++) {
                REQUIRE_THROWS_WITH(img->DrawRectangle(x, y, 0, 0), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawRectangle with negative y2 values") {
        for (int x = 0; x < img->GetWidth(); x++) {
            for (int y = -MAX_HEIGHT; y < 0; y++) {
                REQUIRE_THROWS_WITH(img->DrawRectangle(0, 0, x, y), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawRectangle with negative x1,y1 values") {
        for (int x = -MAX_WIDTH; x < 0; x++) {
            for (int y = -MAX_HEIGHT; y < 0; y++) {
                REQUIRE_THROWS_WITH(img->DrawRectangle(x, y, 0, 0), "Point out of bounds");
            }
        }
    }
    SECTION("Testing DrawRectangle with negative x2,y2 values") {
        for (int x = -MAX_WIDTH; x < 0; x++) {
            for (int y = -MAX_HEIGHT; y < 0; y++) {
                REQUIRE_THROWS_WITH(img->DrawRectangle(0, 0, x, y), "Point out of bounds");
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
                ImageMaker* img1 = new ImageMaker();
                ImageMaker* img2 = new ImageMaker();
                img1->SetWidth(width);
                img1->SetHeight(height);
                img2->SetWidth(width);
                img2->SetHeight(height);

                img1->DrawRectangle(x, y, x, y);
                img2->DrawPixel(x, y);
                img1->SaveImage("test_images/xy1.ppm");
                img2->SaveImage("test_images/xy2.ppm");
                compare_images("test_images/xy1.ppm", "test_images/xy2.ppm");
                delete img1;
                delete img2;
            }
        }
    }
    SECTION("Testing coordinate order") {

        int width = 10;
        int height = 5;
        // Try every combination of points in 10x5 image
        for (int x1 = 0; x1 < width; x1++) {
            for (int y1 = 0; y1 < height; y1++) {
                for (int x2 = 0; x2 < width; x2++) {
                    for (int y2 = 0; y2 < height; y2++) {
                        // Create two blank images
                        ImageMaker* img1 = new ImageMaker();
                        ImageMaker* img2 = new ImageMaker();
                        img1->SetWidth(width);
                        img1->SetHeight(height);
                        img2->SetWidth(width);
                        img2->SetHeight(height);

                        // Try both orders
                        img1->DrawRectangle(x1, y1, x2, y2);
                        img2->DrawRectangle(x2, y2, x1, y1);
                        img1->SaveImage("test_images/rect1_order_test.ppm");
                        img2->SaveImage("test_images/rect2_order_test.ppm");

                        // check to see if they are both the same.
                        compare_images("test_images/rect1_order_test.ppm", "test_images/rect2_order_test.ppm");
                        delete img1;
                        delete img2;
                    }
                }
            }
        }
    }
}
