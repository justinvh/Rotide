cmake_minimum_required(VERSION 2.8)

project(rotide)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

add_subdirectory(tests)

include_directories("include")
set(sources "src/rotide/sys/terminal.cpp")

add_library(rotide ${sources})

add_executable(ro "src/rotide/main.cpp")
target_link_libraries(ro rotide)
