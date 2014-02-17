add_library(StaticLib1 STATIC MathFunctions.cpp)
set_target_properties(StaticLib1 PROPERTIES COMPILE_FLAGS "/ZW /AI$(WindowsSDK_MetadataPath);$(AdditionalUsingDirectories)")
set_target_properties(StaticLib1 PROPERTIES FOLDER MyApp)
