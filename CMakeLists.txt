cmake_minimum_required(VERSION 3.19)
project(Schedulize)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Schedulize
        main.cpp
        schedule.cpp
        schedule.h)
