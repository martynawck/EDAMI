cmake_minimum_required(VERSION 3.5)
project(EDAMI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp 
utils/DatasetReader.cpp utils/DatasetReader.h 
models/Point.cpp models/Point.h 
models/Dataset.cpp models/Dataset.h 
algorithm/NBC.cpp algorithm/NBC.h 
utils/config.cpp utils/config.h)

add_executable(EDAMI ${SOURCE_FILES})