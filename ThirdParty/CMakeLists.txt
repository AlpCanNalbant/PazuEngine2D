# Before any third party library buildation.
add_subdirectory("Preprocess")

# Third party library subfolders which is used by Pazu Engine 2D.
add_subdirectory("glew/build/cmake")
add_subdirectory("mathfu")
add_subdirectory("SDL")
add_subdirectory("SOIL2")
