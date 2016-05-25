cmake_minimum_required(VERSION 3.5)
project(EDAMI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

<<<<<<< HEAD
set(SOURCE_FILES main.cpp utils/DatasetReader.cpp utils/DatasetReader.h models/Point.cpp models/Point.h models/Dataset.cpp models/Dataset.h algorithm/NBC.cpp algorithm/NBC.h )
=======
set(SOURCE_FILES main.cpp 
DatasetReader.cpp DatasetReader.h 
models/Point.cpp models/Point.h 
models/Dataset.cpp models/Dataset.h 
NBC.cpp NBC.h 
utils/simpleini.h)

>>>>>>> 2b809caebe6e71844c7565c813ad1ed2b5693a48
add_executable(EDAMI ${SOURCE_FILES})