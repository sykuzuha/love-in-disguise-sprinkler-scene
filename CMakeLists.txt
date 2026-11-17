cmake_minimum_required(VERSION 3.16)
project(SprinklerScene VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SPRINKLER_ENABLE_OPENMP "Link OpenMP for parallel particle updates" OFF)
option(SPRINKLER_ENABLE_OPENGL "Link OpenGL for rendering" OFF)

add_executable(sprinkler_scene src/main.cpp)
target_include_directories(sprinkler_scene PRIVATE include)

if(SPRINKLER_ENABLE_OPENMP)
    find_package(OpenMP REQUIRED COMPONENTS CXX)
    target_link_libraries(sprinkler_scene PRIVATE OpenMP::OpenMP_CXX)
endif()

if(SPRINKLER_ENABLE_OPENGL)
    find_package(OpenGL REQUIRED)
    target_link_libraries(sprinkler_scene PRIVATE OpenGL::GL)
endif()
