add_library(WinRtWp8Component1 SHARED MathFunctions.cpp)
set_target_properties(WinRtWp8Component1 PROPERTIES COMPILE_FLAGS "/ZW /AI$(WindowsSDK_MetadataPath);$(AdditionalUsingDirectories)")
set_target_properties(WinRtWp8Component1 PROPERTIES VS_WINRT_IS_COMPONENT "true")
set_target_properties(WinRtWp8Component1 PROPERTIES FOLDER MyApp)
