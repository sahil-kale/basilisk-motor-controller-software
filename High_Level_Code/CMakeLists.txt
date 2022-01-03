cmake_minimum_required(VERSION 3.10)

# set the project name
project(HighLevelCode)

# Add the include directory to the target
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.c" "src/*.cpp")

# add the executable
add_executable(HighLevelCode ${SOURCES})