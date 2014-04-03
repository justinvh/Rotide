cmake_minimum_required(VERSION 2.8)

include_directories("../include")

set(sources "test-terminal.cpp")
add_executable(test_terminal_cursor ${sources})
target_link_libraries(test_terminal_cursor rotide)
