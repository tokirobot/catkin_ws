cmake_minimum_required(VERSION 2.8.3)
project(joy_sub)

find_package(catkin REQUIRED COMPONENTS roscpp)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(joy_sub_node src/joy_sub_node.cpp)

target_link_libraries(joy_sub_node ${catkin_LIBRARIES})
