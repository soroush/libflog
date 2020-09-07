cmake_minimum_required(VERSION 3.16)

project(libflog VERSION 0.2.0
    DESCRIPTION "libflog is yet another logging library"
    HOMEPAGE_URL "https://github.com/soroush/libflog"
    LANGUAGES CXX)

option(BUILD_TESTING "Build and run test units" ON)

add_subdirectory(lib)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()