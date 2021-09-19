cmake_minimum_required(VERSION 2.8.3)
project(syogouki_display)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
)
catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(robot_state src/robot_state.cpp)

target_link_libraries(robot_state ${catkin_LIBRARIES})

add_executable(jsk_visual src/jsk_visual.cpp)

target_link_libraries(jsk_visual ${catkin_LIBRARIES})
