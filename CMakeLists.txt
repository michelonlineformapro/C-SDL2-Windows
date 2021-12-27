cmake_minimum_required(VERSION 3.21)
project(SDL2_Clion)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_PATH "C:\\SDL\\SDL2-2.0.18\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(SDL2_Clion main.cpp)

target_link_libraries(SDL2_Clion ${SDL2_LIBRARY} )
