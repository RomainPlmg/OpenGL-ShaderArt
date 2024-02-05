cmake_minimum_required(VERSION 3.27)
project(ShaderArt LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.9)
FetchContent_MakeAvailable(glfw)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/glfw-src/include)
include_directories(Includes/)

add_executable(ShaderArt
        Sources/Main.cpp
        Sources/glad.c
        Sources/Hello_Triangle_App.cpp
        Includes/Hello_Triangle_App.h
)

target_link_libraries(ShaderArt glfw)
target_link_libraries(ShaderArt ${OPENGL_LIBRARIES})
