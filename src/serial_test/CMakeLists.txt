cmake_minimum_required(VERSION 2.8.3)
project(serial_test)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs )

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})


add_executable(serial_test src/serial_test.cpp)
add_executable(serial_test_joy src/serial_test_joy.cpp)


target_link_libraries(serial_test ${catkin_LIBRARIES})
target_link_libraries(serial_test_joy ${catkin_LIBRARIES})
