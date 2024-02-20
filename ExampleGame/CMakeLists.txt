cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(ExampleGame LANGUAGES CXX)

set_property(GLOBAL PROPERTY PAZU_ENGINE_2D_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/deps/PazuEngine2D")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_BINARY_DIR}/deps/PazuEngine2D")

file(GLOB_RECURSE SPLASH_SCREEN_SOURCE "./Game/*.hpp" "./Game/*.inl" "./Game/*.cpp")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${SPLASH_SCREEN_SOURCE})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME PazuEngine2DGame CXX_STANDARD ${WINAPICOMMON_CPP_VERSION} CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
target_link_libraries(${PROJECT_NAME} PRIVATE mingw32 PazuEngine2D -static-libgcc -static-libstdc++ -static Threads::Threads)

message("Installing game example of the Pazu Engine 2D")
set(INSTALL_BIN_HOME "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION ${INSTALL_BIN_HOME})
