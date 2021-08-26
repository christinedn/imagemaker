cmake_minimum_required(VERSION 3.17)
project(ImageMaker)

# Increase the stack memory.  ppm images are big!
MATH(EXPR stack_size "10 * 1024 * 1024") # 10 Mb
# Windows settings
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
endif()

# Apple settings - Can be removed if you don't declare a lot of ImageMaker objects
if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-stack_size,10000000")
endif()

# Linux settings
if(UNIX AND NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,stack-size=${stack_size}")
endif()


# link with lld if available for speed
option(ENABLE_LLD "LLD" ON)
if (ENABLE_LLD)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=lld -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LLD_VERSION)
    if(LLD_VERSION MATCHES "LLD")
        SET(LLD_AVAILABLE ON)
        MESSAGE(STATUS "lld linker available")
    endif()
endif()

# Precompile catch2 to speed up re-compiles
add_library(catch2_main STATIC unit_tests/catch-main.cpp)
target_include_directories(catch2_main PUBLIC unit_tests/)

# Run basic driver test showing functionality.
add_executable(ImageMaker_Driver ImageMaker_driver.cpp ImageMaker.cpp)

# Run all tests
add_executable(ImageMaker_Test unit_tests/catch-main.cpp unit_tests/ImageMaker_tests.cpp ImageMaker.cpp)

# Test getters, setters, constructors, save and load
add_executable(Getter_Setter_Test unit_tests/catch-main.cpp unit_tests/getter_setter_tests.cpp ImageMaker.cpp)
add_executable(Constructor_Test unit_tests/catch-main.cpp unit_tests/constructor_tests.cpp ImageMaker.cpp)
add_executable(Save_Load_Test unit_tests/catch-main.cpp unit_tests/save_load_tests.cpp ImageMaker.cpp)

# Draw Tests (requires getters, setters, constructors, save and load to work)
add_executable(DrawPixel_Test unit_tests/catch-main.cpp unit_tests/DrawPixel_tests.cpp ImageMaker.cpp)
add_executable(DrawRectangle_Test unit_tests/catch-main.cpp unit_tests/DrawRectangle_tests.cpp ImageMaker.cpp)
add_executable(DrawLine_Test unit_tests/catch-main.cpp unit_tests/DrawLine_tests.cpp ImageMaker.cpp)

# Use precompiled catch2 library for all of the executables to speed up recompile times
target_link_libraries(ImageMaker_Test catch2_main)
target_compile_definitions(ImageMaker_Test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(ImageMaker_Test PRIVATE unit_tests/catch.hpp)

target_link_libraries(Getter_Setter_Test catch2_main)
target_compile_definitions(Getter_Setter_Test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(Getter_Setter_Test PRIVATE unit_tests/catch.hpp)

target_link_libraries(Constructor_Test catch2_main)
target_compile_definitions(Constructor_Test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(Constructor_Test PRIVATE unit_tests/catch.hpp)

target_link_libraries(Save_Load_Test catch2_main)
target_compile_definitions(Save_Load_Test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(Save_Load_Test PRIVATE unit_tests/catch.hpp)

target_link_libraries(DrawPixel_Test catch2_main)
target_compile_definitions(DrawPixel_Test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(DrawPixel_Test PRIVATE unit_tests/catch.hpp)

target_link_libraries(DrawRectangle_Test catch2_main)
target_compile_definitions(DrawRectangle_Test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(DrawRectangle_Test PRIVATE unit_tests/catch.hpp)

target_link_libraries(DrawLine_Test catch2_main)
target_compile_definitions(DrawLine_Test PRIVATE CATCH_CONFIG_FAST_COMPILE CATCH_CONFIG_DISABLE_MATCHERS)
target_precompile_headers(DrawLine_Test PRIVATE unit_tests/catch.hpp)

set_property(TARGET ImageMaker_Driver PROPERTY CXX_STANDARD 11)
set_property(TARGET ImageMaker_Test PROPERTY CXX_STANDARD 11)
set_property(TARGET Getter_Setter_Test PROPERTY CXX_STANDARD 11)
set_property(TARGET Constructor_Test PROPERTY CXX_STANDARD 11)
set_property(TARGET Save_Load_Test PROPERTY CXX_STANDARD 11)
set_property(TARGET DrawPixel_Test PROPERTY CXX_STANDARD 11)
set_property(TARGET DrawRectangle_Test PROPERTY CXX_STANDARD 11)
set_property(TARGET DrawLine_Test PROPERTY CXX_STANDARD 11)