cmake_minimum_required(VERSION 3.28.3)

if(NOT DEFINED PROJECT_NAME)
    message(FATAL_ERROR "PROJECT_NAME is not defined. Are you sure you built it from ./build.sh?")
endif()
string(STRIP "${PROJECT_NAME}" PROJECT_NAME_STRIPPED)
if(PROJECT_NAME_STRIPPED STREQUAL "")
    message(FATAL_ERROR "PROJECT_NAME cannot be empty.")
elseif(NOT PROJECT_NAME_STRIPPED MATCHES "^[A-Za-z0-9_.-]+$")
    message(FATAL_ERROR "PROJECT_NAME contains invalid characters. Only letters, numbers, underscore, dash, and dot are allowed.")
endif()

project(${PROJECT_NAME_STRIPPED} C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(.)
include_directories(chunk)
include_directories(init)
include_directories(utils)
include_directories(utils/libc)
include_directories(utils/ops)

# Add all c files except the ones in cmake_build/
file(GLOB_RECURSE ALL_SOURCES "*.c")
set(SOURCES "")
foreach(f ${ALL_SOURCES})
    get_filename_component(ABS_PATH "${f}" ABSOLUTE)
    if(NOT ABS_PATH MATCHES ".*/cmake_build/.*")
        list(APPEND SOURCES ${ABS_PATH})
    endif()
endforeach()

add_executable(${PROJECT_NAME_STRIPPED} ${SOURCES})