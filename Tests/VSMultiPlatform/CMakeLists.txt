cmake_minimum_required (VERSION 2.8.11)
project (vs11MultiPlatform)
#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory (CppStaticLib)
add_subdirectory (CppAppWin32)
 