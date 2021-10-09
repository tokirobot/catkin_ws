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
std_msgs::Int32MultiArray mtcmd;
void async_callback(const std_msgs::Int32MultiArray &asynccom)
{
    //asynccom.data[0];
    
    mtcmd.data[0] = asynccom.data[0];
    mtcmd.data[1] = asynccom.data[1];
    mtcmd.data[2] = asynccom.data[2];
    //mtcmd.data[2] = asynccom.data[2];
   // mtcmd.data[3] = asynccom.data[3];    
    //mtcmd.data[1] = asynccom.data[1];
    ROS_INFO("ASYNC [0]:%d,[1]:%d  [2]:%d,[3]:%d",mtcmd.data[0],mtcmd.data[1],mtcmd.data[2],mtcmd.data[3]);
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "flipper_async");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe("Asyn_com", 10, async_callback);
    ros::Publisher micon_serial = nh.advertise<std_msgs::Int32MultiArray>("Serial_sub_int", 10);

    //mtcmd.data.resize(4);
    mtcmd.data.resize(3);
    ros::Rate loop_rate(30);
    while(ros::ok()){

        micon_serial.publish(mtcmd);
        ros::spinOnce();
        loop_rate.sleep();

    }
    //ros::Publisher joy_com= nh.advertise<sensor_msgs::Join  
    return 0;
}