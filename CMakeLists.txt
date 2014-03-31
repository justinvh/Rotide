cmake_minimum_required(VERSION 2.8)

project(rotide)

set(CURSES_USES_NCURSES TRUE)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

set(sources "src/rotide/main.c")

add_executable(rotide ${sources})
target_link_libraries(rotide ${CURSES_LIBRARIES} -lncursesw)
