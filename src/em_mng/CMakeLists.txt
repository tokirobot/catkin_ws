cmake_minimum_required(VERSION 3.0.2)
project(em_mng)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(flipper_sync src/flipper_sync.cpp)
target_link_libraries(flipper_sync ${catkin_LIBRARIES})

add_executable(flipper_async src/flipper_async.cpp)
target_link_libraries(flipper_async ${catkin_LIBRARIES})

add_executable(Dynamixel_arm src/Dynamixel_arm.cpp)
target_link_libraries(Dynamixel_arm ${catkin_LIBRARIES})