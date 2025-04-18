cmake_minimum_required(VERSION 3.10)

project(CourseRequestSystem)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    )

add_executable(course_request_system ${SRC_LIST})