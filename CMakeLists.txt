cmake_minimum_required(VERSION 3.24)
project(FlappyBird)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED CONFIG)

add_subdirectory(src)
