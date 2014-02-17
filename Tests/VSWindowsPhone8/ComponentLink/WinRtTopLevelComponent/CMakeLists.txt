cmake_minimum_required (VERSION 2.8.11)
  
# add the top-level component
add_library(WinRtTopLevelComponent SHARED tutorial.cxx)
set_target_properties(WinRtTopLevelComponent PROPERTIES COMPILE_FLAGS "/ZW /AI$(WindowsSDK_MetadataPath);$(AdditionalUsingDirectories)")
set_target_properties(WinRtTopLevelComponent PROPERTIES VS_WINRT_IS_COMPONENT "true")
set_target_properties(WinRtTopLevelComponent PROPERTIES FOLDER MyApp)
target_link_libraries(WinRtTopLevelComponent StaticLib1 WinRtWp8Component1 WinRtWp8Component2)

include_directories ("${PROJECT_SOURCE_DIR}/StaticLib1")

