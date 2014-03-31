cmake_minimum_required(VERSION 2.8)

project(rotide)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories("include")
set(sources "src/rotide/main.cpp"
            "src/rotide/sys/terminal.cpp")

add_executable(rotide ${sources})
