# GLEW library.
add_subdirectory(glew/build/cmake EXCLUDE_FROM_ALL) # EXCLUDE_FROM_ALL for preventing from install it.
set(glew_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glew/src" CACHE INTERNAL "Source directory of glew static library.")
set(glew_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glew/include" CACHE INTERNAL "Include directory of glew static library.")

# SOIL2 library.
set(soil2_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SOIL2/src" CACHE INTERNAL "Source directory of soil2 static library.")

# MathFu library.
set(MATHFU_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/mathfu/include;${CMAKE_CURRENT_SOURCE_DIR}/mathfu/dependencies/vectorial/include" CACHE INTERNAL "Include directories of the mathfu library." FORCE)

add_subdirectory(statics/glew_static)
add_subdirectory(statics/SOIL2_static)
