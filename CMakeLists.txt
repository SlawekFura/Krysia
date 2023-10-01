cmake_minimum_required(VERSION 3.13)
project(speech_to_intent)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
add_subdirectory("${PROJECT_SOURCE_DIR}/../demo/c/pvrecorder" build )

set(COMMON_LIBS dl)
set(MIC_LIBS pthread m)

include_directories(${GIO-UNIX_INCLUDE_DIRS})

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

include(${CMAKE_SOURCE_DIR}/cmake_utils/FindDBus.cmake)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLIB REQUIRED glib-2.0)
pkg_check_modules(GTK "gtk+-2.0")
pkg_check_modules(GIO "gio-unix-2.0")

include_directories("${PROJECT_SOURCE_DIR}/../include")
include_directories("${PROJECT_SOURCE_DIR}/../demo/c/dr_libs")
include_directories("${PROJECT_SOURCE_DIR}/../demo/c")
include_directories("${PROJECT_SOURCE_DIR}/../demo/c/pvrecorder/include")
include_directories("${PROJECT_SOURCE_DIR}/modules/intent_manager")
include_directories("${PROJECT_SOURCE_DIR}/modules/mic_setup/")
include_directories("${PROJECT_SOURCE_DIR}/modules/dbus_manager/")
include_directories(${GTK_INCLUDE_DIRS})
include_directories(${DBUS_INCLUDE_DIRS})


add_executable(
        main
        main_demo_mic.c
        modules/mic_setup/mic.c
        modules/intent_manager/intent_mgr.c
        modules/dbus_manager/dbus_mgr.c
        modules/dbus_manager/dbus_mgr_gen.c
        $<TARGET_OBJECTS:pv_recorder_object>)

target_include_directories(main PRIVATE dr_libs)
target_include_directories(main PRIVATE ${GLIB_INCLUDE_DIRS})
target_include_directories(main PRIVATE ${GIO_INCLUDE_DIRS})

target_link_libraries(main dl)
target_link_libraries(main ${GLIB_LDFLAGS})
target_link_libraries(main ${GIO_LDFLAGS})
target_link_libraries(main ${DBUS_LIBRARIES})

message(VAR_AAA="${GLIB_INCLUDE_DIRS}")
message(VAR_BBB="${GTK_INCLUDE_DIRS}")
message(VAR_CCC="${GIO-UNIX_LDFLAGS}")
target_link_libraries(main ${GIO-UNIX_LDFLAGS} ${COMMON_LIBS} ${MIC_LIBS})
if((${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm") AND (UNIX AND NOT APPLE))
    target_link_libraries(main atomic)
endif()

