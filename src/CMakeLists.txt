cmake_minimum_required(VERSION 3.19.2)

# set the project name
project("Patty" VERSION 0.0.1) 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH ${Patty_SRC_DIR}../out)

configure_file(Patty.hpp.in ${Patty_SRC_DIR}Patty.hpp)

# target_include_directories(Patty PUBLIC "${PROJECT_BINARY_DIR}")

# add the executable
add_executable(${PROJECT_NAME} "main.cpp")
