cmake_minimum_required(VERSION 3.10)

project(CourseRequestSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 使用 pkg-config 查找 MySQL
include(FindPkgConfig)
pkg_check_modules(MYSQL REQUIRED mysqlclient)

# 添加头文件目录
include_directories(${PROJECT_SOURCE_DIR}/inc ${MYSQL_INCLUDE_DIRS})

# 源文件
file(GLOB SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(course_request_system ${SOURCES})

# 链接 MySQL 库
target_link_libraries(course_request_system PRIVATE ${MYSQL_LIBRARIES})