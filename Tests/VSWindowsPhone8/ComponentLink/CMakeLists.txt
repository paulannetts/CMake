cmake_minimum_required (VERSION 2.8.11)
project (WindowsPhone8Components)
#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory (WinRtTopLevelComponent)
add_subdirectory (StaticLib1)
add_subdirectory (WinRtWp8Component1)
add_subdirectory (WinRtWp8Component2)
 