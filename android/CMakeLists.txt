cmake_minimum_required(VERSION 3.20)
project(ZenEngine)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(react-native-zen-engine SHARED
    ../cpp/react-native-zen-engine.cpp
    cpp-adapter.cpp
)

target_include_directories(react-native-zen-engine PRIVATE
    ../cpp
    ../zenffi/generated/include
)

cmake_path(SET LIBZENFFI ${CMAKE_CURRENT_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libzen_ffi.so NORMALIZE)

add_library(zenengine STATIC IMPORTED)
set_target_properties(zenengine PROPERTIES IMPORTED_LOCATION ${LIBZENFFI})

target_link_libraries(react-native-zen-engine PRIVATE zenengine)