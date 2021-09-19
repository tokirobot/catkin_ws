#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termio.h>
#include <unistd.h>
#include <stdio.h>

#define DEFAULT_SPEED 300


struct joy_but
{
    int cro_n;
    int cro_s;
    int cro_w;
    int cro_e;

    //int start;
    int select;
    //int pair;

    int tryangle;
    int cross;
    int square;
    int circle;

    int l1;
    int r1;

    float l_stick;
    float r_stick;
    float l2;
    float r2;
    /* data */
};

enum mode {
    Asynchronous=1,
    Synchronous,
    DynamixelArm
};

//std_msgs::Int32MultiArray cro_n;
std_msgs::Int32MultiArray motor_command;
std_msgs::Int32MultiArray mode;

int cro_n, cro_s, cro_e, cro_w ;
int pairbutton=0;
int startbutton=0;
int speedmode=1;
int controlmode=1;
int duty=0;
int default_speed=300;


//pid control speed command
int ref_speed=0;

int setmotorspeed(int default_speed, int speedmode, int button_state){
    return default_speed*speedmode*button_state;
}


void joy_callback(const sensor_msgs::Joy &joy_msg){

    //bfpr=joy_msg.buttons[10];
    pairbutton=joy_msg.buttons[10];

    //bfst=joy_msg.buttons[9];
    startbutton=joy_msg.buttons[9];

    speedmode+=startbutton;
    controlmode+=pairbutton;

    if(speedmode>=4){
        speedmode=1;
    }
        
    if(controlmode>=4){
        controlmode=1;

    }


    duty=setmotorspeed(DEFAULT_SPEED, speedmode, joy_msg.buttons[0]);
    //you should process startbottun in each asyn syn node
    motor_command.data[0]=10;
    motor_command.data[1]=duty;
    //ROS_INFO("[0]:%d,[1]:%d",motor_command.data[0],motor_command.data[1]);
   // ROS_INFO("--------------------------------");
    //ROS_INFO("[0]:%d",speedmode);
    //ROS_INFO("[0]:%d",controlmode);



}




int main(int argc, char** argv)
{

    ros::init(argc, argv, "main");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub = nh.subscribe("joy", 10, joy_callback);
    
    //ros::Publisher robot_3dmodel_state = nh.advertise<std_msgs::Int32MultiArray>("3d_com",10);
    ros::Publisher Flipper_Synchronous = nh.advertise<std_msgs::Int32MultiArray>("Syn_com",10);
    ros::Publisher Flipper_Asynchronous = nh.advertise<std_msgs::Int32MultiArray>("Asyn_com",10);
    ros::Publisher Dynamixel_Arm = nh.advertise<std_msgs::Int32MultiArray>("Dyna_com",10);
    //in rviz , you can see current robot mode , state , and unko
    ros::Publisher JSK_pub = nh.advertise<std_msgs::Int32MultiArray>("operation_mode",10);


    motor_command.data.resize(3);
    //std_msgs::Int32 mode;
    
    mode.data.resize(3);

    //mode.data[1]=DEFAULT_SPEED;
    mode.data[1]=DEFAULT_SPEED;
    ros::Rate loop_rate(20);
    ROS_INFO("main");
    //ROS_INFO("%d",Asynchronous);
    while(ros::ok()){


        
            switch (controlmode)
            {
            case Asynchronous:
                Flipper_Synchronous.publish(motor_command);
                mode.data[0]=Asynchronous;
                //ROS_INFO("Synchronous");
                //if (pairbutton==1)
                //controlmode=Asynchronous;
                
                break;

            case Synchronous:
                Flipper_Asynchronous.publish(motor_command);
                mode.data[0]=Synchronous;
                //ROS_INFO("Asynchronous");

                break;

            case DynamixelArm:
                Dynamixel_Arm.publish(motor_command);
                mode.data[0]=DynamixelArm;
                break;            
            
        /* default:
            ROS_INFO("UNKO");

                break;*/
            }

            
            mode.data[2]=speedmode;
            JSK_pub.publish(mode);
            //ROS_INFO("mode data:%d",mode.data);

            ros::spinOnce();
            loop_rate.sleep();
        }

    //ros::Publisher joy_com= nh.advertise<sensor_msgs::Join  
    return 0;
}