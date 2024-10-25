cmake_minimum_required(VERSION 3.25)
project(TSPbasics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(TSPbasics main.cpp Data.cpp Data.h Config.cpp Config.h Time.cpp Time.h BruteForce.cpp BruteForce.h NN.cpp NN.h)
