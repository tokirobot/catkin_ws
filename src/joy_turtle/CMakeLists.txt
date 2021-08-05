cmake_minimum_required(VERSION 2.8.3)
project(joy_turtle)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs )

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(basic_twist_publisher src/basic_twist_publisher.cpp)

target_link_libraries(basic_twist_publisher ${catkin_LIBRARIES})

