cmake_minimum_required(VERSION 3.13)
project(speech_to_intent)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Release)
#add_subdirectory(pvrecorder)

set(COMMON_LIBS dl)
set(MIC_LIBS pthread m)

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

include_directories("${PROJECT_SOURCE_DIR}/../rhino/include")
include_directories("${PROJECT_SOURCE_DIR}/../rhino/demo/c/dr_libs")
include_directories("${PROJECT_SOURCE_DIR}/../rhino/demo/c")
include_directories("${PROJECT_SOURCE_DIR}/../rhino/demo/c/pvrecorder/include")

add_executable(
        main
        main_demo_mic.c)
target_include_directories(main PRIVATE dr_libs)
target_link_libraries(main dl)
