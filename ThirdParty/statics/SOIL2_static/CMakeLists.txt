cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(soil2_static)

set(SOIL2_STATIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE STRING "Include directory of the soil2 static library." FORCE)
set(soil2_static_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

configure_file("${soil2_SOURCE_DIR}/SOIL2/SOIL2.h" ${SOIL2_STATIC_INCLUDE_DIR} COPYONLY)

configure_file("${soil2_SOURCE_DIR}/SOIL2/image_DXT.c" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/image_helper.c" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/SOIL2.c" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/wfETC.c" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/common/common.cpp" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/pkm_helper.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/pvr_helper.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stb_image.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stb_image_write.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stbi_DDS.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stbi_DDS_c.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stbi_ext.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stbi_ext_c.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stbi_pkm.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stbi_pkm_c.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stbi_pvr.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/stbi_pvr_c.h" ${soil2_static_SOURCE_DIR} COPYONLY)
configure_file("${soil2_SOURCE_DIR}/SOIL2/wfETC.h" ${soil2_static_SOURCE_DIR} COPYONLY)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE soil2_static_SOURCE "${soil2_static_SOURCE_DIR}/*.h" "${soil2_static_SOURCE_DIR}/*.c" "${soil2_static_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME} STATIC ${soil2_static_SOURCE})

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:Clang>:-fPIC>
    $<$<CXX_COMPILER_ID:GNU>:-fPIC>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${soil2_SOURCE_DIR}/SOIL2/>
        $<BUILD_INTERFACE:${soil2_SOURCE_DIR}/common/>
        $<INSTALL_INTERFACE:include>
    INTERFACE
        ${SOIL2_STATIC_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
