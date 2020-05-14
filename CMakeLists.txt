cmake_minimum_required(VERSION 3.16)
project(racing)
set(CMAKE_INCLUDE_PATH ./include)
set(CMAKE_LIBRARY_PATH ./lib)
set(CMAKE_BINARY_DIR ./bin)
set(CMAKE_CXX_STANDARD 14)

#add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

add_executable(racing main.cpp game.h Object.h Position.h Object.cpp Position.cpp)