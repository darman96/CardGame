cmake_minimum_required(VERSION 3.28)
project(CardGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(CardGame Source/Main.cpp
        Source/Application.cpp
        Source/Application.h)
