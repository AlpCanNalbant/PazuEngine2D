cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(glew_static)

find_package(GLEW REQUIRED CONFIG)

set(GLEW_STATIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE STRING "Include directory of the glew static library." FORCE)
file(COPY ${glew_INCLUDE_DIR} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

set(glew_static_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c")
configure_file("${glew_SOURCE_DIR}/glew.c" "${glew_static_SOURCE}" COPYONLY)

add_library(${PROJECT_NAME} STATIC ${glew_static_SOURCE})
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC)
target_include_directories(${PROJECT_NAME} INTERFACE ${GLEW_STATIC_INCLUDE_DIR})
