cmake_minimum_required (VERSION 2.6)
project (tetris_IA)

set(CMAKE_C_FLAGS "-W -Wall")

include_directories(
        src
        src/tetris_ai
        src/tetris_x
        src/tetris_item
        src/tetris_move
        src/tetris_x11
        src/tetris_wall
)

file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(
        tetris
        ${source_files}
)

target_link_libraries(
        tetris
        ncurses
        X11
        Xtst
)
