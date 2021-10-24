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

enum mode {
    Asynchronous=1,
    Synchronous,
    DynamixelArm
};

int moveflag=0;
void sync_callback(const std_msgs::Int32MultiArray &synccom)
{
    mtcmd.data[0] = synccom.data[0];
    mtcmd.data[1] = synccom.data[1];
    mtcmd.data[2] = synccom.data[2];
    mtcmd.data[3] = synccom.data[3];
    moveflag = synccom.data[4];
    //mtcmd.data[2] = asynccom.data[2];
   // mtcmd.data[3] = asynccom.data[3];    
    //mtcmd.data[1] = asynccom.data[1];
   // ROS_INFO("SYNC [0]:%d,[1]:%d  [2]:%d,[3]:%d",mtcmd.data[0],mtcmd.data[1],mtcmd.data[2],moveflag);    
   // ROS_INFO("MODE_SY   %d",synccom.data[2]);    

}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "flipper_sync");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe("Syn_com", 10, sync_callback);
    ros::Publisher micon_serial = nh.advertise<std_msgs::Int32MultiArray>("Serial_sub_int", 10);
    mtcmd.data.resize(4);
 
    ros::Rate loop_rate(30);
    while(ros::ok()){

        if(moveflag == Synchronous){
            micon_serial.publish(mtcmd);
            //ROS_INFO("SSSSSSSSSSSSSSSSSSSS");

        }

 
        ros::spinOnce();
        loop_rate.sleep();
    }
    //ros::Publisher joy_com= nh.advertise<sensor_msgs::Join  
    return 0;
}