cmake_minimum_required(VERSION 3.10)

project(dengine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



add_library(dengine 
    src/sphereVAO.cpp
    src/inputManager.cpp
    src/mainClass_init.cpp
    src/mainClass_input.cpp
    src/mainClass_loop.cpp
    src/model.cpp
    src/shaderManager.cpp
    src/texturedSphere.cpp
    src/camera.cpp
    src/util.cpp
    )

target_include_directories(dengine PUBLIC inc)