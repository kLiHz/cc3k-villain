cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME cc3k-villain)

project(${PROJECT_NAME})

include_directories(".")

add_executable(
    cc3k
    "main.cc"
    "control/game.hpp"
    "control/game.cc"
    "control/display.hpp"
    "control/display.cc"
    "facilities/floor.hpp"
    "facilities/floor.cc"
    "facilities/chamber.hpp"
    "facilities/chamber.cc"
    "facilities/path.hpp"
    "facilities/path.cc"
    "facilities/port.hpp"
    "characters/character_interface.hpp"
    "characters/player_character.hpp"
    "characters/player_character.cc"
    "characters/character.hpp"
    "characters/character.cc"
    "characters/races.hpp"
    "characters/races.cc"
    "characters/strategy_interface.hpp"
    "characters/strategies.hpp"
    "basic/canvas.hpp"
    "basic/canvas.cc"
    "basic/effect.hpp"
    "basic/figures.hpp"
    "basic/figures.cc"
    "basic/status.hpp"
    "basic/types.hpp"
    "items/gold.hpp"
    "items/gold.cc"
    "items/item.hpp"
    "items/potion.hpp"
    "items/potion.cc"
)

install(TARGETS cc3k DESTINATION ${PROJECT_SOURCE_DIR}/bin)
