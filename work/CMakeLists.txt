cmake_minimum_required(VERSION 2.8.12)
project(sotest)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(avro/lang/c++)
include_directories(SYSTEM avro/lang/c++)

add_executable(sotest test.cpp)
target_link_libraries(sotest avrocpp_s)
