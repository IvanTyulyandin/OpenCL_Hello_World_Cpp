cmake_minimum_required(VERSION 3.0)
project(opencl)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Og)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenCL REQUIRED)
add_executable(opencl main.cpp)
target_link_libraries(opencl OpenCL::OpenCL)

