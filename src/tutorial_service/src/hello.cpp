#include <ros/ros.h>

int main(int argc , char **argv )
{
    ros::init(argc, argv, "hello");
    ROS_INFO("hello");
    ros::spin();
    return 0;
}