cmake_minimum_required(VERSION 3.6)
project(design-patterns)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cc)
add_executable(main ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)

target_link_libraries(main patterns)
