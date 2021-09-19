cmake_minimum_required(VERSION 2.8.3)

project(tf_practice)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  actionlib
  actionlib_msgs
  message_generation
  std_msgs
  tf
  tf2
  tf2_ros
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(tf_broadcaster src/tf_broadcaster.cpp)

target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})

add_executable(tf_listener src/tf_listener.cpp)

target_link_libraries(tf_listener ${catkin_LIBRARIES})





