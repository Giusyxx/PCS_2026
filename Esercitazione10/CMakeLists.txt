cmake_minimum_required(VERSION 3.20)

project(Esercitazione10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")

find_package(Eigen3 REQUIRED)

add_executable(gradiente main.cpp)

target_link_libraries(gradiente PRIVATE Eigen3::Eigen)