cmake_minimum_required(VERSION 3.22)
project(ParticleFilterTest)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/boost/boost_1_79_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/boost/boost_1_79_0/stage/gcc/x64/lib")


find_package(Eigen3 3.3 REQUIRED NO_MODULE)
include_directories("${EIGEN3_INCLUDE_DIR}")

find_package(Boost 1.45.0)
include_directories("${Boost_INCLUDE_DIRS}")


add_executable(ParticleFilterTest main.cpp)
target_link_libraries(ParticleFilterTest Eigen3::Eigen)
