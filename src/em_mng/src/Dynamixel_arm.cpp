#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/String.h"
#include <string>
#include <unistd.h>
#include <fcntl.h>
//#include <termio.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{

    ros::init(argc, argv, "Dynamixel_arm");
    ros::NodeHandle nh;

 
    ros::Rate loop_rate(10);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
    //ros::Publisher joy_com= nh.advertise<sensor_msgs::Join  
    return 0;
}