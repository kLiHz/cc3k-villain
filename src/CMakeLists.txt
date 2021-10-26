cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME cc3k-villain)

project(${PROJECT_NAME})

include_directories(".")

add_executable(
    cc3k
    "main.cc"
    "control/game.cc"
    "control/display.cc"
    "facilities/floor.cc"
    "facilities/chamber.cc"
    "facilities/path.cc"
    "characters/player_character.cc"
    "characters/character.cc"
    "characters/races.cc"
    "basic/canvas.cc"
    "basic/figures.cc"
    "items/gold.cc"
    "items/potion.cc"
)

install(TARGETS cc3k DESTINATION ${PROJECT_SOURCE_DIR}/bin)
