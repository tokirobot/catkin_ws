cmake_minimum_required(VERSION 2.8.3)
project(tutorial_param)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

set(TARGET "param_test")
add_executable(${TARGET} src/${TARGET}.cpp)
target_link_libraries(${TARGET} ${catkin_LIBRARIES})