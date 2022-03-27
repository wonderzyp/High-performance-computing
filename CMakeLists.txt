cmake_minimum_required(VERSION 3.10)

project(modern_cpp)


foreach(subdir
  concurrency
)

add_subdirectory(${subdir})

endforeach()