cmake_minimum_required(VERSION 3.10)

project(hello_ptr)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

# add the executable
add_executable(hello_ptr hello_ptr.cpp)