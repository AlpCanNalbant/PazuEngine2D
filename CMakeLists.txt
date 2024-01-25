cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(PAZU_ENGINE2D_VERSION 0.1)
project(PazuEngine2D VERSION ${PAZU_ENGINE2D_VERSION} LANGUAGES CXX)

set(DEPS_HOME "${CMAKE_SOURCE_DIR}/../deps")
set(DEPS_INC_HOME "${DEPS_HOME}/include")
set(DEPS_LIB_HOME "${DEPS_HOME}/lib")

set(PAZU2D_ASSETS_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
set_property(GLOBAL PROPERTY PAZU2D_ASSETS "${PAZU2D_ASSETS_BASE_DIR}/Shaders/default.shader")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(SDL_MAIN_HANDLED "" OFF)

set(COMPILER_NAME "mingw")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_compile_options(-m64)
else()
    add_compile_options(-m64 -Wall -Wextra -Wformat=2 -Wunused -Wpedantic -std=c++23)
endif()

add_subdirectory("${DEPS_HOME}/projects/WinAPICommon" "${CMAKE_BINARY_DIR}/../deps/projects/WinAPICommon")

file(GLOB PAZU_RESOURCE_GENERATOR_SOURCE CONFIGURE_DEPENDS "./Resource/Generator/*.hpp" "./Resource/Generator/*.inl" "./Resource/Generator/*.cpp")

add_executable(PazuResourceGenerator ${PAZU_RESOURCE_GENERATOR_SOURCE})
target_include_directories(PazuResourceGenerator PRIVATE ${DEPS_INC_HOME})
target_compile_definitions(PazuResourceGenerator PRIVATE "$<$<CONFIG:DEBUG>:_DEBUG>" "$<$<CONFIG:RELEASE>:NDEBUG>" _UNICODE UNICODE)
target_link_libraries(PazuResourceGenerator
	PRIVATE
		mingw32 WinAPICommon
		-static-libgcc -static-libstdc++ -static Threads::Threads)

file(GLOB PAZU_RESOURCE_SOURCE CONFIGURE_DEPENDS "./Resource/*.hpp" "./Resource/*.inl" "./Resource/*.cpp")

add_library(PazuResource SHARED ${PAZU_RESOURCE_SOURCE})
target_include_directories(PazuResource PUBLIC ${DEPS_INC_HOME})
target_compile_definitions(PazuResource PUBLIC "$<$<CONFIG:DEBUG>:_DEBUG>" "$<$<CONFIG:RELEASE>:NDEBUG>" _UNICODE UNICODE)
target_link_libraries(PazuResource
	PUBLIC
		mingw32 WinAPICommon
		-static-libgcc -static-libstdc++ -static Threads::Threads)

file(GLOB_RECURSE PAZU_ENGINE2D_SOURCE CONFIGURE_DEPENDS "./Pazu/*.hpp" "./Pazu/*.inl" "./Pazu/*.cpp")

add_library(${PROJECT_NAME} STATIC ${PAZU_ENGINE2D_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME Pazu2D)
target_include_directories(${PROJECT_NAME} INTERFACE ".")
target_link_directories(${PROJECT_NAME} PUBLIC ${DEPS_LIB_HOME})
target_precompile_headers(${PROJECT_NAME} PUBLIC Pazu/Precompiled.hpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC)
if(SDL_MAIN_HANDLED)
	target_compile_definitions(${PROJECT_NAME} PUBLIC SDL_MAIN_HANDLED)
endif()

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		SDL2main SDL2 glew32s soil2 PazuResource
		opengl32 kernel32 advapi32 comdlg32 -mwindows m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 uuid setupapi version)
