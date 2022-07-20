cmake_minimum_required(VERSION 2.8.12)
project(sotest)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(sotest test.cpp)
target_link_libraries(sotest ${CONAN_LIBS})
