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

void Dyna_callback(const std_msgs::Int32MultiArray &dynacom)
{
    //asynccom.data[0];
   //ROS_INFO("DYNAMIXEL [0]:%d, [1]:%d" ,dynacom.data[0], dynacom.data[1]);
    
}


int main(int argc, char** argv)
{

    ros::init(argc, argv, "Dynamixel_arm");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe("Dyna_com", 10, Dyna_callback);

 
    ros::Rate loop_rate(10);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
    //ros::Publisher joy_com= nh.advertise<sensor_msgs::Join  
    return 0;
}