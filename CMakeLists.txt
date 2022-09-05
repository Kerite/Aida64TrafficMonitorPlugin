cmake_minimum_required(VERSION 3.23)
project(Aida64TrafficMonitorPlugin)

set(CMAKE_CXX_STANDARD 23)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

add_executable(Aida64TrafficMonitorPlugin ${SRC_LIST})
target_include_directories(Aida64TrafficMonitorPlugin PRIVATE ${PROJECT_SOURCE_DIR}/include)
