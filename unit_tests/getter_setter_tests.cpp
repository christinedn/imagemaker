/**
 * Created by Varick Erickson on 1/25/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 * If you want to run your own tests, it is recommended you use the provided
 * ImageMaker_driver.cpp file.
 *
 * The purpose of this file is to test the various getters and setters.
 */

#include "catch.hpp"
#include "../ImageMaker.h"

TEST_CASE("Getter/Setter Tests") {
    ImageMaker img;
    SECTION("Testing GetWidth, GetHeight, SetWidth, SetHeight") {

        // Checking all valid widths
        for (int w = -MAX_WIDTH; w < MAX_WIDTH; w++) {
            if (w < 0 || w > MAX_WIDTH) {
                SECTION("Testing invalid input for SetWidth") {
                    REQUIRE_THROWS_WITH(img.SetWidth(w),"Width out of bounds");
                }
            }
            else {
                SECTION("Testing valid input for SetWidth") {
                    img.SetWidth(w);
                    REQUIRE(img.GetWidth() == w);
                }
            }
        }

        // Checking all valid heights
        for (int h = -MAX_HEIGHT; h < MAX_HEIGHT; h++) {
            if (h < 0 || h > MAX_HEIGHT) {
                SECTION("Testing invalid input for SetHeight") {
                    REQUIRE_THROWS_WITH(img.SetHeight(h),"Height out of bounds");
                }
            }
            else {
                SECTION("Testing valid height input for SetHeight") {
                    img.SetHeight(h);
                    REQUIRE(img.GetHeight() == h);
                }
            }
        }
    }

    SECTION("Testing Pen Color Functions") {

        // Check negative values and all
        for (int c = -255; c < 255; c++) {
            if (c < 0 || c >= 255 ) {
                SECTION("Testing invalid color input") {
                    REQUIRE_THROWS_WITH(img.SetPenRed(c), "Color value invalid");
                    REQUIRE_THROWS_WITH(img.SetPenGreen(c), "Color value invalid");
                    REQUIRE_THROWS_WITH(img.SetPenBlue(c), "Color value invalid");
                }
            } else {
                SECTION("Testing valid color inputs") {
                    img.SetPenRed(c);
                    REQUIRE(img.GetPenRed() == c);

                    img.SetPenGreen(c);
                    REQUIRE(img.GetPenGreen() == c);

                    img.SetPenBlue(c);
                    REQUIRE(img.GetPenBlue() == c);
                }
            }
        }
    }
}