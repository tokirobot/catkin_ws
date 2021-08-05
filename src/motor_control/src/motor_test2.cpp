#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/String.h"
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termio.h>
#include <unistd.h>
#include <stdio.h>

//std_msgs::String cro;
std_msgs::Float32MultiArray l2;
int a=0;

void motorjoycallback(const sensor_msgs::Joy &joy_msg){
    //int i=0;
    //i=joy_msg.buttons[14];
    l2.data[0]=joy_msg.buttons[0];
   // ROS_INFO("joy callback");
   // l2.data[0]=joy_msg.axes[5];
    //ROS_INFO("l2 :%lf",l2.data[0]);


    //cro.data = (char)i*810;
}
void stm_rcv_callback(const std_msgs::Float32MultiArray &f_msg){
    /*for(int i=0; i<4 ;i++){
        ROS_INFO("receive from stm %lf",f_msg.data[i]);
    }*/
    //ROS_INFO("receive from stm %lf",f_msg.data[2]);
    //ROS_INFO("l2 :%lf",l2.data[0]);
    ROS_INFO("-------------------------------------");
    
}

int main (int argc, char **argv){
    ros::init(argc, argv , "motor_test2");
    ros::NodeHandle nh;
    //ros::Subscriber receive = nh.subscribe("")
    ros::Subscriber joy_sub = nh.subscribe("joy", 10, motorjoycallback);
    ros::Subscriber re_stm = nh.subscribe("Serial_pub_float", 500, stm_rcv_callback);
    ros::Publisher motorcmd = nh.advertise<std_msgs::Float32MultiArray>("Serial_sub_float", 500);
    
    ros::Rate loop_rate(10);
    ROS_INFO("motor_test2");


    while(ros::ok()){
       
         motorcmd.publish(l2);
         //ROS_INFO("send %lf",l2.data[0]);
       
        ros::spinOnce();
        loop_rate.sleep();
         //ROS_INFO("motor_test2");

    }
    return 0;


}
