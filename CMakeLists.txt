cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(CG VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(CGConfig.h.in CGConfig.h)

add_executable(CG src/main.cpp)

set_target_properties(CG PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/$<0:>)
set_target_properties(CG PROPERTIES OUTPUT_NAME_DEBUG "CG-dbg")
set_target_properties(CG PROPERTIES OUTPUT_NAME_RELEASE "CG")

target_sources(CG PUBLIC
               "${PROJECT_SOURCE_DIR}/src/main.cpp"
               "${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c")

target_include_directories(CG PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/vendor/glad/include"
                           "${PROJECT_SOURCE_DIR}/vendor/glfw/include"
                           )

target_link_libraries(CG glfw)

add_subdirectory(vendor/glfw)

add_custom_target(copy_assets ALL
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                  ${CMAKE_SOURCE_DIR}/assets
                  ${CMAKE_BINARY_DIR}/assets
                  COMMENT "Copying assets" VERBATIM)
add_dependencies(CG copy_assets)