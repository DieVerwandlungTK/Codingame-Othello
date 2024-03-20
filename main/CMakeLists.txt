cmake_minimum_required(VERSION 3.28.2)

set(CMAKE_CXX_COMPILER "C:/Program Files/mingw64/bin/g++.exe" CACHE STRING "g++ compiler" FORCE)
project(main CXX)

add_subdirectory(../Othello Othello)
add_subdirectory(../AI AI)

add_executable(main main.cpp)

target_link_libraries(main Othello AI)