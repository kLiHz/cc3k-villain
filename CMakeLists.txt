cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(PROJECT_NAME cc3k)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
project(${PROJECT_NAME})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
include_directories( 
    ${PROJECT_SOURCE_DIR}/basic 
    ${PROJECT_SOURCE_DIR}/characters 
    ${PROJECT_SOURCE_DIR}/control 
    ${PROJECT_SOURCE_DIR}/facilities 
    ${PROJECT_SOURCE_DIR}/items 
)
add_executable(
    cc3k
    ./main.cc
    ./control/src/game.cc	
    ./control/src/display.cc
    ./facilities/src/floor.cc 
    ./facilities/src/chamber.cc 
    ./facilities/src/path.cc
    ./characters/src/player_character.cc    
    ./characters/src/character.cc
    ./characters/src/races.cc
    ./basic/src/canvas.cc 
    ./basic/src/figures.cc
    ./items/src/gold.cc
    ./items/src/potion.cc
)
