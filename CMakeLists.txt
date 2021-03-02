cmake_minimum_required(VERSION 3.10)

project(dengine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



add_library(dengine 
    src/camera.cpp
    src/inputManager.cpp
    src/dengine_init.cpp
    src/dengine_input.cpp
    src/dengine_loop.cpp
    #src/mdl/model.cpp
    src/mdl/sphereVAO.cpp
    src/mdl/texturedSphere.cpp
    src/mdl/mdl_base.cpp
    src/mdl/l1/mdl_pos.cpp
    src/mdl/l1/mdl_pos_col.cpp
    src/mdl/l1/mdl_pos_col_line.cpp
    src/mdl/l1/mdl_pos_tex.cpp
    src/mdl/l1/mdl_pos_tex_norm.cpp
    src/mdl/l2/mdl_axes_orthnorm.cpp
    src/mdl/l2/mdl_example0.cpp
    src/mdl/l2/mdl_example1.cpp
    src/mdl/l2/mdl_example2.cpp
    src/mdl/l2/mdl_pos_tex_obj.cpp
    src/mdl/l2/mdl_pos_tex_norm_obj.cpp
    src/shaderManager.cpp
    src/textureManager.cpp
    src/util.cpp
    src/obj_import.c

    extern/lodepng/lodepng.cpp
    )

target_include_directories(dengine PUBLIC inc extern/lodepng)