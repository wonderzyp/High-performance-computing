cmake_minimum_required(VERSION 3.10)

project(modern_cpp)


foreach(subdir
  concurrency
  # common
)

add_subdirectory(${subdir})

endforeach()