cmake_minimum_required(VERSION 3.13)
project(speech_to_intent)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Release)
add_subdirectory(pvrecorder)

set(COMMON_LIBS dl)
set(MIC_LIBS pthread m)

include_directories("${PROJECT_SOURCE_DIR}/../../include")

add_executable(
        rhino_demo_file
        rhino_demo_file.c)
target_include_directories(rhino_demo_file PRIVATE dr_libs)