/**
 * Created by Varick Erickson on 1/25/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 * If you want to run your own tests, it is recommended you use the provided
 * ImageMaker_driver.cpp file.
 *
 * The purpose of this file is perform saving and loading tests.
 */

#include "catch.hpp"
#include "../ImageMaker.h"
#include "unit_utils.h"
#include <iostream>
#include <istream>

TEST_CASE("Saving and Loading Tests") {
    SECTION("Testing basic save functionality") {
        ImageMaker* img = new ImageMaker();
        int width = 400;
        int height = 200;
        img->SetWidth(width);
        img->SetHeight(height);
        img->SaveImage("test_images/save_test.ppm");

        compare_images("test_images/save_test.ppm","images/blank.ppm");
        delete img;
    }
    SECTION("Testing save with width 0") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->SaveImage("test_images/bad.ppm"), "Image must have non-zero dimensions");
        delete img;
    }
    SECTION("Test loading using cake.ppm") {
        ImageMaker* img = new ImageMaker();
        img->LoadImage("images/cake.ppm");
        img->SaveImage("test_images/cake_copy.ppm");
        delete img;

        // Check to see if the cake is a lie
        compare_images("test_images/cake_copy.ppm", "images/cake.ppm");
    }
    SECTION("Test bad magic") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->LoadImage("images/bad_magic.ppm"), "Bad magic number");
        delete img;
    }
    SECTION("Test negative width") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->LoadImage("images/bad_width_neg.ppm"), "Width out of bounds");
        delete img;
    }
    SECTION("Test width > MAX_WIDTH") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->LoadImage("images/bad_width_max.ppm"), "Width out of bounds");
        delete img;
    }
    SECTION("Test negative height") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->LoadImage("images/bad_height_neg.ppm"), "Height out of bounds");
        delete img;
    }
    SECTION("Test height > MAX_HEIGHT") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->LoadImage("images/bad_height_max.ppm"), "Height out of bounds");
        delete img;
    }
    SECTION("Test bad magic") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->LoadImage("images/bad_magic.ppm"), "Bad magic number");
        delete img;
    }
    SECTION("Test bad color max (should be 255)") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->LoadImage("images/bad_color_max.ppm"), "Max color range not 255");
        delete img;
    }
    SECTION("Test bad pixel color") {
        ImageMaker* img = new ImageMaker();
        REQUIRE_THROWS_WITH(img->LoadImage("images/bad_pixel_value.ppm"), "Color value invalid");
        delete img;
    }
}




