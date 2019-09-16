cmake_minimum_required(VERSION 3.4)

add_compile_options(
	-std=c++11
	-Wall
	-Werror
	-O2
)

set(LIB_NAME argparse)

add_library(${LIB_NAME} STATIC src/argparse.cpp)
target_include_directories(${LIB_NAME} PUBLIC include)