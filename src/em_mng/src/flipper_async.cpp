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

void async_callback(const std_msgs::Int32MultiArray &asynccom)
{
    //asynccom.data[0];
    ROS_INFO("ASYNC [0]:%d,[1]:%d",asynccom.data[0],asynccom.data[1]);
    
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "flipper_async");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe("Asyn_com", 10, async_callback);


    ros::Rate loop_rate(10);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
    //ros::Publisher joy_com= nh.advertise<sensor_msgs::Join  
    return 0;
}