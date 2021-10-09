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
    int l2;
    int r2;

    int il_stick;
    int ir_stick;

    float l_stick;
    float r_stick;
    float l2_f;
    float r2_f;
    /* data */
};

enum mode {
    Asynchronous=1,
    Synchronous,
    DynamixelArm
};
enum command{
    STOP=0,

    LFU=10,
    LFD=20,
    LBU=30,
    LBD=40,
    RFU=50,
    RFD=60,
    RBU=70,
    RBD=80,

    LRFU=90,
    LRFD=100,
    LRBU=110,
    LRBD=120,

    FRONT=130,
    BACK=140,
    RIGHT=150,
    LEFT=160,

};

//std_msgs::Int32MultiArray cro_n;
std_msgs::Int32MultiArray motor_command;
//std_msgs::Float32MultiArray motor_command;
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


//ros::Publisher test_serial = nh.advertise<std_msgs::Int32MultiArray>("Serial_in",10);
void joy_callback(const sensor_msgs::Joy &joy_msg){

    joy_but joy;
    pairbutton=joy_msg.buttons[10];


    startbutton=joy_msg.buttons[9];

    speedmode+=startbutton;
    controlmode+=pairbutton;

    if(speedmode>=4){
        speedmode=1;
    }
                
    if(controlmode>=4){
        controlmode=1;
    } 

    joy.cro_n=joy_msg.buttons[13];
    joy.cro_s=joy_msg.buttons[14];   
    joy.cro_e=joy_msg.buttons[15];
    joy.cro_w=joy_msg.buttons[16];

    joy.l1 = joy_msg.buttons[4];
    joy.r1 = joy_msg.buttons[5];
    joy.l2 = joy_msg.buttons[6];
    joy.r2 = joy_msg.buttons[7];

    joy.il_stick = (int)joy_msg.axes[1];
    joy.ir_stick = (int)joy_msg.axes[4];

         if(joy.cro_n==1)
         motor_command.data[0]=FRONT;
         else if(joy.cro_s==1)
         motor_command.data[0]=BACK;
         else if(joy.cro_e==1)
         motor_command.data[0]=RIGHT;        
         else if(joy.cro_w==1)
         motor_command.data[0]=LEFT;   
         else 
         motor_command.data[0]=STOP; 


    switch (controlmode)
    {
    case Asynchronous:
        if(joy.l1==1)
        motor_command.data[1]=LFU;
        else if(joy.l2==1)
        motor_command.data[1]=LFD;
        else if(joy.r1==1)
        motor_command.data[1]=RFU; 
        else if(joy.r2==1)
        motor_command.data[1]=RFD;

        else if(joy.il_stick==1)
        motor_command.data[1]=LBU;    
        else if(joy.ir_stick==1)
        motor_command.data[1]=RBU;
        else if(joy.il_stick==-1)
        motor_command.data[1]=LBD;    
        else if(joy.ir_stick==-1)
        motor_command.data[1]=RBD;

        else 
        motor_command.data[1]=STOP;
        break;

    case Synchronous:
        if(joy.l1==1 || joy.r1==1)
        motor_command.data[1]=LRFU;
        else if(joy.l2==1 || joy.r2==1)
        motor_command.data[1]=LRFD;

        else if(joy.il_stick==1 || joy.ir_stick==1)
        motor_command.data[1]=LRBU;    
        else if(joy.il_stick==-1 || joy.ir_stick==-1)
        motor_command.data[1]=LRBD;

        else 
        motor_command.data[1]=STOP; 
        break;

    case DynamixelArm:
        /* code */
        break;
    //default:
       // break;
    }
    motor_command.data[2]=DEFAULT_SPEED*speedmode;







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


    //motor_command.data.resize(4);
    motor_command.data.resize(3);
    mode.data.resize(3);

    mode.data[1]=DEFAULT_SPEED;
    ros::Rate loop_rate(30);
    ROS_INFO("main");

    while(ros::ok()){

            switch (controlmode)
            {
            case Asynchronous:
                Flipper_Asynchronous.publish(motor_command);
                mode.data[0]=Asynchronous;
                ROS_INFO("AAAAAAAAAAAAAAA");

                
                break;

            case Synchronous:
                Flipper_Synchronous.publish(motor_command);
                mode.data[0]=Synchronous;
                 ROS_INFO("SSSSSSSSSSSSSSSSSSSS");               


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