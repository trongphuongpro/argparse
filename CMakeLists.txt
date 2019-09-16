set(LIB_NAME argparse)

add_library(${LIB_NAME} STATIC src/argparse.cpp)
target_include_directories(${LIB_NAME} PUBLIC include)