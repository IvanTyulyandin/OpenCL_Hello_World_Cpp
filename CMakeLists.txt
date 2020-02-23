cmake_minimum_required(VERSION 3.15)
project(opencl)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCL REQUIRED)
add_executable(opencl main.cpp)
target_link_libraries(opencl OpenCL::OpenCL)

