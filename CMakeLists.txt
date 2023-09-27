cmake_minimum_required(VERSION 3.13)
project(speech_to_intent)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
add_subdirectory("${PROJECT_SOURCE_DIR}/../demo/c/pvrecorder" build )

set(COMMON_LIBS dl)
set(MIC_LIBS pthread m)

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

include_directories("${PROJECT_SOURCE_DIR}/../include")
include_directories("${PROJECT_SOURCE_DIR}/../demo/c/dr_libs")
include_directories("${PROJECT_SOURCE_DIR}/../demo/c")
include_directories("${PROJECT_SOURCE_DIR}/../demo/c/pvrecorder/include")
include_directories("${PROJECT_SOURCE_DIR}/modules/intent_manager")
include_directories("${PROJECT_SOURCE_DIR}/modules/mic_setup/")

add_executable(
        main
        main_demo_mic.c
        modules/mic_setup/mic.c
        modules/intent_manager/intent_mgr.c
        $<TARGET_OBJECTS:pv_recorder_object>)
target_include_directories(main PRIVATE dr_libs)
target_link_libraries(main dl)

if (NOT WIN32)
    target_link_libraries(main ${COMMON_LIBS} ${MIC_LIBS})
#    target_link_libraries(rhino_demo_file ${COMMON_LIBS})
    if((${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm") AND (UNIX AND NOT APPLE))
        target_link_libraries(main atomic)
    endif()
endif()
