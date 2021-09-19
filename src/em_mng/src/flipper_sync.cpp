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

void sync_callback(const std_msgs::Int32MultiArray &synccom)
{
    //asynccom.data[0];
    ROS_INFO("SYNC [0]:%d,[1]:%d",synccom.data[0],synccom.data[1]);
    



}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "flipper_sync");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe("Syn_com", 10, sync_callback);

 
    ros::Rate loop_rate(10);
    while(ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
    //ros::Publisher joy_com= nh.advertise<sensor_msgs::Join  
    return 0;
}