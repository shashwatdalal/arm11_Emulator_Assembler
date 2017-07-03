cmake_minimum_required(VERSION 3.7)
project(tron)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        board.c
        board.h
        definitions.h
        game.c
        game.h
        main.c
        player.c
        player.h)

add_executable(tron ${SOURCE_FILES})