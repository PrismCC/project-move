cmake_minimum_required(VERSION 3.23)
project(move)

set(CMAKE_CXX_STANDARD 17)

add_executable(move main.cpp others.h others.cpp structs.cpp structs.h func.cpp func.h)
