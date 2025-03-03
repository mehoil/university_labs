cmake_minimum_required(VERSION 3.29)
project(lab_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_3
        UtilityFunctions.cpp
        UtilityFunctions.h
        MatrixGenerator.h
        InverseIterationsMethod.h
    main.cpp
    TapeMatrix.h
        Test.cpp
        Test.h)
