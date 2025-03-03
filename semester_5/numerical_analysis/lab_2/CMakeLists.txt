cmake_minimum_required(VERSION 3.29)
project(lab_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_2
    BandMatrix.h
    BandMatrixT.h
        TransposedBandMatrixT.h
        main.cpp
        Vector.h
        AvgErrorUtil.h)
