cmake_minimum_required(VERSION 3.5)
project(EDAMI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(SOURCE_FILES main.cpp 
algorithm/models/Cluster.cpp algorithm/models/Cluster.h
algorithm/models/Point.cpp algorithm/models/Point.h
algorithm/models/Dataset.cpp algorithm/models/Dataset.h
algorithm/NBC.cpp algorithm/NBC.h
        algorithm/neighbourhood.cpp algorithm/neighbourhood.h
        )

add_executable(EDAMI ${SOURCE_FILES})