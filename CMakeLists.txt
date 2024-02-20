cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(PazuEngine2D LANGUAGES CXX)

# Before adding this subdirectory for your cmake project, you can set the different installation directory for the Pazu Engine 2D,
# via calling the 'set_pazuengine2d_install_dir("...")' function or you can edit PazuEngine2D_INSTALL_HOME variable's value with cmake-gui application.
function(set_pazuengine2d_install_dir dir)
	set(options OVERWRITE)
	cmake_parse_arguments(PARSED_ARGS "${options}" "dummy1" "dummy2" ${ARGN})
	if(${PARSED_ARGS_OVERWRITE})
		set(OVERWRITE_OPTION FORCE)
	else()
		set(OVERWRITE_OPTION)
	endif()
	set(PazuEngine2D_INSTALL_HOME "${dir}" CACHE STRING "Installation directory of the Pazu Engine 2D." ${OVERWRITE_OPTION})
endfunction()

# Default installation directory of the Pazu Engine 2D.
set(PAZU_ENGINE_2D_DEFAULT_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# Set the base directory of to its default value if it is not already setted.
set_pazuengine2d_install_dir("${PAZU_ENGINE_2D_DEFAULT_INSTALL_DIR}")

get_property(PazuEngine2DInstallDir GLOBAL PROPERTY PAZU_ENGINE_2D_INSTALL_DIR)
if (NOT "${PazuEngine2DInstallDir}" STREQUAL "")
	if ("${PazuEngine2D_INSTALL_HOME}" STREQUAL "${PAZU_ENGINE_2D_DEFAULT_INSTALL_DIR}")
		set_pazuengine2d_install_dir("${PazuEngine2DInstallDir}" OVERWRITE)
	endif()
endif()

set(PazuEngine2D_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Pazu" CACHE STRING "Source directory of the Pazu Engine 2D." FORCE)
set(PazuEngine2D_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "Include directories of the Pazu Engine 2D." FORCE)
add_subdirectory("ThirdParty")

set_property(GLOBAL PROPERTY PAZU_RESOURCE_GENERATOR_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Pazu/Assets")
add_subdirectory("PazuResource")

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

file(GLOB_RECURSE PazuEngine2D_SOURCE CONFIGURE_DEPENDS "Pazu/*.hpp" "Pazu/*.inl" "Pazu/*.cpp")

add_library(${PROJECT_NAME} STATIC ${PazuEngine2D_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME PazuEngine2D CXX_STANDARD ${WINAPICOMMON_CPP_VERSION} CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} ${MATHFU_INCLUDE_DIRS} ${SOIL2_STATIC_INCLUDE_DIR} ${GLEW_STATIC_INCLUDE_DIR}
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(${PROJECT_NAME} PUBLIC Pazu/Precompiled.hpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC M_PI=3.141592f)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		PazuResource
	INTERFACE
		${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} soil2_static glew_static
		kernel32 advapi32 comdlg32 -mwindows m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 uuid setupapi version)

message("Installing Pazu Engine 2D ...")
install(TARGETS ${PROJECT_NAME}
	ARCHIVE DESTINATION ${PazuEngine2D_INSTALL_HOME}/obj/${CMAKE_BUILD_TYPE})
