/**
 * Created by Varick Erickson on 1/25/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 * If you want to run your own tests, it is recommended you use the provided
 * ImageMaker_driver.cpp file.
 *
 * The purpose of this file is to test the constructors.
 */

#include <iostream>
#include <istream>
#include "catch.hpp"
#include "unit_utils.h"
#include "../ImageMaker.h"

TEST_CASE("Constructor Tests") {

    SECTION("ImageMaker() Test (default constructor)") {
        ImageMaker* imgTest = new ImageMaker();
        SECTION("Check if default sizes are 0") {
            REQUIRE(imgTest->GetHeight() == 0);
            REQUIRE(imgTest->GetWidth() == 0);
        }
        SECTION("Check default pen color is black") {
            REQUIRE(imgTest->GetPenRed() == 0);
            REQUIRE(imgTest->GetPenGreen() == 0);
            REQUIRE(imgTest->GetPenBlue() == 0);
        }
        SECTION("Check if image matrix is initialized to white") {
            // Set image to max size and save the image without drawing anything
            imgTest->SetWidth(MAX_WIDTH);
            imgTest->SetHeight(MAX_HEIGHT);
            imgTest->SaveImage("test_images/bg_test.ppm");

            compare_images("images/bg.ppm","test_images/bg_test.ppm");
        }
        delete imgTest;
    }

    SECTION("ImageMaker(filename) Test") {

        SECTION("Check default pen color is black") {
            ImageMaker* imgTest = new ImageMaker("images/cake.ppm");
            REQUIRE(imgTest->GetPenRed() == 0);
            REQUIRE(imgTest->GetPenGreen() == 0);
            REQUIRE(imgTest->GetPenBlue() == 0);
            delete imgTest;
        }
        SECTION("Test valid cake image") {
            ImageMaker* imgCake = new ImageMaker("images/cake.ppm");
            imgCake->SaveImage("test_images/cake_copy.ppm");
            compare_images("test_images/cake_copy.ppm", "images/cake.ppm");
            delete imgCake;
        }
        SECTION("Test valid block image") {
            ImageMaker* imgBlock = new ImageMaker("images/blocks.ppm");
            imgBlock->SaveImage("test_images/blocks_copy.ppm");
            compare_images("test_images/blocks_copy.ppm", "images/blocks.ppm");
            delete imgBlock;
        }
        SECTION("Check if matrix is initialized to white after loading") {
            ImageMaker* imgTest = new ImageMaker("images/cake.ppm");
            // Set image to max size and save the image without drawing anything
            imgTest->SetWidth(MAX_WIDTH);
            imgTest->SetHeight(MAX_HEIGHT);
            imgTest->SaveImage("test_images/cake_bg_test.ppm");

            compare_images("images/cake_bg.ppm","test_images/cake_bg_test.ppm");
        }
        SECTION("Test invalid headers") {
            SECTION("Test bad magic") {
                REQUIRE_THROWS_WITH(delete new ImageMaker("images/bad_magic.ppm"), "Bad magic number");
            }
            SECTION("Test negative width") {
                REQUIRE_THROWS_WITH(delete new ImageMaker("images/bad_width_neg.ppm"), "Width out of bounds");
            }
            SECTION("Test width > MAX_WIDTH") {
                REQUIRE_THROWS_WITH(delete new ImageMaker("images/bad_width_max.ppm"), "Width out of bounds");
            }
            SECTION("Test negative height") {
                REQUIRE_THROWS_WITH(delete new ImageMaker("images/bad_height_neg.ppm"), "Height out of bounds");
            }
            SECTION("Test height > MAX_HEIGHT") {
                REQUIRE_THROWS_WITH(delete new ImageMaker("images/bad_height_max.ppm"), "Height out of bounds");
            }
            SECTION("Test bad color max (should be 255)") {
                REQUIRE_THROWS_WITH(delete new ImageMaker("images/bad_color_max.ppm"), "Max color range not 255");
            }
            SECTION("Test bad pixel color") {
                REQUIRE_THROWS_WITH(delete new ImageMaker("images/bad_pixel_value.ppm"), "Color value invalid");
            }
        }
    }
}