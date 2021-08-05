cmake_minimum_required(VERSION 2.8.3)
project(tutorial_topic)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")


find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation)

add_message_files(FILES Int32Stamped.msg)
generate_messages(DEPENDENCIES std_msgs)

catkin_package()
include_directories(${catkin_INCLUDE_DIRS})

add_executable(publisher src/publisher.cpp)
target_link_libraries(publisher ${catkin_LIBRARIES})

add_executable(subscriber src/subscriber.cpp)
target_link_libraries(subscriber ${catkin_LIBRARIES})

add_executable(subscriber_once src/subscriber_once.cpp)
target_link_libraries(subscriber_once ${catkin_LIBRARIES})

add_executable(subscriber_async src/subscriber_async.cpp)
target_link_libraries(subscriber_async ${catkin_LIBRARIES})
