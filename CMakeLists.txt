cmake_minimum_required(VERSION 3.23)
project(study_reed_solomon_ec)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(study_reed_solomon_ec
        main.cc
        common.h
        galois.h
        galois.cc
        reedsolomon.h
        reedsolomon.cc
        common.cc matric.cc matric.h)
