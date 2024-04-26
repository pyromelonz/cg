cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(CG VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(CGConfig.h.in CGConfig.h)

add_executable(CG src/main.cpp)

target_include_directories(CG PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/vendor/glad/include"
                           )