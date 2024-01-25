cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(PazuEngine2D LANGUAGES CXX)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty")
add_subdirectory("PazuResource")

set(PAZUENGINE2D_INSTALL_HOME "${CMAKE_CURRENT_SOURCE_DIR}/obj/${CMAKE_BUILD_TYPE}" CACHE STRING "Installation directory of the Pazu Engine 2D." FORCE)
file(GLOB_RECURSE PAZU_ENGINE2D_SOURCE CONFIGURE_DEPENDS "./Pazu/*.hpp" "./Pazu/*.inl" "./Pazu/*.cpp")

add_library(${PROJECT_NAME} STATIC ${PAZU_ENGINE2D_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME Pazu2D CXX_STANDARD ${WINAPICOMMON_CPP_VERSION} CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
target_include_directories(${PROJECT_NAME} INTERFACE ".")
target_precompile_headers(${PROJECT_NAME} PUBLIC Pazu/Precompiled.hpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC)

target_link_libraries(${PROJECT_NAME}
	INTERFACE
		SDL2main SDL2 glew32s soil2 PazuResource WinAPICommon
		opengl32 kernel32 advapi32 comdlg32 -mwindows m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 uuid setupapi version)

message("Installing Pazu Engine 2D")
install(TARGETS ${PROJECT_NAME}
	ARCHIVE DESTINATION ${PAZUENGINE2D_INSTALL_HOME})
