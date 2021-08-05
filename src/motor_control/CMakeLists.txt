cmake_minimum_required(VERSION 2.8.3)
project(motor_control)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs )

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})


add_executable(motor_test src/motor_test.cpp)
add_executable(motor_test2 src/motor_test2.cpp)


target_link_libraries(motor_test ${catkin_LIBRARIES})
target_link_libraries(motor_test2 ${catkin_LIBRARIES})