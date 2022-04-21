cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(main LANGUAGES CXX)

add_executable(main test.cpp)

find_package(TBB REQUIRED)
target_link_libraries(main PUBLIC TBB::tbb)

find_package(benchmark REQUIRED)
target_link_libraries(main PUBLIC benchmark::benchmark)
