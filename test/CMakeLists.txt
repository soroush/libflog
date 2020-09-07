cmake_minimum_required(VERSION 3.16)

enable_testing()

include(CTest)

add_executable(cerr_logger cerr-logger.cpp)
target_link_libraries(cerr_logger PUBLIC libflog)

add_test(tst_cerr_logger cerr_logger.exe)