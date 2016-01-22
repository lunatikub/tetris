cmake_minimum_required (VERSION 2.6)
project (tetris_IA)

include_directories(
        src
        src/tetris_ai
        src/tetris_x
        src/tetris_item
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
)
