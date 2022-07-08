cmake_minimum_required(VERSION 3.0)
project(npm-registry)

set(CMAKE_BUILD_TYPE    Debug)

add_executable(
    npm-registry
    src/main.cpp
    src/server.cpp
)